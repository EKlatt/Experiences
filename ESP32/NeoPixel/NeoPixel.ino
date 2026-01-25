// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch NeoPixel.ino 
// Control an NeoPixel-Strip
// https://github.com/adafruit/Adafruit_NeoPixel
// https://learn.adafruit.com/adafruit-neopixel-uberguide/
// https://adafruit.github.io/Adafruit_NeoPixel/html/class_adafruit___neo_pixel.html
// https://www.w3schools.com/colors/default.asp
// https://www.w3schools.com/colors/colors_rgb.asp
// https://colordesigner.io/convert/rgbtohsv

// First of all checking the order of red, green and blue
// Try NEO_GRB, NEO_RGB, NEO_RGBW, NEO_GRBW when creating strip-object

// Adafruit NeoPixel library
#include "Adafruit_NeoPixel.h"

#define LED_PIN    13   	// Which pin on the ESP32 is connected to the NeoPixels?
#define LED_COUNT  10 		// How many NeoPixels are attached to the Arduino?

// Instantiate the class to create a NeoPixel strip object (an instance):
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

//   Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_GRBW    Pixels are wired for GRBW bitstream (NeoPixel GRBW products)

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
    // We use RGB color values, the intensity as parameter from 0 to 255  
    // strip.setPixelColor(0, red, green, blue);
    // strip.setPixelColor(0, red, green, blue, white); // may be used, because we have NEO_GRBW
    // the first parameter is the LED-address starting with 0, up to 9 (10 LEDs)
    strip.setPixelColor(0, 255,   0,   0); // red
    strip.setPixelColor(1,   0, 255,   0); // green
    strip.setPixelColor(2,   0,   0, 255); // blue   
    strip.setPixelColor(3, 255, 255,   0); // yellow
    strip.setPixelColor(4,   0, 255, 255); // cyan

    strip.setPixelColor(5, 255, 128,   0); // orange
    strip.setPixelColor(6, 128, 255,   0); // Glasgrün
    strip.setPixelColor(7,   0, 191, 255); // Blaucyan
    strip.setPixelColor(8, 255,   0, 128); // Blaurot 
    strip.setPixelColor(9, 128, 128, 128); // Grau 

    // strip.fill(strip.Color(255, 0, 0)); // alternative for all LEDs with one color

    done = true;
    Serial.println("Fertig");
  }  
  strip.show();  
}
