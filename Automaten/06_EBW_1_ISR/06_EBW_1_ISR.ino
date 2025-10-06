// EBW 06_EBW_1_ISR.ino
// EBW-code with one ISR-routine
// Pins of the rotary mapped to Arduino R4 ports
#define DTpin  2
#define CLKpin 3

// Current and previous value of the counter tuned by the rotary
int count    = 0;
int preCount = 0;

// Seven states of FSM (finite state machine)
//          0        1      2      3      4       5       6 
enum State {IDLE_11, CW_01, CW_00, CW_10, CCW_10, CCW_00, CCW_01};
int state = IDLE_11;
int oldState;
bool msg   = false;
bool debug = true;

//  State Machine transitions for CLK & DT level changes
//  transition table
//  CW means clockwise, CCW means counterclockwise
//  laststate    with transition     to newstate
//  ------------|-------------------|-----------
//  from IDLE_11 with CLKfall (LOW)  to CW_01
//  from CW_01   with DTfall  (LOW)  to CW_00 
//  from CW_00   with CLKrise (HIGH) to CW_10 
//  from CW_10   with DTrise  (HIGH) to IDLE_11   

//  from IDLE_11 with DTfall  (LOW)  to CCW_10
//  from CCW_10  with CLKfall (LOW)  to CCW_00
//  from CCW_00  with DTrise  (HIGH) to CCW_01
//  from CCW_01  with CLKrise (HIGH) to IDLE_11

void ISRchange() {
  oldState = state;
  bool CLK = digitalRead(CLKpin);
  bool DT  = digitalRead(DTpin);
// CW    
  if ( oldState==IDLE_11 && CLK==LOW )  state=CW_01;
  if ( oldState==CW_01   && DT ==LOW )  state=CW_00;
  if ( oldState==CW_00   && CLK==HIGH ) state=CW_10;
  if ( oldState==CW_10   && DT ==HIGH ) {state=IDLE_11; count++;}
// CCW  
  if ( oldState==IDLE_11 && DT ==LOW )  state=CCW_10;
  if ( oldState==CCW_10  && CLK==LOW )  state=CCW_00;  
  if ( oldState==CCW_00  && DT ==HIGH ) state=CCW_01;  
  if ( oldState==CCW_01  && CLK==HIGH ) {state=IDLE_11; count--;}

  msg=true;
}

void setup() {
  Serial.begin(57600);
  
  // Level HIGH will be default for all pins
  pinMode(CLKpin,INPUT_PULLUP);
  pinMode(DTpin, INPUT_PULLUP);
  
  // Both CLK and DT will trigges interrupts for all level changes
  attachInterrupt(digitalPinToInterrupt(CLKpin), ISRchange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DTpin),  ISRchange, CHANGE);
}

void loop() {
  // Any change in counter value is displayed in Serial Monitor
  if (msg && debug) {
    msgState(oldState, state);
    msg = false;    
  }
  // Any change in counter value is displayed in Serial Monitor
  if (count != preCount) {
    Serial.println("counter=" + String(count));
    preCount = count;
  }  
}

void msgState(int _oldState, int _state){
  Serial.print(" oldState=" + String( _oldState));
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
