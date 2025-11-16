// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch Blink_Mosfet.ino 
// Control an LED with a MOSFET

#define ledPin 4             // GPIO4 where ledPin is connected to

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  while(!Serial) {}
  Serial.println("EBW-Workshop");
  // initialize digital "ledPin" as an output.
  pinMode(ledPin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(ledPin, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                 // wait for a second
  digitalWrite(ledPin, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                 // wait for a second
}
