#include "SPIFFHandler.hpp"

String htmlForm;
String successPage;

bool initSPIFFS() {
    if (!SPIFFS.begin()) {
        Serial.println("SPIFFS Mount Failed");
        return false;
    }
    return true;
}

void loadHTMLFiles() {
    File file = SPIFFS.open("/wifi_setup.html", "r");
    if (file) {
        htmlForm = file.readString();
        file.close();
    } else {
        Serial.println("Failed to open Wi-Fi setup HTML file.");
    }

    file = SPIFFS.open("/wifi_success.html", "r");
    if (file) {
        successPage = file.readString();
        Serial.println("Successfully to open file!");
        file.close();
    } else {
        Serial.println("Failed to open Wi-Fi success HTML file.");
    }
}
