#ifndef WEBSERVER_HANDLER_H
#define WEBSERVER_HANDLER_H

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>


#include "config.hpp"



extern WebServer server;
extern Preferences preferences;
// const char* htmlForm;
extern bool ledState;


class WebServerHandler{

    public:
        void setupWiFi();
        // void createTask();
        void setupWebServer();
        void checkLEDStatus();    
        void clientloop();

    private:
        void startAccessPoint();



        // void handleLEDControl();
        // void attemptWifiReconnect();

};

#endif
