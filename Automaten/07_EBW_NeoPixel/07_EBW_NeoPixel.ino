// EBW 07_EBW_NeoPixel.ino
// EBW-code with two ISR-routines
// controlling NeoPixel-Strip
// message on LCD
// Pins of the rotary mapped to Arduino R4 ports
#define DTpin  2
#define CLKpin 3

// setting LCD 16x2 display
#include <LiquidCrystal_I2C.h>
int lcdColumns = 16;
int lcdRows    = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

// including the NeoPixel-library
#include <Adafruit_NeoPixel.h>

// NeoPixel
#define LED_PIN    6                // Which pin on the UNO R4 is connected to the NeoPixels?
#define LED_COUNT  4                // How many NeoPixels are attached to the Nano?

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to be used
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Current and previous value of the counter tuned by the rotary
int count    = 0;
int preCount = 0;

// Seven states of FSM (finite state machine)
//          0        1      2      3      4       5       6 
enum State {IDLE_11, CW_01, CW_00, CW_10, CCW_10, CCW_00, CCW_01};

int  state = IDLE_11;
int  oldState;

// State Machine transitions for CLK level changes
void CLKchange() {
  oldState = state;
  int CLK = digitalRead(CLKpin);
  if      ( CLK==LOW  && state==IDLE_11 ) state=CW_01;
  else if ( CLK==LOW  && state==CCW_10 )  state=CCW_00;
  else if ( CLK==HIGH && state==CW_00 )   state=CW_10;
  else if ( CLK==HIGH && state==CCW_01 )  {state=IDLE_11; count--;}
}

void DTchange() {
  oldState = state;
  int DT  = digitalRead(DTpin);
  if      ( DT==LOW  && state==IDLE_11 ) state=CCW_10;
  else if ( DT==LOW  && state==CW_01 )   state=CW_00;
  else if ( DT==HIGH && state==CCW_00 )  state=CCW_01;
  else if ( DT==HIGH && state==CW_10 )   {state=IDLE_11; count++;}
}

void setup() {
  Serial.begin(57600);
  lcd.init();                       // initialize LCD                 
  lcd.backlight();                  // turn on LCD backlight  
  Serial.println("Start...");
  lcd.setCursor(0, 0);  lcd.print("EBW");
  strip.begin();
  strip.show();         // Initialize all pixels to 'off'
  strip.clear();
  
  // Level HIGH will be default for all pins
  pinMode(CLKpin, INPUT_PULLUP);
  pinMode(DTpin,  INPUT_PULLUP);
  
  // Both CLK and DT will trigges interrupts for all level changes
  attachInterrupt(digitalPinToInterrupt(CLKpin), CLKchange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DTpin),  DTchange,  CHANGE);
}

void loop() {
  // Any change in counter value is displayed in Serial Monitor
  if (count != preCount) {
    if (count <=1)   count = 1;
    if (count >=360) count = 360;
    Serial.println("HUE= " + String(count));
    preCount = count;
    showPixel(count); 
  }
}

// function calculates hsv-values from rotary-values and shows on strip
void showPixel(unsigned int _hue ) { 
  unsigned int  hue_value    = (65535.0/360.0 * _hue);   // leight red=0, leight green=120, leight blue=240
  unsigned char sat_value    = (255.0/100.0 * 70);       // saturation: 0-100 converted to 0-255 (test 70)
  unsigned char light_value  = (255.0/100.0 * 50);       // lightness:  0–100 converted to 0-255 (test 50)
  unsigned char bright_value = 20;
  
  unsigned int _pastelColor = strip.ColorHSV(hue_value, sat_value, light_value);
  strip.setBrightness(bright_value);      
  strip.fill(_pastelColor);                                                   // fill panel uniform with a color
  strip.show();

  lcd.clear();
  lcd.setCursor(0, 0);  lcd.print("HUE: ");
  lcd.setCursor(5, 0);  lcd.print(_hue);    
}  
