# LedProgressBar - Alpha
Arduino library to sequentially turn on leds array or strip based on input value, like a progress bar.

Intermediate values will be faded. Eg.: an input value of 55% on a 10 led strip, will turn on first 5 leds with full brightness and 6th led with half brightness.

## ToDo
- [ ] Improve analog input smoothing
- [x] Fade between colors

## Examples
### Constructors
```C++
// Create a progress bar with 10 leds
LedProgressBar progressBar(10);

// Create a progress bar with 10 leds, all set to BLUE
LedProgressBar progressBar(10, CRGB::Blue);

// Create a progress bar with 10 leds, all set to BLUE, with pin monitoring
LedProgressBar progressBar(10, CRGB::Blue, A0);
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

// Set led 1 to GREEN and led 10 to RED.
// Leds 2-9 will have intermediate colors (eg.: GREEN -> YELLOW -> ORANGE -> RED)
progressBar.setColor(1, 10, CRGB::Green, CRGB::Red);

// Updates leds array/strip (turned on at 45%)
progressBar.setProgress(45);
```
### Helpers
```C++
// Return percentage value of input value (based on default 0-1023 analogRead range)
progressBar.calculatePercentage(inputValue);

// Return percentage value of input value, using custom min/max values
progressBar.calculatePercentage(inputValue, 10, 100);
```
