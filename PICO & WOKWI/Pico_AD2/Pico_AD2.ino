//Pico_AD2 Diodentest
  
#include "pico/stdlib.h"
#include "hardware/adc.h"

void setup() {
  int iir=0;
  Serial.begin(115200);
  adc_init();
  adc_gpio_init(26);
  gpio_pull_up(26);
  adc_select_input(0);
  uint32_t t = time_us_32(); 
  while(true){
    uint32_t ad = adc_read()*3300/4095;
    for (int n=0; n<10; n++){
      ad = adc_read()*3300/4095;
      iir = (iir*9+ad)/10;       
    }
    Serial.println(iir);
    sleep_ms(500);
  }
} 

void loop() {
}
