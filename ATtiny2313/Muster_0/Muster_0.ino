// BIN-Hourglass
// http://www.harry-gilbert.de/arduino-bitmanipulation/
// Showing decimal numbers as binay numbers (Muster_0.ino)
// With "Arduino-IDE-pin" I refer to the pins used in e.g. digitalWrite()
// The pins of the Microcontroler (µC) itself are different

// How to set column hour, minute, seconds as selected
// Column Hour    Arduino-IDE-pin => 6
//                µC-pin          => 8
//                port-pin        => PD4 set to LOW or binary "0"

// Column Minute  Arduino-IDE-pin => 7
//                port-pin        => PD5 set to LOW or binary "0"
//                µC-pin          => 9 
// Column Seconds Arduino-IDE-pin => 8
//                port-pin        => PD6 set to LOW or binary "0"
//                µC-pin          => 11 

// LEDs            | LED128 | LED64 | LED32 | LED16 | LED8  | LED4  | LED2  | LED1  | 
// Arduino-IDE-pin |  16    |  15   |  14   |  13   |  12   |  11   |  10   |  9    |
// µC-pin          |  19    |  18   |  17   |  16   |  15   |  14   |  13   |  12   |
// Port-pin        | PB7    | PB6   | PB5   | PB4   | PB3   | PB2   | PB1   | PB0   |
//                 |        |       |       |       |       |       |       |       | 
// This represents | bit 7  | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
// Port B          |        |       |       |       |       |       |       |       | 
// e.g.            |    0   |   0   |   1   |   1   |   0   |   1   |   0   |   0   |
// leads to binary number: 0b00110100

void setup() {
  // set pins to OUTPUT, using binary numbers
  DDRD  = 0b01110000;     // pins for columns h=>PD4, m=>PD5, s=>PD6 as Output
  DDRB  = 0b11111111;     // pins for leds PB0 to PB7 as Output

  // Patch for 8-bit Timer, sets prescaler clkI/O devided by 8
  // only valid if the fuse has the "Divide clock by 8" setting working on the Clock Source 
  TCCR0B = (0 << CS02) | (1 << CS01) | (0 << CS00);   
}

void loop() {
  PORTD = 0b11101111;      // sets column hour, means PD4 LOW (led GND)  
  PORTB = 0b11111111;      // sets all LEDs off

  for (int i=0; i <= 24; i++){
                           // 24 decimal hours => 0b00001100 binary hours
    int set = ~i;          // because of PNP-transistor, base needs to be LOW
                           // in order to get led on
                           // "~" bitwise not)
    PORTB = set;
    delay(1000);
  }
  delay(1000);   
}
