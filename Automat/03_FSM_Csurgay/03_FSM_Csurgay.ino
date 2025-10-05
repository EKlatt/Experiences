// EBW 03_FSM_Csurgay.ino
// Peter Csurgay 2019-04-10
// modified by Enno Klatt

// Pins of the rotary mapped to Arduino R4 ports
#define DTpin  2
#define CLKpin 3

// Current and previous value of the counter tuned by the rotary
int curVal = 0;
int prevVal = 0;

// Seven states of FSM (finite state machine)
#define IDLE_11 0
#define CW_01   1
#define CW_00   2
#define CW_10   3
#define CCW_10  4
#define CCW_00  5
#define CCW_01  6
int state = IDLE_11;

// State Machine transitions for CLKpin level changes
void rotaryCLK() {
  if (digitalRead(CLKpin) == LOW) {
    if      (state == IDLE_11) state = CW_01;               //CLKfall
    else if (state == CW_10)   state = CW_00;               //CLKfall
    else if (state == CCW_10)  state = CCW_00;              //CLKfall
  }
  else {
    if (state==CW_01) state = IDLE_11;                      //CLKrise
    else if (state==CW_00)    state = CW_10;                //CLKrise
    else if (state==CCW_00)   state = CCW_10;               //CLKrise
    else if (state==CCW_01) { state = IDLE_11; curVal--; }  //CLKrise
  }
}

// State Machine transitions for DTpin level changes
void rotaryDT() {
  if (digitalRead(DTpin) == LOW) {
    if      (state == IDLE_11) state = CCW_10;               //DTfall
    else if (state == CCW_01)  state = CCW_00;               //DTfall
    else if (state == CW_01)   state = CW_00;                //DTfall
  }
  else {
    if      (state == CCW_10)  state = IDLE_11;              //DTrise
    else if (state == CCW_00)  state = CCW_01;               //DTrise
    else if (state == CW_00)   state = CW_01;                //DTrise
    else if (state == CW_10) { state = IDLE_11; curVal++; }  //DTrise
  }
}

void setup() {
  Serial.begin(57600);
  Serial.println("Start...");
  
  // Level HIGH will be default for all pins
  pinMode(CLKpin,INPUT_PULLUP);
  pinMode(DTpin,INPUT_PULLUP);
  
  // Both CLKpin and DTpin will trigges interrupts for all level changes
  attachInterrupt(digitalPinToInterrupt(CLKpin), rotaryCLK, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DTpin), rotaryDT, CHANGE);
}
void loop() {
  // Any change in counter value is displayed in Serial Monitor
  if (curVal != prevVal) {
    Serial.println(curVal);
    prevVal = curVal;
  }
}
