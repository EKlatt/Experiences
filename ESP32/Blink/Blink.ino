// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch Blink.ino 
// Control an low current LED

#define LED_BUILTIN 2                // Must be new defined because ESP32 comes without definition
unsigned long lastTimeStamp = 0:     // 

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  while(!Serial) {}

  Serial.println("EBW");

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}
