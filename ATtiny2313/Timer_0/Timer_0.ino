// BIN-Hourglass Modding
// https://eleccelerator.com/avr-timer-calculator/
// http://elektronik-kompendium.de/public/arnerossius/programme/web/avrfuse/
// https://www.mikrocontroller.net/articles/AVR-GCC-Tutorial/Die_Timer_und_Z%C3%A4hler_des_AVR
// Blinking LED M1 (Timer_o.ino)
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

#define F_CPU 2000000UL
#define OCRIA_    31250         // external oszillator with 16 MHz and a predifined devider of 8
                                // the System clock runs with 16/8 = 2 MHz.
                                // delivered with internal oszillator with 8 MHz and a predifined devider of 8
                                // the System clock runs with 8/8 = 1 MHz.                                  
#define Column 7                // column minutes
#define pinLED 9                // LED 1 (H1 / M1 / S1)
#define pinButton 5             // Button Minute

volatile boolean int1_occured = false;     // we got an interrupt, do something in loop()

void setup() {
  // set port-pins to OUTPUT
  DDRD  = 0b01110000;   // pins for columns h=>PD4, m=>PD5, s=>PD6 as Output
  DDRB  = 0b11111111;   // pins for LEDs PB0 to PB7 as Output

  // enables (LOW) column minutes
  PORTD = 0b11101111;   // because of PNP-transistor, the base needs to be LOW
                        // in order to get LED on, thus we get positive voltage
  // sets all LEDs off
  PORTB = 0b11111111;
  initTimer();          // init Timer 1
}
 
void loop() {
  if (int1_occured){
    PORTB ^= (1 << PB0);                      // toggle PB0
    int1_occured = false;    
  }
}

// timer interrupt service routine
ISR(TIMER1_COMPA_vect)        
{  
  int1_occured = true;
}

void initTimer(){
  // Timer 1
  cli();                                 // deactivate all interrupts
  TCNT1 = 0;                             // set counter to 0     
  OCR1A = OCRIA_;                        // set Output Compare Register 1A
                                         // 2 MHZ;  compare value = 31250
                                         // leads to interrupts each second
  TCCR1B  = (1 << CS10) | (1 << CS11);   // prescale 64
  TCCR1B |= (1 << WGM12);                // CTC mode; resets TCNT1 at overflow
  TIMSK   = (1 << OCIE1A);               // Compare A Match Interrupt Enable
  sei();                                 // activate all interrupts  
}
