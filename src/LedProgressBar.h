#ifndef LEDPROGRESS_H
#define LEDPROGRESS_H

#include <Arduino.h>
#include <FastLED.h>

class LedProgressBar
{
  // Analog input smoothing
  float smoothedReading;
  float smoothingFactor = .9;
  int deadZone = 3;

  public:
    // Constructors
    LedProgressBar(int _numleds);
    LedProgressBar(int _numleds, CRGB _color);
    LedProgressBar(int _numleds, CRGB _color, byte inputPin);

    // Methods
    void run();
    void setInputRange(int min, int max);
    void setColor(CRGB color);
    void setColor(int index, CRGB color);
    void setColor(int start, int end, CRGB color);
    void setColor(int start, int end, CRGB startColor, CRGB endColor);
    void setProgress(int progress);
    void setDebug(bool state);
    int calculatePercentage(int inputValue);
    int calculatePercentage(int inputValue, int min, int max);
    int getProgress();
    float smooth(float input);

    // Variables
    CRGB *leds;       // leds array used by FastLED library
    CRGB *ledsColors; // leds colors

  private:
    // Methods
    void update(int _inputValue);

    // Variables
    int numleds;
    byte inputPin = 255;
    int min = 0;
    int max = 1023; // default max value for analogRead
    int progress = 0;
    bool debug = false;
    CRGB color;
};

#endif