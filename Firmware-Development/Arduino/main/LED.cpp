#include "LED.hpp"

CRGB leds[NUM_LEDS];

void LED::ledSetup() {
    FastLED.addLeds<WS2812B, DATA_PIN ,GRB>(leds, NUM_LEDS);  // GRB ordering is assumed
}

void LED::runSegments() {
    Serial.println("Checking set time");
    if (ledState) {
      Serial.println("running LED segments");
      // digitalWrite(LED_PIN, HIGH);
      for (uint8_t seg = 0; seg < NUM_SEGMENTS; seg++) {
        uint8_t totalPixels = segmentLedCount[seg];
        if (totalPixels == 0) continue;  // Skip empty segments

        uint8_t pixelsToLight = (totalPixels * segmentControls[seg].percentageComplete) / 100;
        CRGB segmentColor = segmentColors[seg];  // Get color for this segment

        Serial.print("Segment ");
        Serial.print(seg);
        Serial.print(": Lighting ");
        Serial.print(pixelsToLight);
        Serial.println(" pixels");

        for (uint8_t i = 0; i < totalPixels; i++) {
          uint8_t ledIndex = segmentLedIndices[seg][i];

        bool shouldLight = false;
        if (!segmentControls[seg].isInverted) {
            shouldLight = (i < pixelsToLight);
          } else {
            shouldLight = (i >= (totalPixels - pixelsToLight));
          }

          if (shouldLight) {
            leds[ledIndex] = segmentColor;  // Light with SEGMENT COLOR
            Serial.print("Lighting LED ");
            Serial.println(ledIndex);
          } else {
            leds[ledIndex] = CRGB::Black;  // Turn OFF
            Serial.print("Turning OFF LED ");
            Serial.println(ledIndex);
          }
        }
      }
    }
    else {
      // digitalWrite(LED_PIN, LOW);
      Serial.println("Out of Scheduled Time");
    }
    FastLED.show();  // Update LEDs
}
