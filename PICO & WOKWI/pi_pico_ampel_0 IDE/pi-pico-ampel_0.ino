// pi-pico-ampel_0.ino
// IDE-commands
// https://arduino-pico.readthedocs.io/en/latest/help.html
// https://randomnerdtutorials.com/programming-raspberry-pi-pico-w-arduino-ide/#rpi-pico-arduino-ide-programming
// https://randomnerdtutorials.com/projects-raspberry-pi-pico/
// #include "pico/stdlib.h"

// "char" in Arduino reference also defined as "uint8_t" (C99 standard)
char mainRed    = 6;     // GP6
char mainYellow = 7;     // GP7
char mainGreen  = 8;     // GP8

void setup() {
  Serial1.begin(115200);
  Serial1.println("EBW");

  pinMode(mainRed,    OUTPUT);
  pinMode(mainYellow, OUTPUT);
  pinMode(mainGreen,  OUTPUT);
}

void loop() {
  // phase 1:     yellow
  // phase 2: red
  // phase 3: red yellow
  // phase 4:             GREEN

  mainPhase_1(); delay(1500);
  mainPhase_2(); delay(2500);
  mainPhase_3(); delay(1000);
  mainPhase_4(); delay(2500);
  delay(500);
}
void mainPhase_1() {                // yellow
  digitalWrite(mainRed, LOW);
  digitalWrite(mainYellow, HIGH);
  digitalWrite(mainGreen, LOW);
}
void mainPhase_2() {                // red
  digitalWrite(mainRed, HIGH);
  digitalWrite(mainYellow, LOW);
  digitalWrite(mainGreen, LOW);
}
void mainPhase_3() {                // red yellow
  digitalWrite(mainRed, HIGH);
  digitalWrite(mainYellow, HIGH);
  digitalWrite(mainGreen, LOW);
}
void mainPhase_4() {
  digitalWrite(mainRed, LOW);       // green
  digitalWrite(mainYellow, LOW);
  digitalWrite(mainGreen, HIGH);
}
