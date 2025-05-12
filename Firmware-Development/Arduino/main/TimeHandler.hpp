#ifndef TIME_HANDLER
#define TIME_HANDLER


#include <WiFi.h>
#include <time.h>



class TimeHandler{

    public:
        void init();
        void loop();

    private:
        void updateTime();


};



#endif //TIME_HANDLER
