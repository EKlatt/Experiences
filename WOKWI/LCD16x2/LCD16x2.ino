// LCD1602 to Arduino Uno connection example
/*  The circuit:
 * LCD RS pin to digital pin      8
 * LCD Enable pin to digital pin  9
 * LCD D4 pin to digital pin      A2
 * LCD D5 pin to digital pin      A3
 * LCD D6 pin to digital pin      A4
 * LCD D7 pin to digital pin      A5
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * LCD K to ground
 * 10K resistor:
 * ends to +5V and LCD A
*/


#include <LiquidCrystal.h>
const int rs = 8, en = 9, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  lcd.print("Hallo Welt");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}
