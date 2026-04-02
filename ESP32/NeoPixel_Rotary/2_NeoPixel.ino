// show the data on NeoPixel-strip
// routine calculates hsv-values from rotary and shows on strip

void showPixel(unsigned int _hue, unsigned char _sat, unsigned char _value, unsigned char _bright) { 
  unsigned int  hue_value    = (65535.0/360.0 * _hue);   // red=0, green=120, blue=240
  unsigned char sat_value    = (255.0/100.0   * _sat);   // saturation: 0-100 converted to 0-255 
  unsigned char value_value  = (255.0/100.0   * _value); // value:  0–100 converted to 0-255
  
  //unsigned int _Color = strip.gamma32(strip.ColorHSV(hue_value, sat_value, value_value));   // gamma32 is mandatory
  unsigned int _Color = strip.ColorHSV(hue_value, sat_value, value_value);
  strip.setBrightness(_bright);      
  strip.fill(_Color);                                          // fill strip uniform with a color
  strip.show();  
} 
