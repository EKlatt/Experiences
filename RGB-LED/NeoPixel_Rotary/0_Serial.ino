// routines for serial input and evaluating input

void serialData() {
  if (Serial.available() > 0) {
    // Receiving input from Monitor, Syntax h:60 or s:30 or l:50 or b:100   
    strCommand    = Serial.readStringUntil(':');
    controlValue  = Serial.readStringUntil('\n').toInt();
  
    strCommand.trim();
    strCommand.toLowerCase();
    controlLetter  = strCommand.charAt(0);
      
    serialComplete = true;            // setting flag serialComplete for loop()    
  }
}

// evaluating serial input
void processData() {
  if (controlLetter=='h') {
    hue = constrain(controlValue, 0, 360);
    Serial.println("new hue = " + String(hue)); 
  }    
  if (controlLetter=='s') {
    sat = constrain(controlValue, 0, 100);
    Serial.println("new sat = " + String(sat));           
  }
  if (controlLetter=='v') {
    value = constrain(controlValue, 0, 100);
    Serial.println("new value = " + String(value));     
  }
  if (controlLetter=='b') {
    bright = constrain(controlValue, 0, 100); 
    Serial.println("new bright = " + String(bright));                 
  }  
  serialComplete = false;            // setting flag for loop()  
  newParameter   = true;             // setting flag for loop()  
}
