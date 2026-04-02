// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch NeoPixel_HSV.ino 

// https://github.com/adafruit/Adafruit_NeoPixel
// https://learn.adafruit.com/adafruit-neopixel-uberguide/
// https://adafruit.github.io/Adafruit_NeoPixel/html/class_adafruit___neo_pixel.html
// https://www.w3schools.com/colors/default.asp
// https://www.w3schools.com/colors/colors_rgb.asp
// https://colordesigner.io/convert/rgbtohsv

// Adafruit NeoPixel library
#include "Adafruit_NeoPixel.h"

#define LED_PIN    13   	// Which pin on the ESP32 is connected to the NeoPixels?
#define LED_COUNT  10 		// How many NeoPixels are attached to the Arduino?

// Instantiate the class to create a NeoPixel strip object (an instance):
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  while(!Serial) {}
  Serial.println("EBW-Workshop");

  // Initialize strip
  strip.begin();           // Initialize NeoPixel strip object (REQUIRED)
  strip.clear(); 				   // Set all pixel colors to 'off'
  strip.setBrightness(10); // Sets overall brightness: (0 to 255), value 10 leads to 30 mA

  strip.show();            // send previous settings to strip
}

void loop() {
  static bool done = false;       // following code shell be executed once
  if (!done) {
    // We use HSV Color modell
    // With Hue-values for the color: range from 0° up to 360° 
    // With saturation-value: range from 0 to 100 %
    // With 'value': range from 0 to 100 %
    // Adafruit uses defferent ranges
    // Hue-values for the color: range from 0° up to 65535° 
    // With saturation-value: range from 0 to 255
    // With 'value': range from 0 to 255

    // First we calculate a ColorHSV Value: strip.ColorHSV(hue_value, sat_value, value_value))
    // Secondly we use method setPixelColor( address, CalorHSV) do define color of a LED

    unsigned int  hue;
    unsigned char sat;
    unsigned char value;
    unsigned int Color;

    hue    = (65535.0/360.0 * 0);        // red = 0
    sat    = 255;
    value  = 255;

    Color = strip.ColorHSV(hue, sat, value);
    strip.setPixelColor(0, Color);

    hue    = (65535.0/360.0 * 120);                      // green=120
    Color = strip.ColorHSV(hue, sat, value);
    strip.setPixelColor(1, Color);

    hue    = (65535.0/360.0 * 240);                      // blue=240
    Color = strip.ColorHSV(hue, sat, value);
    strip.setPixelColor(2, Color);

    done = true;
    Serial.println("Fertig");
  }  
  strip.show();  
}
