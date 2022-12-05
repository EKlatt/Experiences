//  Photoresistor (LDR) Analog Demo

// LDR Characteristics
const float GAMMA = 0.7;
const float RL10 = 50;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int analogValue = analogRead(A1);
  float voltage = analogValue / 1024. * 5;
  float resistance = 2000 * voltage / (1 - voltage / 5);
  float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));

  Serial.print("Room: ");
  if (lux > 50) {
    Serial.println("Light!");
  } else {
    Serial.println("Dark  ");
  }
  Serial.print("voltage: ");
  Serial.print(voltage);
  Serial.print("Lux: ");
  Serial.print(lux);
  Serial.println("          ");

  delay(500);
}

 
