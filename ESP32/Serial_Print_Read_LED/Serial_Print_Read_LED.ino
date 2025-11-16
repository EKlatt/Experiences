// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch Serial_Print_Read_LED.ino 
// Get data from Serial monitor 
// show blocking from readStringUntil()-function

// Important notices:
// Choose as baudrate in Serial.begin() always 115200 Baud
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
  while(!Serial) {}             // wait for established Serial connection
  Serial.println("EBW-Workshop");
  pinMode(ledPin, OUTPUT);

  // serialEventRun();          // uncomment if serialEvent() does not work
  // serialEvent();             // umcomment this if serialEvent still does not work
}

void loop() {
  if (serialComplete) {         // checking for serial data: true if data received
    Serial.println( "Echo " + strCommand + ":" + controlValue);
    serialComplete = false;      // reset the flag and wait for new input
  }
  blinkLED();                   // call function for blinking LED
}

// function (depending on core) which runs if seriel data are present
void serialEvent() {
  if (Serial.available()) {
    // Receiving input from Serial Monitor, Syntax LED:1 or LED:0  
    strCommand    = Serial.readStringUntil(':');            // read a string up to character ':'
    controlValue  = Serial.readStringUntil('\n').toInt();   // read the remaining input and convert it to int
  }
  serialComplete = true;            // setting flag serialComplete for loop() 
}

void blinkLED() {
  unsigned long currentTime = millis();        // get the currenttime counting since RESET 
  if (currentTime - lastTime >= interval) {    // wait for an interval
    ledState = !ledState;                      // toggle the LED-state from high or low and v.v.
    digitalWrite(ledPin, ledState);            // turn led on or off
    lastTime = millis();                       // notice current time
  }  
}
