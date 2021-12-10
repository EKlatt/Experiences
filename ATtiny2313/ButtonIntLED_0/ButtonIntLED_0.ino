// BIN-Hourglass Modding
// Button LED M1 (ButtonLED_0.ino)
// In order to select column "M", set the pin to LOW or "0" 
// LOW drives the PNP-transistor, so we get positive voltage
// Column Minute  Arduino-IDE-pin => 7
//                Port-pin        => PD5 set to LOW or binary "0"
//                µP-pin          => 9 

// In order to select LED "M", set the pin to LOW or "0", so we get (GND)
// LED              |  1  |
// Arduino-IDE-pin  |  9   |
// Port-pin         |  PB0 |
// µP-pin           |  12  |

// In order to get pressed button "Minute" from interrupt INT1
// Button           | Minute |
// Interrupt        |  INT1  |
// Arduino-IDE-pin  |   5    |
// Port-pin         |   PD3  |
// µP-pin           |   7    |

#define Column 7                // column minutes
#define pinLED 9                // LED 1 (H1 / M1 / S1)
#define pinButton 5             // Button Minute

volatile boolean int1_occured = false;     // we got an interrupt, do something in loop()
volatile unsigned long lastTime = 0;
volatile unsigned long debounceTime = 20;

void setup() {
  // initialize digital pins as an OUTPU.
  pinMode(pinLED, OUTPUT);              // sets LED-Pin as OUTPUT
  pinMode(Column, OUTPUT);              // sets Column-Pin as OUTPUT
  pinMode(pinButton,INPUT_PULLUP);      // Set Pullup, thus PD2 and PD3 have 5 V
                                        // the button is connected to GND
                                        // defining ISR for pinButton and falling edge
  attachInterrupt(digitalPinToInterrupt(pinButton), int1_routine, FALLING);

  digitalWrite(Column, LOW);            // because of PNP-transistor, the base needs to be LOW
                                        // in order to get LED on, thus we get positive voltage
  digitalWrite(pinLED, HIGH);           // at reboot LED off
}
 
void loop() {
  if (int1_occured){
    digitalWrite(pinLED, !digitalRead(pinLED));     // get status of LED and toggle it
    int1_occured = false;    
  }
}

// Interrupt service routine (ISR) for interrupt "INT1"
void int1_routine() {
  if((millis() - lastTime) > debounceTime) {        // do nothing during debouncing time 
    lastTime = millis();                            // store last buttontick 
    int1_occured = true;                            // set message for loop()     
  }
}
