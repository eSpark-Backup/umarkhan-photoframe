#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <NetworkClientSecure.h>

#include "config.hpp"



static const char* URL = "https://api-database-updater.ftled.workers.dev/" ;

extern bool segmentConfigReceivedFlag;
extern String currentDateTime;
extern String currentTimeZone;
struct SegmentControl {
  uint8_t percentageComplete =100 ;  // 0-100
  bool isInverted = false;
};

extern SegmentControl segmentControls[NUM_SEGMENTS];

typedef struct {
  String responseLine;
}ResponseString;

extern ResponseString respStr[NUM_SEGMENTS];


class HttpClient{

  public:
      void makeRequest();

  private:
      void fetchSegmentsFromPayload(const String& payload);
    
};


#endif // HTTPSCLIENT_HPP
