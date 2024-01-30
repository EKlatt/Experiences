// RP2040 ZERO messure capacity
// https://www.elektronik-labor.de/OnlineRechner/Zeitkonstante.html
// https://www.rahner-edu.de/mikrocontroller/avr-controller-und-bascom/entladung-kondensator/
// https://elektro.turanis.de/html/prj080/index.html
// https://am.heise.de/abo/06_ma_education/kondensatormessger%C3%A4t.pdf?wt_mc=intern.abo.make.education.lp_ad.10.10
// https://www.az-delivery.de/blogs/azdelivery-blog-fur-arduino-und-raspberry-pi/prototyp-eines-kapazitatsmessgerates
// https://www.raspberry-pi-geek.de/ausgaben/rpg/2021/06/kapazitaetsmessung-von-kondensatoren/
// https://en.wikipedia.org/wiki/RC_time_constant
// https://arduino-pico.readthedocs.io/en/latest/analog.html

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define PIN_ANALOG    A0      // GPIO26
#define PIN_CHARGE    28      // GPIO28 PNP
#define PIN_DISCHARGE 29      // GPIO29 NPN
#define START_PIN     8       // GPIO8

#define SCREEN_WIDTH    128   // OLED display width, in pixels
#define SCREEN_HEIGHT   64    // OLED display height, in pixels
#define SCREEN_ADDRESS  0x3C  // OLED I2C address

uint16_t tau=2588;                   // RP2040 A0, 12 bit => 0 bis 4095
                                     // should be 63,2 % from 4095 (3.315V)=>2588
uint32_t resistorValue = 99840;      // init resistor value
uint32_t startTime, elapsedTime;
double   microFarads, nanoFarads;
uint16_t adc;
uint16_t counter;

// create "oled" as instance of class Adafruit_SSD1306
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//-------------------------------------------------------------------
// Delete row, in this case 6 rows (0 to 5) y = 0, 11, 22, 33, 44, 55 
// 30 characters/row
void clearText2Line(int line){
  int y= line * 11;
  oled.setTextColor(SSD1306_BLACK);
  oled.setCursor(0, y);
  for (int i=0; i<30; i++) {
    oled.write(0xDA);         // block character "DA"
  }
  oled.display();
  oled.setTextColor(SSD1306_WHITE);
}
//===================================================================

void setup(){
  Serial.begin(9600);
  oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);     // draw white text
  oled.setTextSize(1);                  // 30 character/row, 6 rows y = 0, 11, 22, 33, 44, 55 
  oled.print("EBW");
  oled.display();
     
  gpio_init(PIN_CHARGE);
  gpio_set_dir(PIN_CHARGE,GPIO_OUT);    // initialize PIN_CHARGE to OUTPUT
  gpio_put(PIN_CHARGE,1);               // set PIN_CHARGE to HIGH means "PNP" to "no charge"
                                        // must be "1", otherwise next step creates a short circuit
  gpio_init(PIN_DISCHARGE);             
  gpio_set_dir(PIN_DISCHARGE,GPIO_OUT);  // initialize PIN_DISCHARGE to OUTPUT
  gpio_put(PIN_DISCHARGE,0);             // set PIN_DISCHARGE to LOW means "NPN" to "no discharge"

  gpio_init(START_PIN); 
  gpio_set_dir(START_PIN,0);             // initialize START_PIN to INPUT
  gpio_pull_up(START_PIN);    

  adc_init();
  adc_gpio_init(PIN_ANALOG);             // initialize PIN_ANALOG
  adc_select_input(0);                   // first analog Input GPIO26         
}

void loop(){
  //---------------------- first discharge capacitor -------------------------------------
  discharge();
  // if we have a new plugged in capacitor 
  //---------------------- Wait for start button -----------------------------------------
  clearText2Line(5);
  while (1==gpio_get(START_PIN)){       // condition is true, if button pressed false
    oled.setCursor(0, 5*11); oled.print("Press button to start" ); oled.display();
  }
  //---------------------- second charge capacitor --------------------------------------                                        // will create a short circuit
  gpio_put(PIN_CHARGE, 0);              // set PIN_CHARGE to LOW "PNP" "to charge"
  startTime = time_us_32();             // begins the timer
  adc = adc_read();                     // may some capacity left

  oled.setCursor(0, 5*11); oled.print("adc:" ); oled.print(adc); oled.display();
  //---------------------- Getting load time ------------------------------------------------ 
  while(adc < tau) {                    // Does nothing until capacitor reaches guessed voltage                   

    clearText2Line(5);
    oled.setCursor(0, 5*11); oled.print("adc:" ); oled.print(adc); oled.display();
    elapsedTime = time_us_32() - startTime;   // Determines how much time it took to charge capacitor
    adc=adc_read();
  }
  //---------------------- Dispay elapsed time ---------------------------------------------- 
  clearText2Line(0); clearText2Line(1); clearText2Line(2);
  oled.setCursor(0,0*11); oled.print(elapsedTime); 
  oled.print(" MikroSec"); oled.display();
  //---------------------- Dispay capacitor value ------------------------------------------- 
  microFarads = (elapsedTime / resistorValue);    // T = RC => C = T/R
  if (microFarads > 1) {              // Determines if units should be micro or nano
    oled.setCursor(0,1*11); oled.print(microFarads);
    oled.print(" mikroF"); oled.display();

  } else {
    nanoFarads = microFarads * 1000.0;   
    oled.setCursor(0,2*11); oled.print(nanoFarads);
    oled.print(" nanoF"); oled.display();
  }
  //---------------------- Stop charging near to maximun voltage----------------------------- 
  clearText2Line(5);
  while (1==gpio_get(START_PIN)){       // condition is true, if button pressed false
    oled.setCursor(0, 5*11); oled.print("Press to stop" ); oled.display();
  }
  //---------------------- discharge capacitor -------------------------------------
  discharge();
}

// function for discharging capacitor
void discharge(){
  // Attention: IF PIN_CHARGE is (0) and PIN_DISCHARGE is (1) we create a short circuit!
  gpio_put(PIN_CHARGE, 1);              // Stops charging capacitor (PNP)
                                        // do not miss this step, otherwise we 
                                        // will create a short circuit   
  //---------------------- first discharge capacitor -------------------------------------
  gpio_put(PIN_DISCHARGE, 1);           // allows capacitor to discharge (NPN)
  while(adc_read() > 5) {               // do nothing until capacitor is discharged
    clearText2Line(5);
    oled.setCursor(0, 5*11); oled.print("dis:" ); oled.print(adc); oled.display();
  }

  gpio_put(PIN_DISCHARGE, 0);           // stop discharge capacitor (NPN)
                                        // do not miss this step, otherwise we
                                        // creare a short circuit   
}
