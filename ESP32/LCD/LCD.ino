// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch LCD.ino 
// setting LCD 16x2 display

// Include library which needs to be installed 
// LiquidCrystal I2C Frank de Brabander
#include <LiquidCrystal_I2C.h>
#define lcdColumns 16
#define lcdRows     2

// create object "lcd()" from class LiquidCrystal_I2C 
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

void setup() {
  Serial.begin(115200);
  while(!Serial) {}
  Serial.println("EBW-Workshop");
  // initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.print("EBW-Workshop");
}

void loop() {
  static byte sec=0;     // variable persists between calls
  delay(1000);
  
  // LCD-Display
  lcd.clear(); 
  lcd.setCursor(0, 0);  lcd.print("Seconds:");
  lcd.setCursor(9, 1);  lcd.print(sec++);
  if (sec >= 60) sec = 0;
}
