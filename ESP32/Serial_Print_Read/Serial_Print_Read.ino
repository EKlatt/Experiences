// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch Serial_Print_Read.ino 
// Get data from Serial Monitor

// The syntax of the message in Serial Monitor is: "name:value"
// E.g. "LED:1"

String strCommand;              // the received name
int controlValue;               // the received value
bool serialComplete = false;    // flag for loop() if serial input is complete

void setup() {
  Serial.begin(115200);
  while(!Serial) {}             // wait for established Serial connection
  Serial.println("EBW-Workshop");
  
  // serialEventRun();          // uncomment if serialEvent() does not work
  // serialEvent();             // umcomment this if serialEvent still does not work
}

void loop() {
  if (serialComplete) {         // serialComplete is set by function serialEvent()
    Serial.println( "Echo " + strCommand + ":" + controlValue);
    serialComplete = false;      // reset the flag and wait for new input
  }
}

void serialEvent() {
  byte buffer = Serial.available();
  Serial.println(buffer);        // only buffer=0 leads to false otherwise true
  if (buffer) {
    // Receiving input from Serial Monitor, Syntax LED:1 or LED:0  
    strCommand    = Serial.readStringUntil(':');        // delemitter ':'
    controlValue  = Serial.readStringUntil('\n').toInt();
  }
  serialComplete = true;            // setting flag serialComplete for loop() 
}
