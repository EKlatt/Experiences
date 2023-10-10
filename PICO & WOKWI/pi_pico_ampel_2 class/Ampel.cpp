#include <Arduino.h>
class Ampel{
  private:
  char ledRed;
  char ledYellow;
  char ledGreen;

  public:
  Ampel(char _ledRed, char _ledYellow, char _ledGreen){
  ledRed    = _ledRed;
  ledYellow = _ledYellow;
  ledGreen  = _ledGreen;
  }

  void init(){
    pinMode(ledRed, OUTPUT);
    pinMode(ledYellow, OUTPUT);
    pinMode(ledGreen, OUTPUT); 
  }

  // phases
  void setPhase(bool _red, bool _yellow, bool _green){
    digitalWrite(ledRed, _red);
    digitalWrite(ledYellow, _yellow);
    digitalWrite(ledGreen, _green);       
  }  
  void setAmpel(int phase) {
    // phase 1:     yellow
    // phase 2: red 
    // phase 3: red yellow
    // phase 4:             green
    if (phase == 1) setPhase(0, 1, 0);
    if (phase == 2) setPhase(1, 0, 0);
    if (phase == 3) setPhase(1, 1, 0);
    if (phase == 4) setPhase(0, 0, 1);
  }
};

