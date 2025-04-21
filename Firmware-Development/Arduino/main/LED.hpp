#ifndef LED_HPP
#define LED_HPP

#include <FastLED.h>
#include "httpClient.hpp"
#include "WebServerHandler.hpp"

#define NUM_SEGMENTS 23
#define NUM_LEDS 189
#define DATA_PIN 3

// const int LED_PIN = 2;

const uint8_t segmentLedIndices[NUM_SEGMENTS][10] = {
  { 0, 1, 2 },        // Segment 0 → LEDs 0, 1, 2
  { 5, 6, 7, 8, 9 },  // Segment 1 → LEDs 5, 6, 7, 8, 9
  { 10, 11, 12 },     // Segment 2 → LEDs 10, 11, 12
  { 13, 14, 15 },     // Segment 3 → LEDs 13, 14, 15
  { 16, 17, 18 },     // Segment 4 → LEDs 16, 17, 18
  { 19, 20, 21 },     // Segment 5 → LEDs 16, 17, 18                    // need to add more leds address
};

// Number of LEDs in each segment
const uint8_t segmentLedCount[NUM_SEGMENTS] = {
  3, 5, 3, 3, 3, 3
};                                                                   // need to add leds in each segment


const CRGB segmentColors[NUM_SEGMENTS] = {
  CRGB::Red,     // Segment 0 color
  CRGB::Blue,    // Segment 1 color
  CRGB::Green,   // Segment 2 color
  CRGB::Yellow,  // Segment 3 color
  CRGB::Purple,  // Segment 4 color
  CRGB::Cyan,    // Segment 5 color
  // and so on for all NUM_SEGMENTS                                 // need to add color for each segments
};

void ledSetup();
void runSegments();

#endif  // LED_HPP