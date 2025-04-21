#ifndef WEBSERVER_HANDLER_H
#define WEBSERVER_HANDLER_H

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

#define WIFI_DEBUG 1                /* WIFI_DEBUG = 1 -> enable the localIP*/ /*WIFI_DEBUG = 0 -> Disable the localIP*/ 

#define ESP_AP_ID "ESP32_Config"
#define ESP_AP_PWD "12345678"
#define WIFI_ATTEMPTS 10
#define WIFI_ATTEMPTS_DURATION 5000     // 5 sec

extern WebServer server;
extern Preferences preferences;
// const char* htmlForm;
extern bool ledState;

void setupWiFi();
void handleRoot();
void handleConnect();
void handleLEDControl();
void setupWebServer();
void createTask();
void startAccessPoint();
void attemptWifiReconnect();
void checkLEDStatus();

#endif
