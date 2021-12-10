// BIN-Hourglass Modding
// Blinking LED M1 (BlinkLED.ino)
// In order to select column "M", set the pin to LOW or "0" 
// LOW drives the PNP-transistor, so we get positive voltage
// Column Minute  Arduino-IDE-pin => 7
//                Port-pin        => PD5 set to LOW or binary "0"
//                µP-pin          => 9 
// In order to select LED "1", set the pin to LOW or "0", so we get (GND)
// LED              |  1  |
// Arduino-IDE-pin  |  9   |
// Port-pin         |  PB0 |
// µP-pin           |  12  |

#define Column 7                // column minutes
#define pinLED 9                // LED 1 (H1 / M1 / S1)

void setup() {
  // initialize digital pins as an output
  pinMode(pinLED, OUTPUT);        // sets ATtiny-pins as OUTPUT
  pinMode(Column, OUTPUT);        
  digitalWrite(Column, LOW);      // because of PNP-transistor, the base needs to be LOW
                                  // in order to get led on, thus we get positive voltage
                                  
  // Patch for 8-bit Timer if "Divide clock by 8 (default) is set (Fuses)
  // IF System clock Prescaler is set to 8, we get (clock source 16 MHz) 16/8=2 MHz as System clock
  // We need to set the TIMER0-Prescaler to 8 (default setting is 64)
  TCCR0B = (0 << CS02) | (1 << CS01) | (0 << CS00);
}
 
void loop() {
  digitalWrite(pinLED, LOW);     // connects LED to GND, means LED on
  delay(1000);
  // wait for 1/100 second
  digitalWrite(pinLED, HIGH);    // disconnects LED from GND, that means LED off                   // wait for 1/100 second
  delay(1000);
}
