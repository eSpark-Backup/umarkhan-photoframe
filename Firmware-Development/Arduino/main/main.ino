
#include <Arduino.h>
#include "SPIFFHandler.hpp"
#include "WebServerHandler.hpp"
#include "WifiMonitoring.hpp"
#include "httpClient.hpp"
#include "LED.hpp"
#include "DisplayHandler.hpp"
#include "TimeHandler.hpp"
#include "config.hpp"



LED led;
HttpClient httpclientt;
SPIFFHandler spiff;
WebServerHandler webserver;
DisplayHandler displayhandle;
TimeHandler timehandle;

void setup() {
    Serial.begin(115200);
    delay(1000);
   
    // Setup Wi-Fi 
    webserver.init();
    timehandle.init();

    // Initialize SPIFFS
    if (spiff.initSPIFFS()) {
        spiff.loadHTMLFiles();
    }
   
    led.ledSetup();   
    displayhandle.init();

    xTaskCreate(webServerTask, "webServerTask", 4096, NULL, 1, NULL);
    xTaskCreate(mainTask , "mainTask" , 4096 ,NULL , 2 , NULL);
    xTaskCreate(httpRequestTask , "httpRequestTask" , 8192 , NULL , 2 , NULL );

}

void mainTask( void * pvParameter){
   
        while(true){
            vTaskDelay(pdMS_TO_TICKS(100));
            wifiMonitoring();
            led.runSegments();
            displayhandle.loop();
            timehandle.loop();
          
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
      webserver.loop();
      vTaskDelay(10/ portTICK_PERIOD_MS);
    }
}



void loop() {}





