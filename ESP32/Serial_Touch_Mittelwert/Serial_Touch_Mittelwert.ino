// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch Serial_Touch.ino 
// Get data from touchsensor

// Important notices:
// Choose as baudrate in Serial.begin() always 115200 Baud
// Create a while-loop to wait for Serial-connection
// Change the "Serial Monitor Settings" to 115200 Baud
// COnnect a jumper-wire with GPIO 15 as touch-sensor

const int touchPin = 15;     // GPIO15 defined as Touch 3
int count = 0;
int sum = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial) {}          // wait for established serial connection
  Serial.println("EBW-Workshop");
}

void loop() {
  // put your main code here, to run repeatedly:

  // calculating arithmetic mean of 10 samples
  sum = sum + touchRead(touchPin);
  if (count == 10) {
    Serial.print("Mean Value: ");
    Serial.println( sum/10 ) ;
    sum = 0;
    count = 0;
  }
  count = count + 1;
  Serial.println("count= " + String(count));
  delay (100);
}
