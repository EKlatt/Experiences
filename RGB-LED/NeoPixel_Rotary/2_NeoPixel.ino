// show the data on LED-strip
// routine calculates hsv-values from rotary-value or serial input and shows them on strip

void showPixel(unsigned int _hue, unsigned char _sat, unsigned char _value, unsigned char _bright) { 
  unsigned int  hue_value    = (65535.0/360.0 * _hue);   // light red=0, light green=120, light blue=240
  unsigned char sat_value    = (255.0/100.0   * _sat);   // saturation: 0-100 converted to 0-255 
  unsigned char value_value  = (255.0/100.0   * _value); // value:  0–100 converted to 0-255
  unsigned char bright_value = _bright;
  
  unsigned int _pastelColor = strip.gamma32(strip.ColorHSV(hue_value, sat_value, value_value));   // gamma32 is mandatory
  strip.setBrightness(bright_value);      
  strip.fill(_pastelColor);                                          // fill strip uniform with a color
  strip.show();  
} 
