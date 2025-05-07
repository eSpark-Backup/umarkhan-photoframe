#ifndef WIFI_MONITORING_H
#define WIFI_MONITORING_H

#include <WiFi.h>

#include "WebServerHandler.hpp"
#include "config.hpp"

bool reconnecting = false;

inline void wifiMonitoring() {

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wifi Connection failed!");
    WiFi.disconnect();
    vTaskDelay(pdMS_TO_TICKS(100));

    
    WiFi.reconnect();
    vTaskDelay(pdMS_TO_TICKS(100));

    reconnecting = false;
  } else {
    if (!reconnecting) {
      Serial.println("Wi-Fi Connected successfully!");
      reconnecting = true;
    }
  }
}
#endif  // WIFI_MONITORING_H
