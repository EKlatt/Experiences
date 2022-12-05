// Anmerkung: Eingebundene Bibliotheken ohne Befehlserweiterung
#include <DHT.h>

#define DHTPIN 3            // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11       // DHT 11
DHT dht(DHTPIN, DHTTYPE);   // Create object dht() 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("DHT11 Test");
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);

  // Reading humidity
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();

  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.print(F(" °C  Humidity: "));
  Serial.print(h);
  Serial.println(F(" %"));
} 

