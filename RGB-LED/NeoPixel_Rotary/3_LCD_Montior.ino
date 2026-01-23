// routine for displaying data

void LCD_Monitor(unsigned int _hue, unsigned char _sat, unsigned char _value, unsigned char _bright) {
  // serial monitor output
  Serial.print("hue = "       + String(_hue));
  Serial.print(" sat = "      + String(_sat));
  Serial.print(" value = "    + String(_value));
  Serial.println(" bright = " + String(_bright));
  
  // LCD-Display
  lcd.clear();
  
  lcd.setCursor(0, 0);  lcd.print('h');
  lcd.setCursor(4, 0);  lcd.print('s');
  lcd.setCursor(8, 0);  lcd.print('v');
  lcd.setCursor(12, 0); lcd.print('b');
  
  lcd.setCursor(0, 1);  lcd.print(_hue);
  lcd.setCursor(4, 1);  lcd.print(_sat);
  lcd.setCursor(8, 1);  lcd.print(_value);
  lcd.setCursor(12, 1); lcd.print(_bright);      
}
 
