// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch Bluetooth_Classic.ino 
// Get a message from Serial Monitor and send it to Bluetooth-device
// Get a message from  Bluetooth-device and send it to Serial Monitor

// https://randomnerdtutorials.com/esp32-bluetooth-classic-arduino-ide/
// https://lastminuteengineers.com/esp32-bluetooth-classic-tutorial/

#include "BluetoothSerial.h"        // Library einfügen

BluetoothSerial SerialBT;            // create the object SerialBT from class BluetoothSerial

void setup() {
  // Begin serial communication with ESP32 and Arduino IDE (Serial Monitor)
  Serial.begin(115200);
  while(!Serial) {}                   // wait for established serial connection
  Serial.println("EBW-Workshop");

  // Initialize the Bluetooth stack
  // The Bluetooth device name appears on your smartphone, please change it
  if (!SerialBT.begin("EBW-Enno")) {   // Bluetooth device name   
    Serial.println("Bluetooth failed to intit!");
    while(1);
  }                                 
  Serial.println("Bluetooth bereit. Jetzt mit Smartphone koppeln.");
}

void loop() {
  if (Serial.available()) {           // if there is an input from Serial Monitor (PC)
    SerialBT.write(Serial.read());    // send the input to the Bluetooth-Device
  }
  if (SerialBT.available()) {         // if there is an input from Bluetooth-Device
    Serial.write(SerialBT.read());    // send the input to Serial Monitor (PC)
  }
  delay(20);
}