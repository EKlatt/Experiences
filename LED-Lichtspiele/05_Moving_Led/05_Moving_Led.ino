// EBW: 05_Moving_Led.ino
// Move a white dot along the strip of leds.  This program simply shows how to configure the leds,
// and then how to turn a single pixel white and then off, moving down the line of pixels.

// Library for digital LED-strip:
// https://github.com/FastLED/FastLED
// https://github.com/FastLED/FastLED/wiki/Overview
// https://github.com/FastLED/FastLED/wiki/Basic-usage
// https://github.com/FastLED/FastLED/wiki/Pixel-reference

// including the previous installed library
#include <FastLED.h>

#define DATA_PIN   (13)      // microcontroller-pin for data
#define NUM_LEDS   (56)      // number of leds
#define BRIGHTNESS (30)      // a way to control brightness for all leds: 25->255
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

// set up a block of memory as an array
// this means e.g. leds[12] is the address where led-data are stored
CRGB leds[NUM_LEDS];             // define an array of leds

// This function sets up the leds 
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
    FastLED.setBrightness(BRIGHTNESS);
}

void loop() { 
  // Move a single light forward
  for(int myLed = 0; myLed < NUM_LEDS; myLed++) {
    // Turn our current led on to Blue, then show the leds
    leds[myLed] = CRGB::Blue;
  
    FastLED.show();      // Show the leds
    delay(200);          // Wait a little bit
  
    // Turn our current led back to black for the next loop around
    leds[myLed] = CRGB::Black;
  }
  // Move a single light backword
  for(int myLed = NUM_LEDS - 1; myLed > 0; myLed--) {
    // Turn our current led on to Blue, then show the leds
    leds[myLed] = CRGB::Yellow;
  
    FastLED.show();      // Show the leds
    delay(200);          // Wait a little bit
  
    // Turn our current led back to black for the next loop around
    leds[myLed] = CRGB::Black;
  }
}
