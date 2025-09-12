// AATIS: PWM_analogwrite.ino
// generating a Arduino-PWM signel
// using analogWrite(pin, dutycycle)
// the dutyCyle given as value between 0-255 controls the intensity of the LED

#define REDPIN  (9)                   // Arduino PWM output pin

void setup() {
}

void loop() {
  // analogWrite(pin, dutycyle)
  // dutycyle: between 0 (always off) and 255 (always on)
  analogWrite(REDPIN, 255/4);         // may be located in setup()
}
