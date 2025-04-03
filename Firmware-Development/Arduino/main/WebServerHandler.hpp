#ifndef WEBSERVER_HANDLER_H
#define WEBSERVER_HANDLER_H

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

extern WebServer server;
extern Preferences preferences;

void setupWiFi();
void handleRoot();
void handleConnect();
void handleLEDControl();
void setupWebServer();

#endif
