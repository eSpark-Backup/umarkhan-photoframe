
#include <Arduino.h>
#include "SPIFFHandler.hpp"
#include "WebServerHandler.hpp"
#include "WifiMonitoring.hpp"

const int LED_PIN = 2;

void setup() {
    Serial.begin(115200);
    delay(1000);
   
    // Setup Wi-Fi 
    setupWiFi();
    createTask();
    // Initialize SPIFFS
    if (initSPIFFS()) {
        loadHTMLFiles();
    }
   // WebServer
    // Set LED pin as output
    pinMode(LED_PIN, OUTPUT);    
}

void loop() {
    // server.handleClient();
    delay(100);
    wifiMonitoring();
    checkLEDStatus();

}
