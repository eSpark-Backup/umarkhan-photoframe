#ifndef WEBSERVER_HANDLER_H
#define WEBSERVER_HANDLER_H

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

#include "httpClient.hpp"
#include "TimeHandler.hpp"
#include "esp_sntp.h"

#include "config.hpp"




extern WebServer server;
extern Preferences preferences;
// const char* htmlForm;
extern bool ledState;


class WebServerHandler{

    public:
        void init();
        void loop();

    private:
        void checkLEDStatus();    
        void startAccessPoint();
        void setupWiFi();
        void setupWebServer();


        // void handleLEDControl();
        // void attemptWifiReconnect();

};

#endif
