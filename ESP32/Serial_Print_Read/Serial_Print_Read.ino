// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch Serial_Print_Read.ino 
// Get data from Serial monitor

// Important notices:
// Choose as baudrate in Serial.begin() always 115200 Baud
// The syntax of the message in Serial Monitor is: "name:value"
// E.g. "LED:1"

String strCommand;               // the received name
int controlValue;                // the received value
bool serialComplete = false;     // flag for loop() if serial input is complete

void setup() {
  Serial.begin(115200);
  while(!Serial) {}             // wait for established Serial connection

  // serialEventRun();          // uncomment if serialEvent() does not work
  // serialEvent();             // umcomment this if serialEvent still does not work

  Serial.println("EBW-Workshop");
}

void loop() {
  if (serialComplete) {
    Serial.println( "Echo " + strCommand + ":" + controlValue);
    serialComplete = false;      // reset the flag and wait for new input
  }
}

void serialEvent() {
  if (Serial.available()) {
    // Receiving input from Serial Monitor, Syntax LED:1 or LED:0  
    strCommand    = Serial.readStringUntil(':');
    controlValue  = Serial.readStringUntil('\n').toInt();
  }
  serialComplete = true;            // setting flag serialComplete for loop() 
}
