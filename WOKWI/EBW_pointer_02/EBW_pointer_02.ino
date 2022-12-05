// Direct access to PORTs via pointer
#define PINDx 2

uint8_t *MyDDRDadr = 0x0A + 0x20;    // setting the contents of pointer (address)
                                     // to address of DDRD (0x2A)
#define MyDDRD *MyDDRDadr            // defining a preprocessor directive
// shortend to
// #define MyDDRD (*(volatile uint8_t *) 0x2A ) // defining a preprocessor directive 
                                                                            
uint8_t *MyPORTDadr = 0x0B + 0x20;    // changing the contents of pointer (address)
                                      // to address of PORTD 
#define MyPORTD *MyPORTDadr           // defining a preprocessor directive
// shortend to                                                  
// #define MyPORTD (*(volatile uint8_t *) 0x2B ) 

int main() {                           
  // DDRD |= (1 << PINDx);      // this is the common way, changing the contents of DDRD
  MyDDRD |= (1 << PINDx);       // using my own declaration of DDRD
                                // pointed to by pointer *MyDDRD, set PINDx as output

                                // direct access of DDRD, set PINDx as output
  // (*(volatile uint8_t *) 0x2A ) |= (1 << PINDx);                                 
 
  // PORTD |= (1 << PINDx);     // this is the common way, changing the contents of PORTD                               
  MyPORTD  |= (1 << PINDx);     // using my own declaration of PORTD
                                // pointed to by pointer *MyPORTD. set PINDx to HIGH

                                // direct access of PORTD, set PINDx to HIGH
  // (*(volatile uint8_t *) 0x2B)  |= (1 << PINDx);                                
  _delay_ms(1000);            // delay for 1000 ms 
    
  while(1){
    _delay_ms(1000);              // delay for 1000 ms
                                  // direct access 
    // (*(volatile uint8_t *) 0x2B ) ^= (1 << PINDx);
    // PORTD ^= (1 << PINDx);        // this is the common way, toggle PINDx
    MyPORTD ^= (1 << PINDx);         // 0 ^ 0 == 0 XOR
                                     // 0 ^ 1 == 1 XOR
                                     // 1 ^ 0 == 1 XOR
                                     // 1 ^ 1 == 0 XOR                             
  }
}
