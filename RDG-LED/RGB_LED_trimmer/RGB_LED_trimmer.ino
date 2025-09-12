// AATIS: RGB_LED_calibration.ino
// The colors of an LED have different intensieties of light, 
// so we need to calibrate them

// https://malen-lernen.org/pastellfarben/
// https://www.rapidtables.com/convert/color/index.html

// setting LCD 16x2 display
#include <LiquidCrystal_I2C.h>
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

int redPin = 9,      greenPin = 10,     bluePin = 11;                          // Arduino-Pin PWM to potentiometer-calibration
int multiPlexPin = A0;                                                         // potentiometer-RGB-values to Arduino-Pin analog
int redPoti,         greenPoti,         bluePoti,         brightPoti;          // RGB-values readed from analog-Pin and mapped
int redPotiOld,      greenPotiOld,      bluePotiOld,      brightPotiOld;       // last readed RB-values
int redPotiCal,      greenPotiCal,      bluePotiCal;                           // RGB-calibrate-values readed from analog-Pin and mapped
int redPotiCalOld,   greenPotiCalOld,   bluePotiCalOld;                        // last readed RGB-calibrate-values


 void setup() {
  Serial.begin(57600);
  lcd.init();                                                      // initialize LCD                 
  lcd.backlight();                                                 // turn on LCD backlight  
  pinMode(redPin, OUTPUT);                                         // initializing PWM-pins to OUTPUT
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  setupMulti();                                                    // calls function in Multiplexer.ino   
 }

void loop() {
  loopMulti();                                                     // get potivalues from Multiplexer

  if (redPoti     != redPotiOld    || greenPoti    != greenPotiOld ||   // comparing with last values to encounter change
      bluePoti    != bluePotiOld   || brightPoti   != brightPotiOld ||
      redPotiCal  != redPotiCalOld || greenPotiCal != greenPotiCalOld ||
      bluePotiCal != bluePotiCalOld ) {
                
    redPotiOld      = redPoti;                                      // remember last potentiometer-value
    greenPotiOld    = greenPoti;
    bluePotiOld     = bluePoti;
    brightPotiOld   = brightPoti;
    redPotiCalOld   = redPotiCal;
    greenPotiCalOld = greenPotiCal;
    bluePotiCalOld  = bluePotiCal; 
       
    redPoti      = map(redPoti,      0, 1023, 0, 255);               // mapping from potentiometer-values to range 0-255
    greenPoti    = map(greenPoti,    0, 1023, 0, 255);
    bluePoti     = map(bluePoti,     0, 1023, 0, 255);
    brightPoti   = map(brightPoti,   0, 1023, 0, 100);               // mapping from potentiometer-values to range 0-100
    redPotiCal   = map(redPotiCal,   0, 1023, 0, 100);
    greenPotiCal = map(greenPotiCal, 0, 1023, 0, 100);    
    bluePotiCal  = map(bluePotiCal,  0, 1023, 0, 100);

    lcd.clear();
    lcd.setCursor(0, 0);  lcd.print(brightPoti);
    lcd.setCursor(5, 0);  lcd.print(redPoti);
    lcd.setCursor(9, 0);  lcd.print(greenPoti);
    lcd.setCursor(13, 0); lcd.print(bluePoti);
    
    lcd.setCursor(5, 1);  lcd.print(redPotiCal);
    lcd.setCursor(9, 1);  lcd.print(greenPotiCal);
    lcd.setCursor(13, 1); lcd.print(bluePotiCal);    

//    Serial.print  ("red cal:  "    + String(redPotiCal));
//    Serial.print  (" green cal:  " + String(greenPotiCal));  
//    Serial.print  (" blue cal:   " + String(bluePotiCal));       
//    Serial.print  (" red:  "       + String(redPoti));
//    Serial.print  (" green:  "     + String(greenPoti));  
//    Serial.print  (" blue:  "      + String(bluePoti));
//    Serial.println(" bright:  "    + String(brightPoti));
 
    redPoti   =  redPoti   * redPotiCal/100.0;                      // calibrate LED-value
    greenPoti =  greenPoti * greenPotiCal/100.0;
    bluePoti  =  bluePoti  * bluePotiCal/100.0;
     
    redPoti   =  redPoti   * brightPoti/100.0;                      // correct LED-value with brightness 
    greenPoti =  greenPoti * brightPoti/100.0;
    bluePoti  =  bluePoti  * brightPoti/100.0;
               
    analogWrite (redPin,   redPoti);                                // writing to PWM-Pin
    analogWrite (greenPin, greenPoti);
    analogWrite (bluePin,  bluePoti);
  }
  delay(200);  
}
