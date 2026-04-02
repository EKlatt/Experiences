// routine for displaying data

void LCD_Monitor(unsigned int _hue, unsigned char _sat, unsigned char _value, unsigned char _bright) {
  // serial monitor output
  Serial.print("hue = "       + String(_hue));
  Serial.print(" sat = "      + String(_sat));
  Serial.print(" value = "    + String(_value));
  Serial.println(" bright = " + String(_bright));   
}
 
