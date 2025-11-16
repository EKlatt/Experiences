// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch PWM_Mosfet.ino 
// Control an LED with a MOSFET & PWM

#define ledPin 4               // precompiler directive

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  Serial.println("EBW-Workshop");
  // set the LED as an output
  pinMode(ledPin, OUTPUT);
}

void loop(){
  // increase the LED brightness
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle+= 5){   
    // changing the LED brightness with PWM
    analogWrite(ledPin, dutyCycle);
    Serial.println(dutyCycle);
    delay(250);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle-= 5){
    // changing the LED brightness with PWM
    analogWrite(ledPin, dutyCycle);
    Serial.println(dutyCycle);
    delay(250);
  }
}