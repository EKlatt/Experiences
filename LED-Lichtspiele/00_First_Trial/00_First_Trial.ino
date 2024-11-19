// EBW: 00_First_Trial.ino

// including the previous installed library
#include <FastLED.h>

#define DATA_PIN   (13)               // replace number with your Arduino-Pin
#define NUM_LEDS   (4)                // replace number with your number of leds
#define LED_TYPE    WS2812B           // replace Type with your present type
#define COLOR_ORDER GRB

// ----------------------------------nothing to change-------------------------------
// set up a block of memory as an array
// this means e.g. leds[12] is the address where led-data are stored
CRGB leds[NUM_LEDS];                  // define an array of leds

void setup() {
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay(2000);
  Serial.begin(9600);                 // setup serial monitor for messages
  Serial.println("EBW Ready to go!"); 

  // initialize FastLED-library   
  // possible types in my case: WS2812B, NEOPIXEL
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);  

  FastLED.setBrightness(50);          // overall setting of brightness        
}
// ----------------------------------end of nothing to change------------------------

void loop() {
  FastLED.clear();                    // clear the data-package  
  delay(500);
   
  // https://www.w3schools.com/colors/colors_names.asp 
  // set color via any named HTML web color
  leds[0] = CRGB::Magenta;    delay(200); FastLED.show();
  leds[1] = CRGB::RoyalBlue;  delay(200); FastLED.show(); 
  leds[2] = CRGB::Green ;     delay(200); FastLED.show(); 
  leds[3] = CRGB::Yellow;     delay(200); FastLED.show();
  leds[3] = CRGB::Black;      delay(200); FastLED.show();
  leds[2] = CRGB::Black;      delay(200); FastLED.show(); 
  leds[1] = CRGB::Black ;     delay(200); FastLED.show(); 
  leds[0] = CRGB::Black;      delay(200); FastLED.show();   
}
