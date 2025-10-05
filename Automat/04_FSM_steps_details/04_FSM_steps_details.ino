// EBW 04_FSM_steps_details.ino
// shows change of states (steps) within one move in detail
// Pins of the rotary mapped to Arduino R4 ports
#define DTpin  2
#define CLKpin 3

// Current and previous value of the counter tuned by the rotary
int curVal = 0;
int prevVal = 0;

// Seven states of FSM (finite state machine)
//          0        1      2      3      4       5       6 
enum State {IDLE_11, CW_01, CW_00, CW_10, CCW_10, CCW_00, CCW_01};

//  transition table
//  from IDLE_11 with CLKfall (LOW)  to CW_01
//  from CW_01   with DTfall  (LOW)  to CW_00 
//  from CW_00   with CLKrise (HIGH) to CW_10 
//  from CW_10   with DTrise  (HIGH) to IDLE_11   

//  from IDLE_11 with DTfall  (LOW)  to CCW_10
//  from CCW_10  with CLKfall (LOW)  to CCW_00
//  from CCW_00  with DTrise  (HIGH) to CCW_01
//  from CCW_01  with CLKrise (HIGH) to IDLE_11
                                                                                                                                                
int state = IDLE_11;
int oldState;
int xState;
int msg=false;

// State Machine transitions for CLK level changes
void CLKchange() {                                         // Change in CLK: falls to LOW
  oldState = state;
  if (digitalRead(CLKpin)==LOW) {                          // determine HIGH or LOW
    if      (state==IDLE_11) state = CW_01;                //CLKfall
    else if (state==CCW_10)  state = CCW_00;               //CLKfall
  }
  else {
    if      (state==CW_00)    state = CW_10;               //CLKrise
    else if (state==CCW_01) { state = IDLE_11; curVal--; } //CLKrise
  }
  msg=true;
}

// State Machine transitions for DT level changes
void DTchange() {
  oldState = state;
  if (digitalRead(DTpin)==LOW) {
    if      (state==IDLE_11) state = CCW_10;                //DTfall
    else if (state==CW_01)   state = CW_00;                 //DTfall
  }
  else {
    if      (state==CCW_00)  state = CCW_01;                //DTrise
    else if (state==CW_10) { state = IDLE_11; curVal++; }   //DTrise
  }
  msg=true;  
}

void setup() {
  Serial.begin(57600);
  Serial.println("Start...");
  
  // Level HIGH will be default for all pins
  pinMode(CLKpin,INPUT_PULLUP);
  pinMode(DTpin,INPUT_PULLUP);
  
  // Both CLK and DT will trigges interrupts for all level changes
  attachInterrupt(digitalPinToInterrupt(CLKpin), CLKchange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DTpin),  DTchange,  CHANGE);
}
void loop() {
  // Any change in counter value is displayed in Serial Monitor
  if (msg) {
    decbin(oldState, state);
    msg = false;    
  }
  // Any change in counter value is displayed in Serial Monitor
  if (curVal != prevVal) {
    Serial.println(curVal);
    prevVal = curVal;
  }
}

void decbin(int _oldState, int _state){
  Serial.print("oldState="  + String( _oldState));
  Serial.print(" newState=" + String( _state));    
  Serial.print(" binState=");
  for (int i = 3; i >= 0; i--) {
    Serial.print(bitRead(_state, i));  
  }
  // {IDLE_11, CW_01, CW_00, CW_10, CCW_10, CCW_00, CCW_01}
  switch (_state) {
    case IDLE_11: Serial.println(" IDLE_11"); break;  // index=0
    case CW_01:   Serial.println(" CW_01");   break;  // index=1
    case CW_00:   Serial.println(" CW_00");   break;  // index=2
    case CW_10:   Serial.println(" CW_10");   break;  // index=3
    case CCW_10:  Serial.println(" CCW_10");  break;  // index=4
    case CCW_00:  Serial.println(" CCW_00");  break;  // index=5
    case CCW_01:  Serial.println(" CCW_01");  break;  // index=6
  }  
}
