# LedProgressBar - Alpha
Arduino library to sequentially turn on leds array or strip based on input value, like a progress bar.

Intermediate values will be faded. Eg.: an input value of 55% on a 10 led strip, will turn on first 5 leds with full brightness and 6th led with half brightness.

## Examples
### Constructors
```C++
// Create a progress bar with 10 leds
LedProgressBar progressBar(10);

// Create a progress bar with 10 leds, all set to BLUE
LedProgressBar progressBar(10, CRGB::Blue);
```
### Methods
```C++
// Set all leds to GREEN
progressBar.setColor(CRGB::Green);

// Set first led to BLUE
progressBar.setColor(CRGB::Blue);

// Set leds 7 and 8 to ORANGE
progressBar.setColor(7, 8, CRGB::Orange);

// Set leds 9 and 10 to RED
progressBar.setColor(9, 10, CRGB::Red);

// Updates leds array/strip (turned on at 45%)
progressBar.setProgress(45);
```
