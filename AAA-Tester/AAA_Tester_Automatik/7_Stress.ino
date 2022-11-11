// check if battery is in measuring position
boolean battery_present(){
  // check stepAutoPin battery present or not
  if (digitalRead(stopAutoPin) == HIGH) {
    Serial.println(F("Batterie geladen"));
    lcd.clear(); lcd.print(F("Batterie geladen"));
    delay(1000); 
    return false;            
  } else {
    Serial.println(F("Keine Batterie"));
    lcd.clear(); lcd.print(F("Keine Batterie"));
    delay(1000); 
    return true;    
  }   
}

// AA-battery testing procedure
double check_voltage(){
  double readAnalog = analogRead(voltagePin);
                                   // times 2 because of voltage devider  
  readAnalog = AREF_Voltage/1023 * (readAnalog) * 2;                        
  return readAnalog;
}

// activate or deactivate stress-circuit
void stress_circuit(){
  if ( activeStress == false ){
    activeStress = true;
    digitalWrite( stressPin, HIGH);
    Serial.println(F("Lastkreis geschlossen"));
    lcd.clear(); lcd.print(F("Lastkreis"));
    lcd.setCursor(0,1);lcd.print(F("   geschlossen"));         
  } else {
    activeStress = false;
    digitalWrite( stressPin, LOW);
    Serial.println(F("Lastkreis offen"));
    lcd.clear(); lcd.print(F("Lastkreis"));
    lcd.setCursor(0,1);lcd.print(F("   offen"));                 
  }
}
