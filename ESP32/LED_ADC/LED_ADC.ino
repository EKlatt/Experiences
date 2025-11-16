// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch LED_PWM.ino 
// Attention: Never supply potentiometer with a volatage higher than 3.3 V
//            Never change the attenuation: default "ADC_11db"
// the ADC has a 12 bit resolution from 0 to 4095 (2^12-1)

#define potiPin  36  // ESP32 pin GPIO36 (ADC0) connected to Potentiometer pin
#define ledPin    2  // ESP32 pin GPIO2 connected to LED's pin

void setup() {
  Serial.begin(115200);
  while(!Serial) {}
  Serial.println("EBW-Workshop");

  // Initialize ledPin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // reads the input from analog pin A0 (value between 0 and 4095)
  short analogValue = analogRead(potiPin);

  // the analogRead() values for 12 bit resolution have a range between 0 to 4095
  // scale poti-values to led-brightness: PWM value between 0 and 255
  short brightness = map(analogValue, 0, 4095, 0, 255);

  // sets the brightness LED that connects to ledPin
  analogWrite(ledPin, brightness);

  // print out the value
  Serial.print("Analog value = ");
  Serial.print(analogValue);
  Serial.print(" => brightness = ");
  Serial.println(brightness);
  delay(500);  
}
