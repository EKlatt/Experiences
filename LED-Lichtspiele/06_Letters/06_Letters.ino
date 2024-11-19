// EBW: 05_Letters.ino

// Library for digital LED-strip
// https://github.com/FastLED/FastLED
// https://github.com/FastLED/FastLED/wiki/Overview
// https://github.com/FastLED/FastLED/wiki/Basic-usage
// https://github.com/FastLED/FastLED/wiki/Pixel-reference

// including the previous installed library
#include <FastLED.h>
#include "pattern.h"         // my own pattern-library

#define DATA_PIN   (13)      // microcontroller-pin for data
#define NUM_LEDS   (56)      // number of leds
#define BRIGHTNESS (50)      // a way to control brightness for all leds: 25->255
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

// set up a block of memory as an array
// this means e.g. leds[12] is the address where led-data are stored
CRGB leds[NUM_LEDS];             // define an array of leds

// pattern of adresses
byte address[8][7]={
  {7,  8, 23, 24, 39, 40, 55},
  {6,  9, 22, 25, 38, 41, 54},
  {5, 10, 21, 26, 37, 42, 53},
  {4, 11, 20, 27, 36, 43, 52},
  {3, 12, 19, 28, 35, 44, 51},
  {2, 13, 18, 29, 34, 45, 50},
  {1, 14, 17, 30, 33, 46, 49},
  {0, 15, 16, 31, 32, 47, 48}
};  

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
}

void loop() {
  FastLED.clear();
  FastLED.setBrightness(BRIGHTNESS);
  // build(tree); delay(5000);
  build(E); delay(2000); FastLED.clear();
  build(N); delay(2000); FastLED.clear();
  build(blank); delay(1000); FastLED.clear();
  build(N); delay(2000); FastLED.clear();
  build(O); delay(2000);            
}

// build the display according to the pattern
void build(byte arr[8][7]){               // I pass the name of the array-pattern to function array "arr"
  // start with line one
  for (int line = 0; line < 8; line++){
    // for line one step through the columns of the line
    for (int col = 0; col < 7; col++){
      // has e.g. the tree-array (here arr) a "1" then get the address
      // and set the led with the appropriate led-address
      int led_address;
      if ( arr[line][col] == 1 ) {
        led_address = address[line][col];
        leds[led_address] = CRGB::Green;
      }
    }
    FastLED.show();
  }  
}
