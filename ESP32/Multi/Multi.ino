// EBW: Experimentieren mit dem „ESP-32 Dev Kit C V2“
// Sketch Multi.ino 

void setup() {
  Serial.begin(115200);
  while(!Serial){}
  Serial.println("EBW-Workshop");
}
void loop() {
    static boolean done=false;
    if (!done){
        int a = 5;
        int b = 25;
        int s = 0;
        Serial.println(a);
        Serial.println(b);        

        while(a > 0) {
          if (a & 1) s += b;     // s = s + b;
            a = a >> 1;          // a = a / 2;
            b = b << 1;          // b = b * 2;
        }

        Serial.println(s);
        Serial.println("Done!");
        done=true;
    }
}

