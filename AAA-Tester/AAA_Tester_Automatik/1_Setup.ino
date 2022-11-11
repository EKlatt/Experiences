// Arduino-IDE setup()
void setup() {
  Serial.begin(9600);               // Open serial communication
  lcd.begin();                      // initialize the LCD
  
  pinMode(stressPin, OUTPUT);       // initialize the load circuit
  pinMode(operationPin,INPUT);      // button left, start operation
  pinMode(stepPin,INPUT);           // button right, move stepper
  pinMode(stopAutoPin,INPUT);       // limit switch, no battery, 
                                    // stop automatic operation
  stepper.setSpeed(stepperSpeed);   // initialize stepper  
 
  analogReference(INTERNAL);             // should be 1.1 V
                                         // new battery-voltage may have 1.65 V
                                         // we need to use a voltage devider
                                         // for analog input (10 kOhm for R1 and R2)   
    
  // RTC initialization
  if (! rtc.begin()) {
    Serial.println(F("RTC nicht gefunden"));
    lcd.clear(); lcd.print(F("RTC?"));
    Serial.flush();
    while (1) delay(10);
  }
 if (! rtc.isrunning()) {
    Serial.println(F("RTC nicht gestartet, Zeit wird initialisiert"));
    lcd.clear(); lcd.print(F("RTC init"));    
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  } 

  // SD-card initalization
  if (!SD.begin(10)) {
    Serial.println(F("SD-Karte Initialisierung fehlgeschlagen"));
    lcd.clear(); lcd.print(F("SD-Karte?"));      
    while (1);
  }
  Serial.println(F("SD-Karte Initialisierung erfolgt"));
  Serial.println(F("Ladepunkt pruefen: ->Rechte Taste<-"));  
  lcd.clear(); lcd.print(F("  Ladepunkt:"));
  lcd.setCursor(0,1);lcd.print(F("->Rechte Taste<-"));
  delay(2500);
  Serial.println(F("Start mit ->Linke Taste<-"));  
  lcd.clear(); lcd.print(F("  Start mit"));
  lcd.setCursor(0,1);lcd.print(F("->Linke Taste<-"));

  double dummy = analogRead(voltagePin); // to initialize AREF            
}
