#ifndef NixieModule_h
#define NixieModule_h

#include "FastLED.h"
#include "Arduino.h"

class NixieModule{
  public:
    void begin(int position);
    void displayNumber(int number, bool showZero, CRGB inputLeds[180]);
    void displayFirstDigit(char numToDisplay, CRGB inputLeds[180]);
    void displaySecondDigit(char numToDisplay, CRGB inputLeds[180]);
    String numToString(int number, bool showZero);

    //main color to use to display a number
    CRGB mainProfile = CRGB(0,255,80);

    const int LEDS_PER_MODULE = 60;
    const int TOTAL_NUM_LEDS = 180;
    //each module comes with 60 LEDs which is split into 6 groups of 10
    const int LEDS_PER_COLUMN = 10;


    byte firstLEDId;
    byte lastLEDId;

    //set to 0 by default. 0 indicates the first position/first module
    int modulePosition = 0;
};

#endif