#include <inttypes.h>
#include <Arduino.h>
#include "controler.h"
#include "sensor.h"
#include "pin.h"
#include "switch.h"
#include "heater.h"
#include "lcd.h"

void ctrl_heater(uint8_t temp);

double exp_tempreture = 60.0;
uint8_t stm;

void ctrl_init(void) {
  stm = ST_INIT;
  sensor_begin();
}

uint8_t ctrl_get_stm(void){
    return stm;
}

void ctrl_main(void) {
  static uint16_t ctrl_temp;
  static uint16_t ctrl_timer;

  uint8_t ctrl_sw_state[PIN_SIZE];

  for(uint8_t i=0;i<PIN_SIZE;i++){
    ctrl_sw_state[i]=switch_read(i);
  }
  Serial.println(stm);

  switch (stm) {
    case ST_INIT:
      heater_off();
      if (sensor_check_state() == 1) {
        stm = ST_SETTING;
      }
      break;
    case ST_SETTING:
      if(ctrl_sw_state[SW_OK]){
        stm = ST_RUNNING;
      }
      ctrl_temp = sensor_get_value();
      lcd_set_tempreture(ctrl_temp);
      break;
    case ST_RUNNING:
      ctrl_temp = sensor_get_value();
      ctrl_heater(ctrl_temp);
      lcd_set_tempreture(ctrl_temp);
      
      if(ctrl_sw_state[SW_CANCEL]){
        heater_off();
        stm = ST_SETTING;
      }
      break;
    case ST_STOP:
        heater_off();
      break;
    case ST_ERROR:
        heater_off();
      break;
  }
}

void ctrl_heater(uint8_t temp) {
  if (temp < (uint16_t)(exp_tempreture * 16.0)) {
    heater_on();
  } else {
    heater_off();
  }
}