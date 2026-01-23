// the rotary encoder is controlled via a state machine (FSM)
// State Machine transitions for CLK level changes

void CLKchange() {
  oldState = state;
  if (digitalRead(CLKpin) == LOW) {
    if      (state == IDLE_11) state = CW_01;              //CLKfall
    else if (state == CW_10)   state = CW_00;              //CLKfall
    else if (state == CCW_10)  state = CCW_00;             //CLKfall
  }
  else {
    if (state==CW_01) state = IDLE_11;                      //CLKrise
    else if (state == CW_00)    state = CW_10;              //CLKrise
    else if (state == CCW_00)   state = CCW_10;             //CLKrise
    else if (state == CCW_01) { state = IDLE_11; hueRE--; } //CLKrise
  }
}
// State Machine transitions for DT level changes
void DTchange() {
  oldState = state;
  if (digitalRead(DTpin) == LOW) {
    if      (state == IDLE_11) state = CCW_10;             //DTfall
    else if (state == CCW_01)  state = CCW_00;             //DTfall
    else if (state == CW_01)   state = CW_00;              //DTfall
  }
  else {
    if      (state == CCW_10)  state = IDLE_11;             //DTrise
    else if (state == CCW_00)  state = CCW_01;              //DTrise
    else if (state == CW_00)   state = CW_01;               //DTrise
    else if (state == CW_10) { state = IDLE_11; hueRE++; }  //DTrise
  }
}
