// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch L_Schmidt.ino 
// Get data from Serial Monitor
// Calculate and output in Serial Monitor

// The syntax of the input in Serial Monitor is: "a:b"
// E.g. "12;13"

int a;                          // the received value
int b;
bool serialComplete = false;    // flag for loop() if serial input is complete

void setup() {
  Serial.begin(115200);
  while(!Serial) {}             // wait for established Serial connection
  Serial.println("EBW-Workshop");
}

void loop() {
  // did we get data from serial monitor
  if (serialComplete) {                               // serialComplete is set by function serialEvent()
    old_multi(a, b);
    serialComplete = false;                           // reset the flag and wait for new input
  }
  // allways at the end of the loop we check for serial data  
  if (Serial.available()) serialEvent();              // emulate serialEvent
}

// function runs if serial data are present
void serialEvent() {
  // Receiving input from Serial Monitor, Syntax LED:1 or LED:0  
  a  = Serial.readStringUntil(';').toInt();      // delemitter ';'
  b  = Serial.readStringUntil('\n').toInt();     // delemitter "New Line"
  serialComplete = true;                         // setting flag serialComplete for loop() 
}

void old_multi(int _a, int _b){
  int s=0;
  Serial.println(_a);
  Serial.println(_b);        

  while( _a > 0) {
    if (_a & 1) s=s+_b;
    // _a = (_a/2);
    _a=_a >> 1;
    // _b = _b*2;
    _b=_b << 1;
  }
  Serial.println(s);
  Serial.println("Done!"); 
}