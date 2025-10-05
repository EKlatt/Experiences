// EBW 02_steps_graycode.ino
// Shows 4 steps within one move of the rotary encoder
// Example for polling  
// Hands on Arduino Incremental Rotary Encoders
// Based on Robert Paz
// https://www.youtube.com/watch?v=S1JJc8YAJqQ

 
// Pins of the rotary mapped to Arduino R4 ports
#define DTpin   2
#define CLKpin  3
#define DT_LED  12
#define CLK_LED 11

int  events = 0;
byte CLK, DT;              // value of Pin 3 /CLK and 2/DT to be read
byte DTp=1, CLKp=1;        // initialize previous state

void setup() {
  Serial.begin(57600);
  Serial.println("EBW");
  pinMode(CLK_LED, OUTPUT);      // show the movement of the Rotary Encoder
  pinMode(DT_LED, OUTPUT); 
  
  pinMode(CLKpin, INPUT_PULLUP);
  pinMode(DTpin, INPUT_PULLUP);
  
  // debugging LEDs starting state
  Serial.println("Starting state");
  digitalWrite(CLK_LED, digitalRead(CLKpin));
  digitalWrite(DT_LED,  digitalRead(DTpin));
  delay(2000);
  Serial.println("Loop starting");
}

void loop() {
  // code which shall be executed over and over
  // in this case polling Pins 3/CLK and 2/DT
  CLK = digitalRead(CLKpin);   // reading Pin 3/CLK  
  DT  = digitalRead(DTpin);    // reading Pin 2/DT


  // catch changing of state CLK or state DT
  if ( CLK^CLKp || DT^DTp ) {   // exclusive or "^"
    // code to be executed after state has changed
    events++;
    if (events==5) events=1;          
    Serial.print("events=");Serial.print(events);
    Serial.print(" CLK=");Serial.print(CLK);
    Serial.print(" DT=");Serial.print(DT);
    Serial.print(" CLK&DB=");
	
    // a little bit of mystic code in order to show state CLK and DT together
    binDisplay(2, CLK<<1 | DT);
	
    // debugging LEDs
    digitalWrite(CLK_LED, digitalRead(CLKpin));
    digitalWrite(DT_LED,  digitalRead(DTpin));
    
    DTp = DT; 
	  CLKp = CLK;            
    // end code to be executed after state has changed   
  }
}

// displaying binary number in Monitor for debug
void binDisplay(int size, unsigned long int value){
  for (int i = size-1; i >= 0; i--) {
    Serial.print((value >> i) & 1);}
  Serial.println();
}
