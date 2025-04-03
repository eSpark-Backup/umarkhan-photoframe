#ifndef SPIFFS_HANDLER_H
#define SPIFFS_HANDLER_H

#include <Arduino.h>
#include <SPIFFS.h>

extern String htmlForm;
extern String successPage;

bool initSPIFFS();
void loadHTMLFiles();

#endif
