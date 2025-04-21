#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <NetworkClientSecure.h>

#define NUM_SEGMENTS  23

// const char* URL = "https://api-database-updater.ftled.workers.dev/" ;

static const char* URL = "https://api-database-updater.ftled.workers.dev/" ;

const unsigned long interval = 1; // 60,000 milliseconds = 1 minute

struct SegmentControl {
  uint8_t percentageComplete;  // 0-100
  bool isInverted;
};

extern SegmentControl segmentControls[NUM_SEGMENTS];

    void httpsClock();
    void makeRequest();
    void setClock();
    
    
#endif // HTTPSCLIENT_HPP
