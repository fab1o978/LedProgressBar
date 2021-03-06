#include <LedProgressBar.h>
#include <ColorFade.h>

// Initialize new LedProgressBar object with given leds number
LedProgressBar::LedProgressBar(int _numleds)
{
    // set how many leds to control
    numleds = _numleds;

    // initialize leds array
    leds = new CRGB[numleds];

    // initialize leds colors array
    ledsColors = new CRGB[numleds];
}

// Initialize new LedProgressBar object with given leds number and color
LedProgressBar::LedProgressBar(int _numleds, CRGB _color)
{
    // set how many leds to control
    numleds = _numleds;

    // set default color
    color = _color;

    // initialize leds array
    leds = new CRGB[numleds];

    // initialize leds colors array
    ledsColors = new CRGB[numleds];

    // Set all leds color
    setColor(color);
}

LedProgressBar::LedProgressBar(int _numleds, CRGB _color, byte _pin)
{
    // set how many leds to control
    numleds = _numleds;

    // set default color
    color = _color;

    // initialize leds array
    leds = new CRGB[numleds];

    // initialize leds colors array
    ledsColors = new CRGB[numleds];

    // Set all leds color
    setColor(color);

    // Set pin to monitor
    inputPin = _pin;

    pinMode(inputPin, INPUT);
}

// adjust minimum and maximum values used on map function
void LedProgressBar::setInputRange(int _min, int _max)
{
    min = _min;
    max = _max;
}

// set all leds color
void LedProgressBar::setColor(CRGB _color)
{
    for (int i = 0; i < numleds; i++)
    {
        ledsColors[i] = _color;
    }
}

// set individual led color (starting from 1)
void LedProgressBar::setColor(int _index, CRGB _color)
{
    ledsColors[_index - 1] = _color;
}

// set led color for given range of leds
void LedProgressBar::setColor(int _start, int _end, CRGB _color)
{
    int first = _start - 1;
    int last = _end - 1;

    for (int i = first; i <= last; i++)
    {
        ledsColors[i] = _color;
    }
}

// Set start/end color, fading between them across leds range
void LedProgressBar::setColor(int _start, int _end, CRGB _startColor, CRGB _endColor)
{
    int first = _start - 1;
    int last = _end - 1;
    int steps = 1000 / (_end - _start);

    // Set start / end colors
    ledsColors[first] = _startColor;
    ledsColors[last] = _endColor;

    for (int i = _start; i <= _end; i++){
        ledsColors[i] = fadeTowardColor(_startColor, _endColor, steps);
    }
}

void LedProgressBar::usePot(bool state)
{
    usePotentiometer = state;
}

// calculate percentage from input value
int LedProgressBar::calculatePercentage(int _inputValue)
{
    return map(constrain(_inputValue, min, max), min, max, 0, 100);
}

// calculate percentage from input value using specified min and max values
int LedProgressBar::calculatePercentage(int _inputValue, int _min, int _max)
{
    return map(constrain(_inputValue, _min, _max), _min, _max, 0, 100);
}

// return current progress value
int LedProgressBar::getProgress()
{
    return progress;
}

// set progress value and update leds
void LedProgressBar::setProgress(int _progress)
{
    progress = _progress;

    update(progress);
}

// set debug state
void LedProgressBar::setDebug(bool _state)
{
    debug = _state;
}

// Smooths analog input value
float LedProgressBar::smooth(float _inputValue)
{
    // Calculates difference
    unsigned int difference = smoothedReading - _inputValue;

    // If difference is bigger than deadZone value, then set new value as smoothedReading base value
    if (difference > deadZone)
    {
        smoothedReading = _inputValue;
    }
    else
    {
        smoothedReading = smoothedReading * smoothingFactor + _inputValue * (1 - smoothingFactor);
    }

    return smoothedReading;
}

// updates leds state (must be followed by FastLED.show())
void LedProgressBar::update(int _progress)
{
    float total = map(_progress, 0, 100, 0, 255 * numleds);

    for (int led = 0; led < numleds; led++)
    {

        // reset default color
        leds[led] = ledsColors[led];

        // set brightness
        int fadeBy = 255 - constrain(total, 0, 255);
        leds[led].fadeLightBy(fadeBy);

        if (debug)
        {
            Serial.print("[LED");
            Serial.print(led + 1);
            Serial.print("] ");
            Serial.print(255 - fadeBy);
            Serial.print(" | ");

            Serial.print("R: ");
            Serial.print(leds[led].r);
            Serial.print(" G: ");
            Serial.print(leds[led].g);
            Serial.print(" B: ");
            Serial.println(leds[led].b);
        }

        total -= 255;
    }

    // Add newline to separate output
    if (debug)
    {
        Serial.println("");
    }
}

void LedProgressBar::run()
{
    // Works only if input pin has been defined
    if(inputPin != 255 && usePotentiometer){

        // Read and smooth analog read
        smooth(analogRead(inputPin));

        Serial.print("Reading: ");
        Serial.println((int)smoothedReading);

        // Updates current percentage based on analog input
        setProgress(calculatePercentage(smoothedReading));
    }
    else
    {
        setProgress(100);
    }
    
}