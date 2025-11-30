// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch Blink_SOS.ino 
// Make Morse Code visible with LED

// https://docs.sunfounder.com/projects/raphael-kit/de/latest/c/3.1.10_morse_code_generator_c.html
// https://de.wikipedia.org/wiki/Morsecode

const int ledPin   = 2;
const int tonePin = 32;

#define RYT             (200)
#define DOT         (1 * RYT)
#define DASH       ( 3 * RYT)
#define P_TONE     ( 1 * RYT)  // e.g. "-.-"" means pause between "-" and next "."
#define P_LETTER   ( 3 * RYT)  // e.g. 1st letter "..." pause P_LETTER 2nd letter "---"
#define P_WORD     ( 7 * RYT)  // e.g. word "SOS" pause P_WORD word "HELP"

// Defining a new datatype called typeMorse
struct typeMorse{
  char letter;      // 1st elemnet holds Morse Letter like 'S'
  String code;      // 2nd elemnet holds Morse code like '010'; 0 for dot; 1 for dash
};

// Create an array morseDict[] from new datatype "typeMorse"
typeMorse morseDict[]=
{
  {'A',"01"},     {'B',"1000"},   {'C',"1010"},   {'D',"100"},    {'E',"0"},
  {'F',"0010"},   {'G',"110"},    {'H',"0000"},   {'I',"00"},     {'J',"0111"},
  {'K',"101"},    {'L',"0100"},   {'M',"11"},     {'N',"10"},     {'O',"111"},
  {'P',"0110"},   {'Q',"1101"},   {'R',"010"},    {'S',"000"},    {'T',"1"},
  {'U',"001"},    {'V',"0001"},   {'W',"011"},    {'X',"1001"},   {'Y',"1011"},
  {'Z',"1100"},   {'1',"01111"},  {'2',"00111"},  {'3',"00011"},  {'4',"00001"},
  {'5',"00000"},  {'6',"10000"},  {'7',"11000"},  {'8',"11100"},  {'9',"11110"},
  {'0',"11111"},  {'?',"001100"}, {'/',"10010"},  {',',"110011"}, {'.',"010101"},
  {';',"101010"}, {'!',"101011"}, {'@',"011010"}, {':',"111000"}
};
byte lengthMorseDict = 44;   // 44 items index 0 to 43

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("EBW-Workshop");
  
  // initialize digital pin ledPin as an output.
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // call the function morseCode with word "SOS"
  morseCode("SOS");
  Serial.println();
  delay(P_WORD);          // pause between words

  morseCode("HELP");
  Serial.println();
  delay(P_WORD);
}

// Turn the LED on
void on()  { 
  digitalWrite( ledPin, HIGH ); 
  tone(tonePin, 1000);
}
// Turn the LED off
void off() { 
  digitalWrite( ledPin, LOW );
  noTone(tonePin);
}

// function takes word and seperates letters and executes code
void morseCode( String _word){
  int lenWord = _word.length();           // how many letters has the word
  for ( int i = 0; i < lenWord; i++) {    // for each letter in word
    char _letter = _word[i];              // get the letter
    Serial.print( _letter );
    Serial.print(" ");

    String code = lookup( _letter );      // look for letter in morseDict[] and return code
    int lenCode = code.length();          // how many tones has the code

    for ( int j = 0; j < lenCode; j++){   // for each tone in code 
      if ( code[j] == '0') {              // "0 => dot"
        Serial.print('0');
        on(); delay(DOT); off(); delay(P_TONE);   // pause for P_TONE
      }

      if ( code[j] == '1') {              // "1 => dash"
        Serial.print('1');
        on(); delay(DASH); off(); delay(P_TONE);   // pause for P_TONE
      }
    }
    delay(P_LETTER);                              // pause for P_LETTER
    Serial.print(" ");
  }
}

// Look for letter in morseDict[] and return Morse Code
String lookup(char key) {
  byte k;
  for ( k = 0; k < lengthMorseDict; k++ ) {
    if( morseDict[k].letter == key) break;
  }
  return morseDict[k].code;
}

