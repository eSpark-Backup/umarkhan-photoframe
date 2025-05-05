#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <NetworkClientSecure.h>

#define NUM_SEGMENTS  23
#define INTERVAL_MIN 1
// const char* URL = "https://api-database-updater.ftled.workers.dev/" ;

static const char* URL = "https://api-database-updater.ftled.workers.dev/" ;

const unsigned long interval = INTERVAL_MIN; // 60,000 milliseconds = 1 minute

struct SegmentControl {
  uint8_t percentageComplete;  // 0-100
  bool isInverted;
};

extern SegmentControl segmentControls[NUM_SEGMENTS];


class HttpClient{

  public:
      void httpsClock();
      void makeRequest();
      void setClock();

  private:
      void fetchSegmentsFromPayload(const String& payload);
    
};


#endif // HTTPSCLIENT_HPP
