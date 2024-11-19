// EBW: 03_Leds_Basics.ino

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
  // RGB
  // https://www.pixolum.com/blog/fotografie/additive-farbmischung
  // https://en.wikipedia.org/wiki/RGB_color_model
  // https://www.w3schools.com/colors/colors_rgb.asp  
  // only component of RGB is set, this means red/green/blue or r/g/b
  // a one byte value (0-255) representing the amount of channel red.
  // if we refer to channel red, channel green and blue is set to "0"
  leds[0].red   = 1;         // smallest possible amount of red
  leds[1].r     = 50; 
  leds[2]       = CRGB::Red; // defined as "0xFF0000" 
  leds[3].green = 50; 
  leds[4]       = CRGB::Green;
  
  // set color from red, green, and blue components all at once
  leds[5]       = CRGB(0, 0, 100);  // only green component
  
  // set color via 'hex color code', in C++ "0xRRGGBB"
  leds[6] = 0xFF0000;
   
  // set color via any named HTML web color
  leds[7] = CRGB::Gold;             // defined as "0xFFD700" 
  
  // set color via setRGB
  leds[8].setRGB( 50, 100, 150); 

  FastLED.show();      
}
