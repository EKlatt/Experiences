// Here we deal with input from serial Monitor/Terminal
// these functions are only used in manuel-mode (Terminal)

// evaluate input "controlLetter/stringCommand/controlValue" and perform action on it
void terminalInput(){
  // main command central
  if (serialComplete) {
    bufferToTokens();                   // separte input to tokens    
                                        // controlLetter, stringCommand, controlValue
    // Help
    if (controlLetter == 'h') help();
    // Automatic operation
    if (controlLetter=='a' || stringCommand.equals("auto")) {
      Serial.println(F("Automatik"));
      lcd.clear(); lcd.print("Automatik");              
      automatic();   
    }
    // Time, displays time on monitor/LCD
    if (stringCommand.equals("time")) echo_time();   
    // Read data from config.ini file
    if (controlLetter == 'r') {
      Serial.println(F("Lese config.ini"));
      lcd.clear(); lcd.print("Lese config.ini");           
      read_file(); 
    }
    // Show config-data
    if (controlLetter == 'i') echo_config();  
    // Initialize trap with defaults                                           
    if (stringCommand.equals("ti")) {  
      servo_move(trapClosed);           // parameter trapClosed for good AA-battery 
      Serial.println(F("Falle geschlossen"));
      lcd.clear(); lcd.print("Falle geschlossen");                        
    }
    // Battery present in measuring position
    if (controlLetter=='b') battery_present(); 
    // manual output of AA-battery voltage
    if (controlLetter=='v') echo_voltage(check_voltage());    
    // Stress-circuit on/off    
    if (controlLetter == 'l' || stringCommand.equals("load")) { 
      Serial.println(F("Last an/aus"));
      lcd.clear(); lcd.print(F("Last an/aus"));            
      stress_circuit();
    }            
    // (hidden) write data to file (test purpose)
    if (controlLetter == 'w') {
      Serial.println(F("Schreibe auf SD-Karte"));
      lcd.clear(); lcd.print(F("Schreibe auf SD"));                             
      write_file("19.09.2022;18:00", "1.5", "1.4", "0");
    }               
    // move trap e.g. "t:90"
    if (controlLetter=='t' || stringCommand.equals("trap")) {
      Serial.println(F("Falle bewegt"));
      lcd.clear(); lcd.print(F("Falle bewegt"));                 
      servo_move(controlValue);         
      echo_trap();                           // feedback of servo parameters 
    }
    // move stepper e.g. "s:512"
    if (controlLetter=='s' || stringCommand.equals("stepper")) {
      Serial.println(F("Stepper gedreht"));              
      stepper_move(controlValue, "Terminal s:xxx");
    }
     
    serialComplete = false;         // calling for new input
    controlLetter = 'n';            // n means nothing
    stringCommand = "not";          // not means nothing 
  } 
}
