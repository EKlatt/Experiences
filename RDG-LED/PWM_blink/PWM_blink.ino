// AATIS: PWM_blink.ino
// generating a PWM signel from scratch
// using micros() and digitalWrite
// the dutyCyle given in percent controls the intensity of the LED
// https://www.thegeekpub.com/277872/arduino-rgb-led-tutorial/?srsltid=AfmBOorMQ5dd68xAXOhbqzmmK1JuAGU6cT_Vr6nJoZgDTCirIcnx3Bp-

#define REDPIN  (9)                      // PWM output pin
#define FREQ    (490)                    // Frequenz f = 490 Hz (1/s)
                                         // PERIODE duration in microseconds (2000 µs) µ = 10^(-6)
                                         // T = 1/f in seconds T = 1/500 seconds
                                         // conversion from seconds to microseconds (us)
#define PERIODE  (1.0/FREQ * 1000000)    // 1 / 490 * 1.000.000 = 2.041 us
#define DUTYCYLE (30)                    // Duty cycle in percent (0%-100%)

void setup() {
  // initialize digital pin 9 as an output.
  pinMode(REDPIN, OUTPUT);
}

void loop() {
  int HIGHzeit = (PERIODE * DUTYCYLE) / 100;        // DUTYCYLE = 50 2.041 * 50 / 100 = 1.020; 
  int LOWzeit  = PERIODE - HIGHzeit;                // 2.041 - 1.000    = 1.041
  
  digitalWrite(REDPIN, HIGH);                      // turn the LED on (HIGH means 5 V)
  delayMicroseconds(HIGHzeit);                     // wait for HIGHzeit
  digitalWrite(REDPIN, LOW);                       // turn the LED off (LOW means 0 V)
  delayMicroseconds(LOWzeit);                      // wait for LOWzeit
}
