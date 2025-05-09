#ifndef CONFIG_HPP
#define CONFIG_HPP

//TEST
// #define LED_TEST_LOGS 

//HTTP
#define HTTP_REQ_INTERVAL_SEC 15
#define HTTP_REQ_INTERVAL_MS (HTTP_REQ_INTERVAL_SEC* 1000 )


//LED
#define NUM_SEGMENTS  23
#define NUM_LEDS 189
#define LED_DATA_PIN 4


//WIFI
#define WIFI_DEBUG 1                /* WIFI_DEBUG = 1 -> enable the localIP*/ /*WIFI_DEBUG = 0 -> Disable the localIP*/ 
#define ESP_AP_ID "LED_FRAME"
#define ESP_AP_PWD "12345678"
#define WIFI_ATTEMPTS 10
#define WIFI_ATTEMPTS_DURATION 5000     // 5 sec


//DISPLAY

#define SCROLL_BOX_HEIGHT 200
#define SCROLL_LINE_HEIGHT 20



#endif //CONFIG_HPP