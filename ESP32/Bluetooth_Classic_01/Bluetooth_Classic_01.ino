// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch Bluetooth_Classic_01.ino 

// get a message from  Bluetooth-Device and send it to Serial Monitor

// https://randomnerdtutorials.com/esp32-bluetooth-classic-arduino-ide/
// https://lastminuteengineers.com/esp32-bluetooth-classic-tutorial/

#include "BluetoothSerial.h"

BluetoothSerial SerialBT;          // create the object SerialBT from class BluetoothSerial

void setup() {
  // Begin serial communication with ESP32 and Arduino IDE (Serial Monitor)
  Serial.begin(115200);
  SerialBT.begin("EBW-Enno");       // Bluetooth device name
  // There is no Pin possible in this Library
                                  
  Serial.println("The device started, now you can pair it with bluetooth!");
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