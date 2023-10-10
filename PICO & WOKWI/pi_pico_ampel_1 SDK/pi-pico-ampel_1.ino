// pi-pico-ampel_1.ino
// SDK-commands
// https://arduino-pico.readthedocs.io/en/latest/
// https://arduino-pico.readthedocs.io/en/latest/sdk.html
// https://cec-code-lab.aps.edu/robotics/resources/pico-c-api/group__hardware__gpio.html
// https://www.youtube.com/watch?v=Duel_Oaases

#include "pico/stdlib.h"
uint8_t mainRed    = 6;     // GP6 main street
uint8_t mainYellow = 7;     // GP7
uint8_t mainGreen  = 8;     // GP8
uint8_t sideRed    = 10;    // GP10 side street
uint8_t sideYellow = 11;    // GP11
uint8_t sidegreen  = 12;    // GP12

uint32_t mask_main = 0x00000000;  //32 bit mask as Hex number
uint32_t mask_side = 0x00000000;

void setup() {
  Serial1.begin(115200);
  Serial1.println("EBW");

  // create a 32 bit-mask and set bits according to GPx-number 
  // GPx 29 - 0
  // GPx ... 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
  // 0b  ...  0  0  0  0  0  0  0  1  1  1  0  0  0  0  0  0          // sets GP8, GP7, GP6
  // mask_main = ( 0b0000000111000000 )                               // as Binary number
  // mask_main = ( 0x01C0 )                                           // as Hex number
  // mask_main = ( (1ul << 8) | (1ul << 7) | (1ul << 6 ) );           // "<<" bitshift left
                                                                      // "|"  bitwise or
                                                                      // "1ul" means force long unsigned
                                                                      // "long" is a 32 bit integer
  // mask_main = (1ul << mainRed) | (1ul << mainYellow) | (1ul << mainGreen );
  
  mask_main = (1ul << mainRed) | (1ul << mainYellow) | (1ul << mainGreen );
  mask_side = (1ul << sideRed) | (1ul << sideYellow) | (1ul << sidegreen );

  // instead of IDE pinMode() we use SDK-functions for setting OUTPUT-mode
  gpio_init_mask         ( mask_main | mask_side );   // SDK-function gpio_init_mask()
  gpio_set_dir_out_masked( mask_main | mask_side );   // SDK-function gpio_set_dir_out_masked()
}

void loop() {
  // phase 1:     yellow
  // phase 2: red 
  // phase 3: red yellow
  // phase 4:             GREEN

  // lights( mainPhase, sidePhase)
  lights( 1, 3 );
  lights( 2, 4 );   
  lights( 3, 1 );
  lights( 4, 2 );    
}

void lights(int mainPhase, int sidePhase) {       // red  yellow  green
  if (mainPhase == 1) setMaskMain (0, 1, 0);      //      yellow  
  if (mainPhase == 2) setMaskMain (1, 0, 0);      // red
  if (mainPhase == 3) setMaskMain (1, 1, 0);      // red  yellow
  if (mainPhase == 4) setMaskMain (0, 0, 1);      //              green

  if (sidePhase == 1) setMaskSide (0, 1, 0);      //      yellow  
  if (sidePhase == 2) setMaskSide (1, 0, 0);      // red
  if (sidePhase == 3) setMaskSide (1, 1, 0);      // red  yellow
  if (sidePhase == 4) setMaskSide (0, 0, 1);      //              green
  gpio_put_all (mask_main | mask_side);           // SDK
  
  if (mainPhase == 1) delay(1500);
  if (mainPhase == 2) delay(2500);  
  if (mainPhase == 3) delay(1500);  
  if (mainPhase == 4) delay(2500);          
}

void setMaskMain(int red, int yellow, int green){
  mask_main = 0;
  if (red    == 1) mask_main |= (1ul << mainRed);
  if (yellow == 1) mask_main |= (1ul << mainYellow);
  if (green  == 1) mask_main |= (1ul << mainGreen);  
}
void setMaskSide(int red, int yellow, int green){
  mask_side = 0;
  if (red    == 1) mask_side |= (1ul << sideRed);
  if (yellow == 1) mask_side |= (1ul << sideYellow);
  if (green  == 1) mask_side |= (1ul << sidegreen);  
}