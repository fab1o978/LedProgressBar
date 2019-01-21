#include <LedProgressBar.h>

// Initialize new LedProgressBar object with given leds number
LedProgressBar::LedProgressBar(int _numleds){
    // set how many leds to control
    numleds = _numleds;

    // initialize leds array
    leds = new CRGB[numleds];

    // initialize leds colors array
    ledsColors = new CRGB[numleds];
}

// Initialize new LedProgressBar object with given leds number and color
LedProgressBar::LedProgressBar(int _numleds, CRGB _color){
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

// adjust minimum and maximum values used on map function
void LedProgressBar::setInputRange(int _min, int _max){
    min = _min;
    max = _max;
}

// set all leds color
void LedProgressBar::setColor(CRGB _color){
    for (int i = 0; i < numleds; i++)
    {
        ledsColors[i] = _color;
    }
}

// set individual led color (starting from 1)
void LedProgressBar::setColor(int _index, CRGB _color){
    ledsColors[_index - 1] = _color;
}

// set led color for given range of leds
void LedProgressBar::setColor(int _start, int _end, CRGB _color){
    int first = _start - 1;
    int last = _end - 1;

    for (int i = first; i <= last; i++){
        ledsColors[i] = _color;
    }
}

// calculate percentage from input value
int LedProgressBar::calculatePercentage(int _inputValue){
    return map(constrain(_inputValue, min, max), min, max, 0, 100);
}

// calculate percentage from input value using specified min and max values
int LedProgressBar::calculatePercentage(int _inputValue, int _min, int _max){
    return map(constrain(_inputValue, _min, _max), _min, _max, 0, 100);
}

// return current progress value
int LedProgressBar::getProgress(){
    return progress;
}

// set progress value and update leds
void LedProgressBar::setProgress(int _progress){
    progress = _progress;

    update(progress);
}

// set debug state
void LedProgressBar::setDebug(bool _state){
    debug = _state;
}

float LedProgressBar::smooth(float _inputValue){
    unsigned int difference = smoothedReading - _inputValue;

    if(debug){
        Serial.print("Difference: ");
        Serial.println(difference);
    }

    if(difference > deadZone){
        smoothedReading = _inputValue;
    } else {
        smoothedReading = smoothedReading * smoothingFactor + _inputValue * (1 - smoothingFactor);
    }

    return smoothedReading;
}

// updates leds state (must be followed by FastLED.show())
void LedProgressBar::update(int _progress){

    float total = map(_progress, 0, 100, 0, 255 * numleds);

    for (int led = 0; led < numleds; led++) {

        // reset default color
        leds[led] = ledsColors[led];

        // set brightness
        int fadeBy = 255 - constrain(total, 0, 255);
        leds[led].fadeLightBy(fadeBy);

        if(debug){
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
    if(debug){
        Serial.println("");
    }
}