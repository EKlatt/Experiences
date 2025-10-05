// EBW 01_Bouncing.ino
// Shows bouncing
// Pins of the rotary mapped to Arduino R4 ports
#define DTpin  2
#define CLKpin 3

// Current and previous value of the counter tuned by the rotary
int count    = 0;
int preCount = 0;

// rotary encoder gray-code
// 11 => 0b11 => decimal 3
// 01 => 0b11 => decimal 1
// 00 => 0b11 => decimal 0
// 10 => 0b11 => decimal 2

int state = 0b11;      // 0b11 => 3
int oldState;

void setup() {
  Serial.begin(57600);
  
  // Level HIGH will be default for all pins    
  pinMode(DTpin,  INPUT_PULLUP);
  pinMode(CLKpin, INPUT_PULLUP);
  
  // Both CLK and DT will trigges interrupts for all level changes
  attachInterrupt(digitalPinToInterrupt(DTpin),  ISRchange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(CLKpin), ISRchange, CHANGE);
}

void loop() {
  // Any change of counter value is displayed in Serial Monitor
  if (count != preCount) {
    Serial.print("Count= ");
    Serial.println(count);
    preCount = count;
  }
}

void ISRchange() {
  oldState = state;
  state = (digitalRead(CLKpin) << 1) | digitalRead(DTpin);

  // evaluate only if we are in idle-state 0b11
  if (state == 0b11) {
    if (oldState      == 0b10) count++;  // clockwise
    else if (oldState == 0b01) count--;  // counterclockwise
  }
}
