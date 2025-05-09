#include "DisplayHandler.hpp"


ResponseString animationText[NUM_SEGMENTS];

TFT_eSPI tft = TFT_eSPI();

// Scroll box parameters

int scroll_y = 0;

void DisplayHandler::init() {
        tft.init();
        tft.setRotation(1);
        tft.fillScreen(TFT_BLACK);

        // Set timezone using environment variable style (change as needed)
        configTzTime("PKT-5", "pool.ntp.org");  // Pakistan Standard Time (UTC+5)

        // Draw static layout
        drawLayout();

        // Add some demo scroll text
        for (int i = 0; i <= NUM_SEGMENTS-1; i++) {
            addLineToScrollBox(animationText[i].responseLine);
            vTaskDelay(pdMS_TO_TICKS(300));
        }
}

void DisplayHandler::loop() {
        updateTimeDisplay();
            vTaskDelay(pdMS_TO_TICKS(1000));
}

void DisplayHandler::drawLayout() {
        // Draw scroll box (top part of screen)
        tft.drawRect(0, 0, tft.width(), SCROLL_BOX_HEIGHT, TFT_WHITE);
        scroll_y = SCROLL_LINE_HEIGHT;

        // Draw info area (bottom row)
        tft.fillRect(0, SCROLL_BOX_HEIGHT + 1, tft.width(), 40, TFT_DARKGREY);

        // Labels
        tft.setTextColor(TFT_YELLOW, TFT_DARKGREY);
        tft.drawString("Time:", 10, SCROLL_BOX_HEIGHT + 10, 2);
        tft.drawString("Zone:", tft.width() / 2 + 10, SCROLL_BOX_HEIGHT + 10, 2);
}

void DisplayHandler::updateTimeDisplay() {
        struct tm timeinfo;
        if (!getLocalTime(&timeinfo)) {
            Serial.println("Failed to get time");
            return;
        }

        char timeStr[9];
        strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeinfo);

        char zoneStr[6];
        strftime(zoneStr, sizeof(zoneStr), "%z", &timeinfo);  // +0500 format

        // Display time
        tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
        tft.drawString(timeStr, 60, SCROLL_BOX_HEIGHT + 10, 2);
        tft.drawString(zoneStr, tft.width() / 2 + 60, SCROLL_BOX_HEIGHT + 10, 2);
}

void DisplayHandler::addLineToScrollBox(String line) {
        // Scroll up by one line height
        // tft.scroll( -SCROLL_LINE_HEIGHT );

        // Fill the new line area at bottom
        tft.fillRect(1, SCROLL_BOX_HEIGHT - SCROLL_LINE_HEIGHT + 1, tft.width() - 2, SCROLL_LINE_HEIGHT - 2, TFT_BLACK);

        // Draw new text
        tft.setTextColor(TFT_CYAN, TFT_BLACK);
        tft.drawString(line, 4, SCROLL_BOX_HEIGHT - SCROLL_LINE_HEIGHT + 4, 2);
}
