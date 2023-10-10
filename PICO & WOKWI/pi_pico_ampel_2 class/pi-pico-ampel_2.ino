// pi-pico-ampel_2.ino
// class example with IDE & class
// https://arduino-pico.readthedocs.io/en/latest/
// https://arduino-pico.readthedocs.io/en/latest/sdk.html
// https://cec-code-lab.aps.edu/robotics/resources/pico-c-api/group__hardware__gpio.html
#include "Ampel.cpp"

Ampel mainLine(6, 7, 8);
Ampel sideLine(10, 11, 12);

void setup() {
  mainLine.init(); 
  sideLine.init();       
}

void loop() {
  //setAmpel(int phase) {
  // phase 1:     yellow
  // phase 2: red 
  // phase 3: red yellow
  // phase 4:            green   
  mainLine.setAmpel(1);
  sideLine.setAmpel(3);
  delay(2000);

  mainLine.setAmpel(2);
  sideLine.setAmpel(4);
  delay(2000);

  mainLine.setAmpel(3);
  sideLine.setAmpel(1);
  delay(2000);

  mainLine.setAmpel(4);
  sideLine.setAmpel(2);
  delay(2000);   
}