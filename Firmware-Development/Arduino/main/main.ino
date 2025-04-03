
#include <Arduino.h>
#include "SPIFFHandler.hpp"
#include "WebServerHandler.hpp"

const int LED_PIN = 2;

void setup() {
    Serial.begin(115200);
    delay(1000);

    // Initialize SPIFFS
    if (initSPIFFS()) {
        loadHTMLFiles();
    }

    // Set LED pin as output
    pinMode(LED_PIN, OUTPUT);

    // Setup Wi-Fi and WebServer
    setupWiFi();
    setupWebServer();
}

void loop() {
    server.handleClient();
    // updateLED();
}
