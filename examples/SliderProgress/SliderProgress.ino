#include <SoftwareSerial.h>
#include <SerialCommand.h>
#include <FastLED.h>
#include <LedProgress.h>

#define DATA_PIN 2
#define NUM_LEDS 10

SerialCommand SCmd;
LedProgress progressBar(NUM_LEDS);

void setup() {
  // initialize serial:
  Serial.begin(9600);

  SCmd.addCommand("T", set_progressbar);
  SCmd.addDefaultHandler(unrecognized);

  progressBar.setDebug(true);

  // Set all leds to GREEN
  progressBar.setColor(CRGB::Green);

  // Set leds 6, 7 and 8 to ORANGE
  progressBar.setColor(6, 8, CRGB::Orange);

  // Set leds 9 and 10 to RED
  progressBar.setColor(9, 10, CRGB::Red);

  // tune slider min/max values
  // progressBar.setInputRange(10, 100);

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(progressBar.leds, NUM_LEDS);
}

void loop() {
  SCmd.readSerial();

  delay(50);
}

void set_progressbar() {

  int inputValue;
  char *arg;

  arg = SCmd.next();

  if (arg != NULL)
  {
    inputValue = atoi(arg);

    progressBar.setProgress(progressBar.calculateProgress(inputValue, 0, 100));

    Serial.print("Current progress: ");
    Serial.print(progressBar.getProgress());
    Serial.println('%');

    FastLED.show();
  }
}

void unrecognized() {
  Serial.println("What?");
}
