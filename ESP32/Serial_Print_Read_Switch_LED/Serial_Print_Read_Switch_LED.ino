// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch Serial_Print_Read_Switch_LED.ino 
// Get data from Serial Monitor 
// Switch LED on or off

// The syntax of the message in Serial Monitor is: "name:value"
// E.g. "LED:1"

String strCommand;               // the received command name
int controlValue;                // the received value
bool serialComplete = false;     // flag for loop() if serial input is complete

const byte ledPin            =   2;    // GPIO of low current LED
const unsigned long interval = 100;    // Blink interval in milliseconds

void setup() {
  Serial.begin(115200);
  while(!Serial) {}             // wait for established Serial connection
  Serial.println("EBW-Workshop");
  Serial.println("Message led:1 or led:0");
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // did we get data from serial monitor
  if (serialComplete) {                               // serialComplete is set by function serialEvent()
    switchLED();                                      // call function for switching LED
    serialComplete = false;                           // reset the flag and wait for new input
  }
  // allways at the end of the loop we check for serial data
  if (Serial.available()) serialEvent();              // emulate "SerialEvent" because we own an ESP32
}

// function runs if serial data are present
void serialEvent() {
  // Receiving input from Serial Monitor, Syntax LED:1 or LED:0  
  strCommand     = Serial.readStringUntil(':');          // delemitter ':'
  controlValue   = Serial.readStringUntil('\n').toInt(); // delemitter "New Line"
  serialComplete = true;                                 // setting flag serialComplete for loop() 
}

void switchLED() {
  strCommand.trim();
  strCommand.toUpperCase();
  if (strCommand == "LED") {
    Serial.println( "Echo " + strCommand + ":" + controlValue);
    if (controlValue == 1) digitalWrite(ledPin, HIGH);
    if (controlValue == 0) digitalWrite(ledPin, LOW);   
  } else Serial.println("unknown command -> timeout");
}
