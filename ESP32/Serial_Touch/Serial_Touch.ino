// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch Serial_Touch.ino 
// Control an low current LED

// Important notices:
// Choose as baudrate in Serial.begin() always 115200 Baud
// Create a while-loop to wait for Serial-connection
// Change the "Serial Monitor Settings" to 115200 Baud
// COnnect a jumper-wire with GPIO 15 as touch-sensor

const int touchPin = 15;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial) {}          // wait for established serial connection
  Serial.println("EBW-Workshop");
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print("Touch-Sensor: ");
  Serial.println(touchRead(touchPin));
  delay (500);
}
