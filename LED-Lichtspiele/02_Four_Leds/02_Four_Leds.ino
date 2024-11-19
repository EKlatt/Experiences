// EBW: 02_Four_Leds.ino

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
  FastLED.setBrightness(BRIGHTNESS);    // overall setting of brightness
  // https://www.w3schools.com/colors/colors_names.asp 
  // set color via any named HTML web color
  leds[0]  = CRGB::Magenta;
    // unusual command for beginners
    // CRGB is a structure where Magenta is defined as "Magenta = 0xFF00FF"
    // the alternative would be
  // leds[1]  = 0xFF00FF; 
  leds[7]  = CRGB::RoyalBlue;
  leds[48] = CRGB::SpringGreen;
  leds[55] = CRGB::Yellow; 
   
  FastLED.show();   // sends data-set to LED-strip      
}
