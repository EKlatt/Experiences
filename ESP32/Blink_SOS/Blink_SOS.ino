#define LED_BUILTIN 2

short sos[] = {500, 500, 500, 1000, 1000, 1000, 500, 500, 500};
char  phase= 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {

  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(sos[phase]);                // wait ....

  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW                    
  if (phase == 8) delay(2000 );  else delay(200); // wait ....

  phase = phase + 1;
  if (phase == 9) phase = 0;
}
