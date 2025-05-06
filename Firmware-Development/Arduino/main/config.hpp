#ifndef CONFIG_HPP
#define CONFIG_HPP




#define NUM_SEGMENTS  23
#define NUM_LEDS 189
#define DATA_PIN 5



#define WIFI_DEBUG 1                /* WIFI_DEBUG = 1 -> enable the localIP*/ /*WIFI_DEBUG = 0 -> Disable the localIP*/ 
#define ESP_AP_ID "LED_FRAME"
#define ESP_AP_PWD "12345678"
#define WIFI_ATTEMPTS 10
#define WIFI_ATTEMPTS_DURATION 5000     // 5 sec


#define HTTP_REQ_INTERVAL_SEC 30
#define HTTP_REQ_INTERVAL_MS (HTTP_REQ_INTERVAL_SEC* 1000 )




#endif