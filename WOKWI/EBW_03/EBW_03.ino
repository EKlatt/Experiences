void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Taster testen.");
  pinMode(4, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(4)) {
    Serial.println("Nachricht gesendet");
  }
  delay(200);
}  
  
