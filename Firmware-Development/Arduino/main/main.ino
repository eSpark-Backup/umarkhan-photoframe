
#include <Arduino.h>
#include "SPIFFHandler.hpp"
#include "WebServerHandler.hpp"
#include "WifiMonitoring.hpp"
#include "httpClient.hpp"
#include "LED.hpp"
#include "DisplayHandler.hpp"
#include "config.hpp"



LED led;
HttpClient httpclientt;
SPIFFHandler spiff;
WebServerHandler webserver;
DisplayHandler displayhandle;

void setup() {
    Serial.begin(115200);
    delay(1000);
   
    // Setup Wi-Fi 
    webserver.setupWiFi();
    webserver.setupWebServer();
    // Initialize SPIFFS
    if (spiff.initSPIFFS()) {
        spiff.loadHTMLFiles();
    }
   
    httpclientt.httpsClock(); 
    led.ledSetup();   
    displayhandle.init();

    xTaskCreate(webServerTask, "webServerTask", 4096, NULL, 1, NULL);
    xTaskCreate(mainTask , "mainTask" , 4096 ,NULL , 2 , NULL);
    xTaskCreate(httpRequestTask , "httpRequestTask" , 8192 , NULL , 2 , NULL );

}

// String currentDateTime;
void mainTask( void * pvParameter){
   
        while(true){
            vTaskDelay(pdMS_TO_TICKS(100));

            wifiMonitoring();
            webserver.checkLEDStatus();
            led.runSegments();
            displayhandle.loop();
            Serial.print("current date and time");Serial.println(currentDateTime);
            // printf("[loop] ledState: %d\n\r" , ledState);
        }

}

void httpRequestTask(void * pvParameter){
    vTaskDelay(pdMS_TO_TICKS(HTTP_REQ_INTERVAL_MS));
    while(true){
        httpclientt.makeRequest();
        vTaskDelay(pdMS_TO_TICKS(HTTP_REQ_INTERVAL_MS));
    }
}

void webServerTask(void * pvParameter){
    while (true) {
      webserver.clientloop();
      vTaskDelay(10/ portTICK_PERIOD_MS);
    }
}



void loop() {}





