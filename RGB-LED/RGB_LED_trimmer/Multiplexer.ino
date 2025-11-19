// https://www.youtube.com/watch?v=_biBagZ48Us
// Multiplexer control pins A, B, C
int multiPinA = 2;
int multiPinB = 3;
int multiPinC = 4;
int counter = 0;
// 
int bitA = 0;
int bitB = 0;
int bitC = 0;

void setupMulti() {
 pinMode(multiPinA, OUTPUT);
 pinMode(multiPinB, OUTPUT);
 pinMode(multiPinC, OUTPUT);
 Serial.begin(57600);
}

// function which gets analogvalues from multiplexer
void loopMulti () {
 for ( counter = 0; counter <= 7; counter++ ) {
  bitA = bitRead(counter, 0); bitB = bitRead(counter, 1); bitC = bitRead(counter, 2);
  digitalWrite(multiPinA, bitA); digitalWrite(multiPinB, bitB); digitalWrite(multiPinC, bitC);
  
  // values for calibration
  if (counter==0) redPotiCal   = analogRead(multiPlexPin);          // reading potentiometer analog-values   
  if (counter==1) greenPotiCal = analogRead(multiPlexPin);     
  if (counter==2) bluePotiCal  = analogRead(multiPlexPin); 
  // values for setting RGB-color  
  if (counter==4) redPoti      = analogRead(multiPlexPin);                           
  if (counter==5) greenPoti    = analogRead(multiPlexPin);
  if (counter==6) bluePoti     = analogRead(multiPlexPin);
  if (counter==7) brightPoti   = analogRead(multiPlexPin);
 } 
}
