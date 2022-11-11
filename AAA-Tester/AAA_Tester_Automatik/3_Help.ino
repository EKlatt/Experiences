// functions which defines Help
// german version
void help(){
  Serial.println(F( "AATiS AA-Tester bereit"));
  Serial.println(F( "Hilfe-Text           'h'"));
  Serial.println(F( "Drehe Stepper        'Druecke rechte Taste'"));
  Serial.println(F( "Starte automatisch   'Druecke linke Taste"));   
  Serial.println(F( "Automatik            'a' or 'auto'"));       
  Serial.println(F( "Zeit?                'time'"));
  Serial.println(F( "Lese config.ini      'r'")); 
  Serial.println(F( "Zeige config.ini     'i'"));          
  Serial.println(F( "Falle initialiseren  'ti'"));
  Serial.println(F( "Batterie vorhanden?  'b'"));
  Serial.println(F( "Anliegende Spannung  'v'"));    
  Serial.println(F( "Last-Kreis an/aus    'l' or 'last'"));    
  Serial.println(F( "Syntax fuer Falle    't:90' or trap:0/5/.../90"));
  Serial.println(F( "Syntax fuer Stepper  's:90' or stepper:512/1024/.../2048"));
}

// english version
//void help(){
//  Serial.println(F( "AATiS AA-Tester ready"));
//  Serial.println(F( "Help-Text            'h'"));
//  Serial.println(F( "Move stepper         'Press right button'"));
//  Serial.println(F( "Start automatic      'Press left button'"));   
//  Serial.println(F( "Automatic            'a' or 'auto'"));       
//  Serial.println(F( "Time                 'time'"));
//  Serial.println(F( "File read config     'r'")); 
//  Serial.println(F( "Show config-data     'i'"));          
//  Serial.println(F( "Initialize trap      'ti'"));
//  Serial.println(F( "Battery present      'b'"));
//  Serial.println(F( "Present voltage      'v'"));    
//  Serial.println(F( "Stress circuit       'l' or 'load'"));    
//  Serial.println(F( "Syntax of trap       't:90' or trap:0/5/.../90"));
//  Serial.println(F( "Syntax of stepper    's:90' or stepper:512/1024/.../2048"));
//}
