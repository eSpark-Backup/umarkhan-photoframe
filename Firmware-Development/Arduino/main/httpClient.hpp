#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <NetworkClientSecure.h>

#define NUM_SEGMENTS  23

struct SegmentControl {
  uint8_t percentageComplete;  // 0-100
  bool isInverted;
};

extern SegmentControl segmentControls[NUM_SEGMENTS];

    void httpsClock();
    void makeRequest(const char* url);
    void setClock();
    
    
#endif // HTTPSCLIENT_HPP
