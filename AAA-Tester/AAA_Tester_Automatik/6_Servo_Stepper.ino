// main function for moving the stepper (Revolver)
void stepper_move(int _controlValue, String _message){
  Serial.println(_message);
  lcd.clear(); lcd.print(_message);
  int moveDir = 1;
  if (_controlValue > 0) moveDir=1; else moveDir=-1;
  _controlValue = abs(_controlValue);
  for (int i=0; i <= _controlValue; i++){
  stepper.step(moveDir);
  } 
  stepper_off();                  // detach coils of stepper-motor 
}

// main function for moving servo (Trap)
void servo_move(int _stopAngle){
  servo_attach(true);
  startAngle = stopAngle;
  stopAngle = _stopAngle;
  myServo.write(stopAngle);
  delay(1000);                  // give move some time
  servo_attach(false);
}

// enables/disables servo
void servo_attach(boolean servoAttache){
  if (servoAttache==true) {
  myServo.attach(servoPin, 500, 2500);  // https://www.arduino.cc/reference/en/libraries/servo/attach/
                                        // changing min- and max-pulswidth to tested values   
  }
  if (servoAttache==false){
    myServo.detach();
  }
}

// disables the coils of the stepper-motor
void stepper_off(){
  digitalWrite(motor_pin_1,LOW);
  digitalWrite(motor_pin_3,LOW);
  digitalWrite(motor_pin_2,LOW);
  digitalWrite(motor_pin_4,LOW);   
}
