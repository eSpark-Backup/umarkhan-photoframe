#include "TimeHandler.hpp"



time_t currentTime;



void TimeHandler::updateTime() {


    // configTime() called earlier in setup  configures the system time according to the fetched time from NTP
    time(&currentTime);  //fetches current system time in Epoch
    Serial.print("[TimeHandler syncTime] current Epoch time: ");
    Serial.println(currentTime);

     struct tm* tm_info = localtime(&currentTime);      //converts epoch time to readable
    if (tm_info) {
        Serial.print("[TimeHandler updateTime] Date and Time and Time zone:");Serial.println(&(*tm_info), "%Y-%m-%d %H:%M:%S -%Z");
    } else {
        Serial.println("[TimeHandler updateTime]Failed to convert epoch to local time");
    }

}




void TimeHandler::init(){
    // configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);       //fetches from NTP and configures system time
    configTzTime("GMT0BST,M3.5.0/1,M10.5.0", "pool.ntp.org");       //this one lines fetches time from UK and syncs the system time with it

    updateTime();

}

void TimeHandler::loop(){

    vTaskDelay(pdMS_TO_TICKS(1000));
    updateTime();
}