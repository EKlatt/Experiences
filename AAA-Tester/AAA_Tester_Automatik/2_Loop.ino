// Arduino-IDE loop()
void loop() {
  // check left button in order to start manuel or automatic operation
  if (digitalRead(operationPin)==HIGH) {                    
    if (operationOn == false){                        
      Serial.println(F("Betrieb gestartet"));
      Serial.println(F("Automatik? ->Linke Taste<-"));
      lcd.clear(); lcd.print(F("  Automatik?"));    
      lcd.setCursor(0,1);lcd.print(F("->Linke Taste<-"));      
      help();
      operationOn = true;      
    } 
    else if (operationOn == true && standAlone == false) {
      Serial.println(F("Automatik gestartet"));
      lcd.clear(); lcd.print(F("Automatik"));    
      lcd.setCursor(0,1);lcd.print(F("   gestartet"));
      delay(1000);      
      standAlone = true;
      read_file();                  // read parameter from config.ini
      automatic();         
    } else {
      Serial.println(F("Reset!"));
      lcd.clear(); lcd.print(F("Reset!"));       
      delay(1000);
      operationOn = false; 
      standAlone = false;             
    }
  }
  // check right button in order to move stepper
  if (digitalRead(stepPin)==HIGH) {
    stepper_move(10, "10 Schritte");            
  }
  // if there is a Terminal input, process it
  // we use serialEvent() to capture data
  if (operationOn == true) terminalInput();  
}
