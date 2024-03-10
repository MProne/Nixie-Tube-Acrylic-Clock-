#include "Arduino.h"

#include "NixieModule.h"
#include "FastLED.h"

//assigns values to variables needed later in the program
void NixieModule::begin(int position){
  
  modulePosition = position;
  
  position++;
  
  //record Ids of first and last LED in the module
  firstLEDId = (LEDS_PER_MODULE * position) - LEDS_PER_MODULE;
  lastLEDId = (LEDS_PER_MODULE * position) - 1;

  
}

//Turns number into a string and handles if a 0 wants to be displayed on a 1 digit number
String NixieModule::numToString(int number, bool showZero){
  
  String numAsString = String(number);
  String outputString = "  ";
  
  
  //if the number only contains 1 digit and showZero is true, then display a 0 as the second digit
  //and the actual number as the first digit
  if(numAsString.length() == 1  && showZero){
  
    outputString[1] = numAsString[0];
    outputString[0] = '0';
    
  //if the number only contains 1 digit and showZero is false, then don't display anything (represented with an X)
  //on the second digit and display the actual number as the first digit
  }else if(numAsString.length() == 1 && !showZero){
  
    outputString[1] = numAsString[0];
    outputString[0] = 'X';
  
  }else{
  
    outputString = numAsString;
  
  }
 
  return outputString;
}


//takes a single digit from a number and displays it on the right acrylic panels of the module
void NixieModule::displayFirstDigit(char numToDisplay, CRGB inputLeds[180]){
  CRGB RGBProfile = mainProfile;
  
  int offsetValue = 0;
  
  if(numToDisplay == 'X'){
    RGBProfile = CRGB(0,0,0);
  }else{
    offsetValue = String(numToDisplay).toInt();
  }


  inputLeds[LEDS_PER_COLUMN - offsetValue - 1 + (60 *modulePosition)] = RGBProfile;
  //Serial.println(LEDS_PER_COLUMN - offsetValue - 1 + (60 *modulePosition));

  inputLeds[LEDS_PER_COLUMN + offsetValue + (60 * modulePosition)] = RGBProfile;
  //Serial.println(LEDS_PER_COLUMN + offsetValue + (60 * modulePosition));

  inputLeds[LEDS_PER_COLUMN * 3 - 1 + offsetValue + (60 * modulePosition)] = RGBProfile;
  //Serial.println(LEDS_PER_COLUMN * 3 - 1 - offsetValue + (60 * modulePosition));

  FastLED.show();
}

//takes a single digit from a number and displays it on the left acrylic panels of the module
void NixieModule::displaySecondDigit(char numToDisplay, CRGB inputLeds[180]){
  CRGB RGBProfile = mainProfile;
  
  int offsetValue = 0;
  
  if(numToDisplay == 'X'){
    RGBProfile = CRGB(0,0,0);
  }else{
    offsetValue = String(numToDisplay).toInt();
  }

  inputLeds[LEDS_PER_COLUMN + offsetValue + (60 * modulePosition + 20)] = RGBProfile;
  //Serial.println(LEDS_PER_COLUMN + offsetValue + (60 * modulePosition + 20));

  inputLeds[LEDS_PER_COLUMN - offsetValue - 1 + (60 * modulePosition + 40)] = RGBProfile;
  //Serial.println(LEDS_PER_COLUMN - offsetValue - 1 + (60 * modulePosition + 40));

  inputLeds[LEDS_PER_COLUMN * 2 + offsetValue + (60 * modulePosition + 30)] = RGBProfile;
  //Serial.println(LEDS_PER_COLUMN * 2 + offsetValue + (60 * modulePosition + 30));

  FastLED.show();
}


//Use displayDigit methods to display a whole number on the module
void NixieModule::displayNumber(int number, bool showZero, CRGB inputLeds[180]){
  String numAsString = numToString(number, showZero);
  displayFirstDigit(numAsString[0], inputLeds); 
  displaySecondDigit(numAsString[1], inputLeds);
}

