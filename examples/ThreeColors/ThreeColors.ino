#include <FastLED.h>
#include <LedProgressBar.h>

#define DATA_PIN 2
#define NUM_LEDS 10

LedProgressBar progressBar(NUM_LEDS);

void setup() {

  progressBar.setDebug(true);

  // Set all leds to GREEN
  progressBar.setColor(CRGB::Green);

  // Set leds 6, 7 and 8 to ORANGE
  progressBar.setColor(6, 8, CRGB::Orange);

  // Set leds 9 and 10 to RED
  progressBar.setColor(9, 10, CRGB::Red);

  // Initialize FastLED object
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(progressBar.leds, NUM_LEDS);
}

void loop() {
  progressBar.setProgress(random(0, 100));

  delay(3000);
}