# LedProgressBar
Arduino library to turn on (fading) leds based on input value, like a progress bar.

## Examples
### Constructors
```C++
LedProgressBar progressBar(10);
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
