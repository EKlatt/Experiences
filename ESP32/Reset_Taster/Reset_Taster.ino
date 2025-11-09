// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch Reset_Taster.ino 
// Hardware-Reset with button
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  while(!Serial) {}

  Serial.println("EBW");
}

// the loop function runs over and over again forever
void loop() {
}