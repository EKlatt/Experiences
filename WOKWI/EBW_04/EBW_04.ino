boolean led;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Taster & LED.");
  pinMode(13, OUTPUT);
  pinMode(4, INPUT);
  led = false;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(4) & led == false) {
    digitalWrite(13, HIGH);
    led = true;
    delay(1000);
  }
  if (digitalRead(4) & led == true){
    digitalWrite(13, LOW);
    led = false;
    delay(1000);    
  }  
} 
