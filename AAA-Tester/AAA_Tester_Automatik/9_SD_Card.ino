// functions for reading and writing of SD-card
void read_file(){
  // open the config.ini file for reading 
  myFile = SD.open("config.ini");
  if (myFile) {
    String configData;
    configData          = myFile.readStringUntil('\n');
    compareVoltage      = configData.toDouble();
    configData          = myFile.readStringUntil('\n');
    referenceStressTime = configData.toInt();       
    configData          = myFile.readStringUntil('\n');
    AREF_Voltage         = configData.toDouble();
    configData          = myFile.readStringUntil('\n');
    stepsLoadTest       = configData.toInt(); 
    configData          = myFile.readStringUntil('\n');         
    stepsTestTrap       = configData.toInt();
    
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("Fehler beim oeffnen von config.ini");
  }
}

// write protocol-data
void write_file(String _time, String _voltageStart, String _voltageEnd, String _status){
  // open the protocol file for writing
  myFile = SD.open("Excel.csv", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println(F("Schreibe in Excel.csv"));
    String convertToComma = _voltageStart + ";" + _voltageEnd;
    convertToComma.replace('.', ',');                             // german Excel expects comma
    myFile.println(_time + ";" + convertToComma + ";" + _status);
    myFile.close();                                               // close the file
    Serial.println(F("Daten in Excel.csv geschrieben"));
    lcd.clear(); lcd.print(F("Daten nach"));
    lcd.setCursor(0,1);lcd.print("   Excel.csv");      
  } else {
    // if the file didn't open, print an error:
    Serial.println(F("Fehler beim oeffnen Excel.csv"));
  }
  delay(2000);  
}
