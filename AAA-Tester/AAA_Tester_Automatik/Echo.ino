// display trap-data
void echo_config(){
  Serial.println(F("Zeige config Werte"));
  Serial.print(F("Batterie Vergleichsspannung:    "));Serial.println(compareVoltage);
  Serial.print(F("Belastungsdauer:                "));Serial.println(referenceStressTime);  
  Serial.print(F("AREF:                           "));Serial.println(AREF_Voltage);
  Serial.print(F("Schritte Ladepunkt-Testposition:"));Serial.println(stepsLoadTest); 
  Serial.print(F("Schritte Testposition-Falle:    "));Serial.println(stepsTestTrap);         
}

void echo_trap(){
  Serial.print(F("Falle: "));
  Serial.print(F("startAngle:" )); Serial.print(startAngle);
  Serial.print(F(" stopAngle:" )); Serial.println(stopAngle);  
}

// displaying present voltage
void echo_voltage(double _voltage){
  Serial.print(F("U = ")); Serial.print(_voltage); Serial.println(" V");
  lcd.clear();
  lcd.print(F("U = ")); lcd.print(_voltage); ; lcd.print(" V");
  delay(2000);
}
