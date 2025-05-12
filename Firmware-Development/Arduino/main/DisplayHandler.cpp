#include "DisplayHandler.hpp"


ResponseString animationText[NUM_SEGMENTS];
// bool segmentConfigReceivedFlag;
TFT_eSPI tft = TFT_eSPI();

// Scroll box parameters

int scroll_y = 0;

void DisplayHandler::init() {
        tft.init();
        tft.setRotation(1);
        tft.fillScreen(TFT_BLACK);
        // Draw static layout
        drawLayout();

}

void DisplayHandler::loop() {
        updateTimeDisplay();
        if(segmentConfigReceivedFlag){
                Serial.println("[ display handler: loop ] Updating Scroll Box ");
                updateScrollBox();
        }
            vTaskDelay(pdMS_TO_TICKS(1000));
}

void DisplayHandler::updateScrollBox(){
        segmentConfigReceivedFlag= false;
                // Add some demo scroll text
        for (int i = 0; i <= NUM_SEGMENTS-1; i++) {
            addLineToScrollBox(animationText[i].responseLine);
            vTaskDelay(pdMS_TO_TICKS(10));
        }
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
        // Display time
         struct tm timeinfo;
        if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return;
        }

        // Format date and time (without timezone)
        char dateTimeStr[64];
        strftime(dateTimeStr, sizeof(dateTimeStr), "%Y-%m-%d %H:%M:%S", &timeinfo);

        // Format timezone only
        char timeZoneStr[16];
        strftime(timeZoneStr, sizeof(timeZoneStr), "%Z", &timeinfo);

        tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
        tft.drawString(dateTimeStr, 60, SCROLL_BOX_HEIGHT + 10, 2);
        tft.drawString(timeZoneStr, tft.width() / 2  + 60, SCROLL_BOX_HEIGHT + 10, 2);
        //   Serial.print("Date-Time: ");
        // Serial.println(dateTimeStr);

        // Serial.print("Time Zone: ");
        // Serial.println(timeZoneStr);
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
