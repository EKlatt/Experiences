// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch LCD.ino 
// Control an LED with a MOSFET
// setting LCD 16x2 display

#include <LiquidCrystal_I2C.h>
#define lcdColumns 16
#define lcdRows     2
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

void setup() {
  // put your setup code here, to run once:

  // initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.print("EBW");
}

void loop() {
  // put your main code here, to run repeatedly:
  static int sec=0;
  delay(1000);
  
  // LCD-Display
  lcd.clear(); 
  lcd.setCursor(0, 0);  lcd.print("Seconds:");
  lcd.setCursor(9, 1);  lcd.print(sec++);
  if (sec >= 60) sec = 0;
}
