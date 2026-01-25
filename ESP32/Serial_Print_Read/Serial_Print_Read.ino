// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch Serial_Print_Read.ino 
// Get data from Serial Monitor
// Echo message in Serial Monitor

// The syntax of the message in Serial Monitor is: "name:value"
// E.g. "LED:1"

String strCommand;              // the received command name
int controlValue;               // the received value
bool serialComplete = false;    // flag for loop() if serial input is complete

void setup() {
  Serial.begin(115200);
  while(!Serial) {}             // wait for established Serial connection
  Serial.println("EBW-Workshop");
}

void loop() {
  // did we get data from serial monitor
  if (serialComplete) {                               // serialComplete is set by function serialEvent()
    Serial.println( "Echo " + strCommand + ":" + controlValue);
    serialComplete = false;      // reset the flag and wait for new input
  }
  // allways at the end of the loop we check for serial data  
  if (Serial.available()) serialEvent();              // emulate serialEvent
}

// function runs if serial data are present
void serialEvent() {
  // Receiving input from Serial Monitor, Syntax LED:1 or LED:0  
  strCommand    = Serial.readStringUntil(':');          // delemitter ':'
  controlValue  = Serial.readStringUntil('\n').toInt(); // delemitter "New Line"
  serialComplete = true;                                // setting flag serialComplete for loop() 
}
