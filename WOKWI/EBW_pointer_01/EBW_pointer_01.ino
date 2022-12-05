// Pointer arithmetic
 void setup() {
  Serial.begin(9600);
  
  uint8_t MyDDRD = 0x10;                // declare a variable and initialze with 0x10
  uint8_t *ptrMemAdr;                   // "*" => declare ptrMemAdr as a pointer to uint8_t data type 
  ptrMemAdr = &MyDDRD;                  // "&" => give me the address of MyDDRD

  Serial.print("ptrMemAdr ");
  Serial.println((long)ptrMemAdr,HEX);  // => 8FB  (contents of ptrMemAdr = address of MyDDRD)
  Serial.print("*ptrMemAdr ");
  Serial.println(*ptrMemAdr,HEX);       // => 10  (contents of address pointed to by ptrMemAdr).
   
                                        // the "*" sets or gets contents depending on syntax
  *ptrMemAdr = 0x20;                    // "*" => set the contents of address pointed to by ptrMemAdr
  uint8_t result = *ptrMemAdr;          // "*" => get the value of the address of pointer ptrMemAdr

  Serial.print("*ptrMemAdr ");
  Serial.println(*ptrMemAdr,HEX);       // => 20    (contents of address pointed to by ptrMemAdr).
  Serial.print("result ");
  Serial.println(result, HEX);          // => 20     (contents of address pointed to by ptrMemAdr).     
  Serial.print("MyDDRD "); 
  Serial.println(MyDDRD,HEX);           // => 20     (contents of MyDDRD)

  Serial.print("ptrMemAdr ");
  Serial.println((long)ptrMemAdr,HEX);  // => 8FB    (contents of ptrMemAdr = address of MyDDRD)                           
  Serial.print("&ptrMemAdr ");
  Serial.println((long)&ptrMemAdr,HEX); // => 8F9   (give me the address of ptrMemAdr)
} 
void loop() {}
