// User input over terminal
// event incoming serial data from serial monitor
void serialEvent() {
  // listen for serial commands like: s:512 or stepper:512
  while (Serial.available() && !serialComplete) { 
    char inChar = (char)Serial.read();      // cast incoming byte to char 
      Serial.print(inChar);                   // echo the character to serial output
                                            // store it in buffer[]; increase index 
    if(i_buf < MAX_BUF-1) buffer[i_buf++] = inChar;                                                  
    if (inChar == '\n') {                   // entire message received
      buffer[i_buf-1]='\0';                 // terminate the buffer with '\0'
      i_buf=0;                              // setting the buffer index back to 0
      serialComplete = true;                // setting flag "input completed"
                                            // this flag needs to be checked in loop()
    }
  }              
}

// separate input into tokens 
void bufferToTokens(){
  // deviding monitor input "letter:positon" e.g. "s:512" into tokens
  // deviding monitor input "string:positon" e.g. "stepper:512" into tokens                                    
  char *arg0 = strtok(buffer, ":");         // token e.g. 's' or "stepper"          
  char *arg1 = strtok(NULL, ":");           // token e.g. "512" 
  
  controlLetter = arg0[0];                  // make a char-variable for switch() of arg0
  controlValue = atoi(arg1);                // make a int-variable of arg1
  controlLetter = tolower(controlLetter);   // convert to lowercase 
                                            // if we have a string and not a letter
  stringCommand = arg0;                     // for input like stepper:512
  stringCommand.trim();
  if (stringCommand.length() != 1 ) controlLetter = 'n';
}
