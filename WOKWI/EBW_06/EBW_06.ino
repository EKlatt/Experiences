#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x27
#define LCD_COLUMNS 16
#define LCD_LINES   2

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);
void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();  

  // Print something
  lcd.setCursor(0, 0);
  lcd.print("Hallo EBW");
  lcd.setCursor(0, 1);
  lcd.print("Wokwi Online IoT");
}

void loop() {
  // put your main code here, to run repeatedly:

} 

