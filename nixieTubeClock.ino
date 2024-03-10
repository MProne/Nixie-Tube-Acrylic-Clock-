//declare libaries
#include "Arduino.h"
#include "RTClib.h"
#include "FastLED.h"
#include "NixieModule.h"
//RGB constants
#define RGB_DATA_PIN 2
#define NUM_LEDS 180

//create objects
DateTime setTime;
RTC_DS3231 rtcModule;
CRGB leds[NUM_LEDS];




NixieModule hourModule;
NixieModule minuteModule;
NixieModule secondModule;

void setup() {


  Serial.begin(9600);
  //give program a little bit of time to open the serial port
  delay(2000);

  //begin RGBS and each acrylic nixie tube module
  FastLED.addLeds<WS2812B, RGB_DATA_PIN, GRB>(leds, NUM_LEDS);
  
  hourModule.begin(0);
  minuteModule.begin(1);
  secondModule.begin(2);

  //if unable to connect to RTC module, display red on all RGB LEDs
  if(!rtcModule.begin()){
    FastLED.showColor(CRGB::Red);
    while(true);
  }
 



}

void loop() {
  
  //add delay so its not rapidly checking quickly
  delay(250);
  secondModule.displayNumber(getCurrentSecond(), true, leds);
  
  //check the minute every time the seconds get reset back to 0
  if(getCurrentSecond() == 0){
    minuteModule.displayNumber(getCurrentMinute(), true, leds);
  }
  
  //check the hour every time the minute gets reset back to 0
  if(getCurrentMinute() == 0){
    hourModule.displayNumber(getCurrentHour(), true, leds);
  }

}

int getCurrentHour(){
  return rtcModule.now().hour();
}

int getCurrentMinute(){
  return rtcModule.now().minute();
}

int getCurrentSecond(){
  return rtcModule.now().second();
}