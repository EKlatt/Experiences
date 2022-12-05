// Anmerkung: Funktioniert auch wenn DDRD nicht gesetzt; PIND liefert falschen Wert
#define UsedPin PD2

void setup(){
  Serial.begin(9600);
  DDRD |= (1 << UsedPin);           // make PDx an output, changes only PDx
  // DDRD |= 0b00000100;            // Binary
  // DDRD |= 0x04;                  // Hex number  
  printBits("DDRD ", DDRD);         // Monitor information

  PORTD = (1 << UsedPin);           // PDx on
  printBits("PORTD ", PORTD);
  printBits("PIND",PIND);
}

void loop(){
    _delay_ms(1000);                // AVR function
    PORTD ^= (1 << UsedPin);        // toggle PDx
    _delay_ms(1000);                // AVR function
}

// a function used for debugging
void printBits(String _msg, byte b)
{
  Serial.println(_msg);
  Serial.println("76543210");
  for (int i = 7; i >= 0; i--) Serial.print(bitRead(b, i));
  Serial.println();
  Serial.flush();
}

