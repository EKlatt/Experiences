// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch Bluetooth_Classic_LED.ino
// Get a message from  Bluetooth-device and switch an LED
// The syntax of the message from Bluetooth is: "name:value"
// e.g. "LED:1"

// https://randomnerdtutorials.com/esp32-bluetooth-classic-arduino-ide/
// https://lastminuteengineers.com/esp32-bluetooth-classic-tutorial/

#include "BluetoothSerial.h"

#define ledPin  2            // GPIO where ledPin is connected to

// Variables for BluetoothSerial input
String strCommand     =  "";  // empty command-string
short  controlValue   =   0;  // values sets LED status 1=>HIGH 0=>LOW
bool serialComplete = false;  // flag for loop() "serial input is complete"

// Create BluetoothSerial object
BluetoothSerial SerialBT;

void setup() {
  // Begin serial communication with ESP32 and Arduino IDE (Serial Monitor)
  Serial.begin(115200);
  while (!Serial) {}
  Serial.println("EBW-Workshop");

  // Initialize ledPin as an output
  pinMode(ledPin, OUTPUT);
  
  // Initialize the Bluetooth stack
  // The Bluetooth device name appears on your smartphone, please change it
  if (!SerialBT.begin("EBW-Enno")) {   // Bluetooth device name   
    Serial.println("Bluetooth failed to intit!");
    while(1);
  }                                 
  Serial.println("Bluetooth bereit. Jetzt mit Smartphone koppeln.");
}

void loop() {
  // call the function looking for data in Bluetooth stack
  serialBTdata();

  // processe Bluetooth input
  if (serialComplete) processData();  // get the command and switch LED
}

void serialBTdata() {
  if (SerialBT.available() > 0) {
    // Receiving input from Smartphone, Syntax LED:1 or LED:0  
    strCommand    = SerialBT.readStringUntil(':');           // read a string up to character ':'
    controlValue  = SerialBT.readStringUntil('\n').toInt();  // read the remaining input and convert it to int
  
    strCommand.trim();
    strCommand.toLowerCase();
  
    serialComplete = true;            // setting flag serialComplete for loop()    
  }
}

// evaluate Bluetooth input
void processData() {
  if (strCommand == "led") {
    Serial.println("LED: " + String(controlValue)); 

    if (controlValue == 1) digitalWrite(ledPin, HIGH);
    if (controlValue == 0) digitalWrite(ledPin, LOW); 
  }   
  
  serialComplete = false;            // setting flag for loop()   
}
