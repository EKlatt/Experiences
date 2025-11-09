// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch Serial_Print.ino 
// Control an low current LED

// Important notices:
// Choose as baudrate in Serial.begin() always 115200 Baud
// Create a while-loop to wait for Serial-connection
// Change the "Serial Monitor Settings" to 115200 Baud

#define SPEED_SERIAL 115200

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SPEED_SERIAL);
  while(!Serial) {}          // wait for established serial connection

  Serial.println("EBW-Workshop");
}

void loop() {
  // put your main code here, to run repeatedly:
  byte touchValue = touchRead(15)
  Serial.println("Touch 3: " + String(touchValue));
  delay(500);
}
