#ifndef DISPLAY_HANDLER
#define DISPLAY_HANDLER



#include <TFT_eSPI.h>  // TFT library
#include <SPI.h>
#include <time.h>

#include "config.hpp"
#include "httpClient.hpp"


class DisplayHandler{

    public:
        void init();
        void loop();

    private:
        void drawLayout() ;
        void updateTimeDisplay() ;
        void addLineToScrollBox(String line) ;


};







#endif // DISPLAY_HANDLER