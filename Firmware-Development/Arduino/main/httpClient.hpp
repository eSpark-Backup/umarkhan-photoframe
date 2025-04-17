#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <NetworkClientSecure.h>

    void begin();
    void makeRequest(const char* url);
    void setClock();
    
    
#endif // HTTPSCLIENT_HPP
