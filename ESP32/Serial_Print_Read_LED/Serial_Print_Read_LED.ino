// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch Serial_Print_Read_LED.ino 
// Get data from Serial monitor 
// show blocking from readStringUntil()-function

// The syntax of the message in Serial Monitor is: "name:value"
// E.g. "LED:1"

String strCommand;               // the received name
int controlValue;                // the received value
bool serialComplete = false;     // flag for loop() if serial input is complete
const byte ledPin      =   2;    // GPIO of low current LED
unsigned long lastTime =   0;    // variable holds the previous millis() value
const long interval    = 100;    // Blink interval in milliseconds
bool ledState          = false;  // used for toggling LED

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1000);
  while(!Serial) {}             // wait for established Serial connection
  Serial.println("EBW-Workshop");
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // did we get data from serial monitor
  if (serialComplete) {                               // serialComplete is set by function serialEvent()
    Serial.println( "Echo " + strCommand + ":" + controlValue);
    serialComplete = false;      // reset the flag and wait for new input
  }

  // call function for blinking LED
  blinkLED();                   

  // allways at the end of the loop we check for serial data   
  if (Serial.available()) serialEvent();              // emulate SerialEvent
}

// function runs if serial data are present
void serialEvent() {
  // Receiving input from Serial Monitor, Syntax LED:1 or LED:0  
  strCommand    = Serial.readStringUntil(':');          // delemitter ':'
  controlValue  = Serial.readStringUntil('\n').toInt(); // delemitter "New Line"
  serialComplete = true;                                // setting flag serialComplete for loop() 
}

// function which makes the LED blinking
void blinkLED() {
  unsigned long currentTime = millis();        // get the currenttime counting since RESET 
  if (currentTime - lastTime >= interval) {    // wait for an interval
    ledState = !ledState;                      // toggle the LED-state from high or low and v.v.
    digitalWrite(ledPin, ledState);            // turn led on or off
    lastTime = millis();                       // notice current time
  }  
}
