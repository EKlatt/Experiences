// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch Blink_No_Blocking.ino 
// Control an low current LED
// An alternate code for non-blocking blinking LED

const byte ledPin      = 2;           // GPIO2 (no LED on board)
unsigned long lastTime = 0;           // Variable holds the previous millis() value
const long interval    = 1000;        // Blink interval
bool ledState          = false;       // variable for toggling LED

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  while(!Serial) {}
  Serial.println("EBW-Workshop");

  // initialize ledPin as an output.
  pinMode(ledPin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  unsigned long currentTime = millis();     // time since RESET
  if (currentTime - lastTime >= interval) { // wait a second
    ledState = !ledState;                   // toggle the LED-state from high or low ...
    digitalWrite(ledPin, ledState);         // turn led on or off
    Serial.println(currentTime);
    lastTime = millis();                    // notice current time
  }
}