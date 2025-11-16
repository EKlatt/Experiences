// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch LDR_ADC.ino 
// Attention: Never supply potentiometer with a volatage higher than 3.3 V
//            Never change the attenuation: default "ADC_11db"
// the ADC has a 12 bit resolution from 0 to 4095 (2^12-1)

// setting LCD 16x2 display
#include <LiquidCrystal_I2C.h>
#define lcdColumns 16
#define lcdRows     2
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

#define ldrPin 35  // ESP32 pin GPIO35 (ADC1-7) connected to LDR

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
  // reads the input from analog pin A0 (value between 0 and 4095)
  short analogValue = analogRead(ldrPin);

  // the analogRead() values for 12 bit resolution have a range between 0 to 4095
  // scale LDR-values to led-brightness: % value between 0 and 100
  short brightness = map(analogValue, 0, 4095, 0, 100);  

  lcd.clear(); 
  lcd.setCursor(0, 0);  lcd.print("LDR:");
  lcd.setCursor(6, 1);  lcd.print(brightness);
  delay(500);  
}
