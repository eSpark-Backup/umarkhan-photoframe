
#include <Arduino.h>
#include "SPIFFHandler.hpp"
#include "WebServerHandler.hpp"
#include "WifiMonitoring.hpp"
#include "httpClient.hpp"
#include "LED.hpp"

// const int LED_PIN = 2;
LED led;
HttpClient httpclientt;
SPIFFHandler spiff;
WebServerHandler webserver;

void setup() {
    Serial.begin(115200);
    delay(1000);
   
    // Setup Wi-Fi 
    webserver.setupWiFi();
    webserver.createTask();
    // Initialize SPIFFS
    if (spiff.initSPIFFS()) {
        spiff.loadHTMLFiles();
    }
   // WebServer
    // Set LED pin as output
    // pinMode(LED_PIN, OUTPUT);
    httpclientt.httpsClock(); 
    led.ledSetup();   
}

void loop() {
    // server.handleClient();
    delay(100);

    wifiMonitoring();
    webserver.checkLEDStatus();
    httpclientt.makeRequest();
    led.runSegments();

    printf("[loop] ledState: %d\n\r" , ledState);
}
