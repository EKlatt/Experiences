// AAtis_NeoPixel_Rotary.ino
// for further details see Tab Info.h

// Pins of the rotary mapped to Arduino R4 ports
#define DTpin  2
#define CLKpin 3

// setting LCD 16x2 display
#include <LiquidCrystal_I2C.h>
#define lcdColumns 16
#define lcdRows     2
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

// including the NeoPixel-library
#include <Adafruit_NeoPixel.h>

// NeoPixel
#define LED_PIN  12  // Which pin on the UNO R4 is connected to the NeoPixels?
#define LED_COUNT 4  // How many NeoPixels are attached to the Nano?

// setting up the NeoPixel library
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Initial values of hue (tuned by the rotary), saturation, value, brightness
int hue = 0, hueRE = 0, preHueRE = 0;
int sat = 30, value = 50, bright = 14;  // initial values from experience

// Seven states of finite state machine (FSM) for RE
// Index are:  0        1      2      3      4       5       6
enum State { IDLE_11,
             CW_01,
             CW_00,
             CW_10,
             CCW_10,
             CCW_00,
             CCW_01 };

// primary state of FSM for RE
unsigned char state = IDLE_11, oldState;

// Variables for serial input
char controlLetter  = 'n';    // control letter s, l, b, n means nothing
int controlValue    = 0;      // values depend on ColorHSV() function
String strCommand;
bool serialComplete = false;  // flag for loop() serial input is complete
bool newParameter   = false;  // flag for loop() new parameter present

// function State Machine transitions for CLK level changes
void CLKchange();             // see Tab 1_Rotary
// function State Machine transitions for DT level changes
void DTchange();              // see Tab 1_Rotary

void setup() {
  Serial.begin(57600);
  while(!Serial) {}           // Warte, bis der serielle Monitor verbunden ist

  Serial.println("AAtis");

  // initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.print("EBW");

  // initialize strip
  strip.begin();
  strip.show();              // Initialize all pixels to 'off'
  strip.clear();

  // some user information
  Serial.println("Monitor commands e.g.: 'b:20' or 'h:200' or 's:30' or 'v:50'");
  Serial.println("'Values for h beteeen 0-360' and 'values for b, S, v between 0 to 100'");

  // Level HIGH will be default for all pins of TY-040 RE
  pinMode(CLKpin, INPUT);
  pinMode(DTpin,  INPUT);

  // Both CLK and DT will trigger interrupts for all level changes
  attachInterrupt(digitalPinToInterrupt(CLKpin), CLKchange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DTpin),  DTchange, CHANGE);
}

void loop() {
  // looking for data in serial input
  serialData();                       // when data are available: flag serialComplete is set

  // processing serial input
  if (serialComplete) processData();  // get the command letter and perform action from it

  // values are set in general from serial input and also from rotary encoder
  // Any change in hue from rotary encoder
  if (hueRE != preHueRE) {
    hueRE = constrain(hueRE, 0, 360);
    preHueRE = hueRE;

    // calling LCD-Display and Monitor routine
    LCD_Monitor(hueRE, sat, value, bright);

    // calling NeoPixel routine
    showPixel(hueRE, sat, value, bright);
  }

  // function processData() sets the flag newParameter
  if (newParameter) {

    // calling LCD-Display and Monitor routine
    LCD_Monitor(hue, sat, value, bright);

    // calling NeoPixel routine
    showPixel(hue, sat, value, bright);

    // telling Rotary Encoder that we have a new hue-value from serial input
    hueRE = hue;
    newParameter = false;
  }
}
