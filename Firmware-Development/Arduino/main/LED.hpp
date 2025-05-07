#ifndef LED_HPP
#define LED_HPP

#include <FastLED.h>

#include "httpClient.hpp"
#include "WebServerHandler.hpp"
#include "config.hpp"




const uint8_t segmentLedIndices[NUM_SEGMENTS][15] = {


  { 76 , 67 , 68 , 69 , 70 ,71 ,72, 73 ,74 , 75  } ,                                       // segment 1
  { 60 , 61 , 62, 63 , 64 ,65 , 66 , 78 , 79  },                                         // segment 2
  { 80, 81 , 82 ,83 ,84 ,85 ,86 }   ,                                                     // segment 4
  { 88 , 89 , 90 , 91 , 92 , 93 , 94 }   ,                                                // segment 5 
  { 52 , 53} ,                                                                           //segment 6
  { 55 , 56 , 57 } ,                                                                      //segment 7
  { 58 , 50} ,                                                                            // segment 8
  { 95 , 96 , 97 , 98 , 99 , 100 , 101 } ,                                              // segment 9
  { 125 , 126 , 127 , 128 , 129 , 130  , 131 } ,                                         //segment 10
  { 124  , 133 , 134 , 135 , 136 , 137 ,138 , 139 , 140 ,141 ,142 ,143, 144 ,145 }  ,     // segment 11
  { 118 , 117 , 119 , 120 , 121 , 122 , 123 }  ,                                         //segment 12
  { 103 , 104 , 105 , 106 , 107 , 108 , 109 , 110 } ,                                     //segment 13
  { 35 , 36 , 37 ,38 , 39 , 40 , 41 ,42 ,43 , 44, 45, 46 , 47, 48 , 49 }  ,               // segment 14
  { 111 , 112 , 113 , 114 , 115, 116  }  ,                                                 //segment 15
  { 147 , 148 , 149 , 150 , 151 , 152 , 153 ,154 , 155 , 156 , 157 , 158  } ,              // segment 16
  { 18 , 19 , 20 , 21 ,  22, 23, 24, 25, 26 , 27,28 ,29 ,30 ,31 ,32  },                    // segment 17
  {  166 , 165 , 164 , 163 , 162 , 161 , 160 , 159 , 33 }  ,                               // segment 18 
  { 12 , 13 , 14 , 15 , 16  } ,                                                              // segment 19
  { 168  , 188 , 187 , 186 , 185 , 184 , 183 ,182  }    ,                                //segement 20 
  { 1, 2 , 3, 4 , 5 , 6, 7, 8 , 9, 10 , 11 },                                                //segment 21
  { 169 , 170 , 171 , 172  }   ,                                                            // segment 22
  { 174 , 175 , 176 , 177 , 178 , 179 , 180 , 181 }   ,                                      //segment 23



};

// // Number of LEDs in each segment
const uint8_t segmentLedCount[NUM_SEGMENTS] = {
  10 ,   //1            
  9 ,       //3
   7 ,      //4
   7 ,      //5
   2 ,    //6
   3 ,    //7
   2,     //8
   7 ,    //9
   7 ,    //10
   14 ,     //11
   7,     //12
   8 ,    //13
   15 ,     //14
   6 ,    // 15
   12 ,     //16
   15 ,     //17
   9 ,      //18
  5 ,       //19
  8 ,       //20
  11 ,      //21
  4 ,       //22
  8 ,       //23

};                                                                   // need to add leds in each segment


const CRGB segmentColors[NUM_SEGMENTS] = {

  CRGB(28, 0 , 235 ),           //segment 1 
  CRGB::Red,                    // segment 2
  CRGB(192, 2 , 230 ),           //segment 4
  CRGB(216, 139 , 130 ),           //segment 5
  CRGB(96, 142 , 126 ),           //segment 6
  CRGB::Yellow,                 // segment 7 
  CRGB(255, 152 , 0 ),           //segment 8
  CRGB(0, 255 , 221 ),           //segment 9
  CRGB(190, 186 , 162 ),           //segment 10
  CRGB(61, 255 , 0 ),           //segment 11
  CRGB(250, 171 , 210 ),           //segment 12
  CRGB(106, 43 , 43 ),           //segment 13
  CRGB(173, 184 , 37 ),           //segment 14
  CRGB(68, 111 , 147 ),           //segment 15
  CRGB(158, 203 , 173 ),           //segment 16
  CRGB(40, 19 , 60 ),             //segment 1
  CRGB(132, 117 , 137 ),           //segment 18
  CRGB(16, 195 , 139 ),           //segment 19
  CRGB(185, 211 , 163 ),           //segment 20
  CRGB(3, 46 , 44 ),           //segment 21
  CRGB(83, 74 , 107 ),           //segment 22
  CRGB(169, 43 , 43 ),           //segment 23

};


class LED{

  public:

    void ledSetup();
    void runSegments();
  

};

#endif  // LED_HPP