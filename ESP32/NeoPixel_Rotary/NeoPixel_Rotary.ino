// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch NeoPixel_Rotary.ino 
// Using the Rotary Encoder for adjusting hue-value

// Adafruit NeoPixel library
#include "Adafruit_NeoPixel.h"
#define LED_PIN    13   	// Which pin on the ESP32 is connected to the NeoPixels?
#define LED_COUNT  10 		// How many NeoPixels are attached to the Arduino?

// Instantiate the class to create a NeoPixel strip object (an instance):
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

// Pins of the rotary mapped to ESP32 GPIOs
#define DTpin  32
#define CLKpin 33

// Initial values of hue (tuned by the rotary)
int hueRE = 0, preHueRE = 0;
int sat = 100, value = 100, bright = 20;  // initial values from experience

// Seven states of finite state machine (FSM) for RE
// Index is:     0      1      2      3       4       5       6
enum State { IDLE_11, CW_01, CW_00, CW_10, CCW_10, CCW_00, CCW_01 };

// primary state of FSM for RE
unsigned char state = IDLE_11, oldState;

// function State Machine transitions for CLK level changes
void CLKchange();             // see Tab 1_Rotary
// function State Machine transitions for DT level changes
void DTchange();              // see Tab 1_Rotary

void setup() {
 Serial.begin(115200);
  while(!Serial) {}
  Serial.println("EBW-Workshop");

  // Initialize strip
  strip.begin();           // Initialize NeoPixel strip object (REQUIRED)
  strip.clear(); 				   // Set all pixel colors to 'off'
  strip.show();

   // some user information
  Serial.println("Rotary Encoder starts by 0 and ends by 360");
  Serial.println("Red = 0, Green = 120, Blue = 240, Red = 360");

  // Level HIGH will be default for all pins of TY-040 RE
  pinMode(CLKpin, INPUT);
  pinMode(DTpin,  INPUT);

  // Both CLK and DT will trigger interrupts for all level changes
  attachInterrupt(digitalPinToInterrupt(CLKpin), CLKchange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DTpin),  DTchange, CHANGE); 
}

void loop() {
  // Any change in hue from rotary encoder
  if (hueRE != preHueRE) {
    hueRE = constrain(hueRE, 0, 360);
    preHueRE = hueRE;

    // calling Monitor routine
    LCD_Monitor(hueRE, sat, value, bright);

    // calling NeoPixel routine
    showPixel(hueRE, sat, value, bright);
  }
}
