#include "common.h"
double exp_tempreture =60.0;
uint8_t stm;
uint8_t st_running;

void controler_init(void) {
  stm = ST_INIT;
  sensor_begin();
}

void controler_main(void) {
  static uint16_t temp;
  Serial.println(stm);
  switch (stm) {
    case ST_INIT:
      if(sensor_check_state()==1){
        stm=ST_SETTING;
      }
      break;
    case ST_SETTING:
      stm=ST_RUNNING;
      break;
    case ST_RUNNING:
      temp=sensor_get_value();
      if(temp<(uint16_t)(exp_tempreture*16.0)){
        heater_on();
      }else{
        heater_off();
      }

      lcd_set_tempreture(temp);
      
      break;
    case ST_STOP:
      break;
    case ST_ERROR:
      break;
  }
}