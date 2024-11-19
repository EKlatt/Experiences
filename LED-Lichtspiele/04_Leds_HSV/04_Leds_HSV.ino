// EBW: 04_Leds_HSV.ino

// Library for digital LED-strip
// https://github.com/FastLED/FastLED
// https://github.com/FastLED/FastLED/wiki/Overview
// https://github.com/FastLED/FastLED/wiki/Basic-usage
// https://github.com/FastLED/FastLED/wiki/Pixel-reference

// including the previous installed library
#include <FastLED.h>

#define DATA_PIN   (13)      // microcontroller-pin for data
#define NUM_LEDS   (56)      // number of leds
#define BRIGHTNESS (50)      // a way to control brightness for all leds: 25->255
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

// set up a block of memory as an array
// this means e.g. leds[12] is the address where led-data are stored
CRGB leds[NUM_LEDS];             // define an array of leds
 
void setup() {
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay(2000);
  Serial.begin(9600);                 // setup serial monitor for messages
  Serial.println("EBW Ready to go!"); 

  // initialize FastLED-library   
  // possible types in my case: WS2812B, NEOPIXEL
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);  
      // unusual command for beginners
      // a class-template
      // this tells the library "FastLED" that there's a number of 56 PIXEL's on pin 13   

  // first trial without loop()
  first_trial();                        // calling my function 
}

void loop() {}

void first_trial(){
  // HSV (hue, saturation, value)
  // https://en.wikipedia.org/wiki/HSL_and_HSV
  // https://github.com/FastLED/FastLED/wiki/FastLED-HSV-Colors
  // Hue is the 'angle' around a color wheel.
  // Saturation is how 'rich' (versus pale) the color is.
  // Value is how 'bright' (versus dim) the color is.
  // Differences to FastLED library!
  // In 'traditional' computer HSV color models, 
  // hue is represented as a number (of degrees) from 0-360. 
  // Saturation and value (light) are often represented as numbers (percentages) from 0-100.
  // The FastLED library uses simple one-byte values (from 0-255) for hue, and for saturation, and for value.
  // My own functions for mapping of hue, saturation and light: 
  // map(hue, 0, 360, 0, 255);
  // map(sat, 0, 100, 0, 255); 
  // map(light, 0, 100, 0, 255); 
  // my function.calls with traditional HSV-parameter:
  // hue = myHUE(214);
  // sat = mySAT(100);
  // light = myLIGHT(60); 

  // https://www.w3schools.com/colors/colors_hsl.asp
  // w3-schools color picker: hsl(110, 100%, 60%) light green
  // calling my functions in order to convert from traditional to FastLED
  uint16_t hue   = myHUE(110);      // parameter is traditional value
  uint16_t sat   = mySAT(100);
  uint16_t light = myLIGHT(50);
  leds[10] = CHSV(hue, sat, light); // calling CHSV-function
  
  // alternate syntax
  leds[11].setHSV(hue, sat, light);

  // CHSV light blue 
  // traditional hsl(200, 100%, 60%)                        // light blue
  leds[12] = CHSV( myHUE(200), mySAT(100), myLIGHT(50) );   // mapped to CHSV 

  // CHSV light red 
  // traditional hsl(0, 100%, 60%)                         // light red
  leds[13] = CHSV( myHUE(0), mySAT(100), myLIGHT(50) );    // mapped to CHSV 
                      
  FastLED.show();      
}

// My functions for mapping traditional HSL to CHSV of FastLED
uint16_t myHUE(uint16_t hue)     { return map(hue,   0, 360, 0, 255); }
uint16_t mySAT(uint16_t sat)     { return map(sat,   0, 100, 0, 255); }
uint16_t myLIGHT(uint16_t light) { return map(light, 0, 100, 0, 255); }
