#include <inttypes.h>
#include <Arduino.h>
#include "controler.h"
#include "sensor.h"
#include "pin.h"
#include "switch.h"
#include "heater.h"
#include "lcd.h"
#include "timer.h"

void ctrl_heater(uint8_t temp);
void ctrl_timer_cbk(void);

double exp_tempreture = 60.0;
uint64_t ctrl_timer;
uint8_t stm;

void ctrl_init(void)
{
  stm = ST_INIT;
  timer_set_cbk(ctrl_timer_cbk);
  sensor_begin();
  ctrl_timer = 60 * 60 * 3;
}

uint8_t ctrl_get_stm(void)
{
  return stm;
}

void ctrl_main(void)
{
  static uint16_t ctrl_temp;

  uint8_t ctrl_sw_state[PIN_SIZE];

  for (uint8_t i = 0; i < PIN_SIZE; i++)
  {
    ctrl_sw_state[i] = switch_read(i);
  }
  Serial.println(stm);

  switch (stm)
  {
  case ST_INIT:
    heater_off();
    if (sensor_check_state() == 1)
    {
      lcd_set_content(0, LC_STM);
      lcd_set_content(1, LC_TEMP);
      lcd_set_content(2, LC_TIMER);
      ctrl_timer = 60 * 1; // 3h timer
      timer_set(ctrl_timer);
      lcd_set_timer(ctrl_timer);
      stm = ST_SETTING;
    }
    break;
  case ST_SETTING:
    if (ctrl_sw_state[SW_OK])
    {
      timer_start();
      stm = ST_RUNNING;
    }
    ctrl_temp = sensor_get_value();
    lcd_set_tempreture(ctrl_temp);
    break;
  case ST_RUNNING:
    ctrl_temp = sensor_get_value();
    ctrl_timer = timer_read();
    ctrl_heater(ctrl_temp);
    lcd_set_tempreture(ctrl_temp);
    lcd_set_timer(ctrl_timer);

    if (ctrl_sw_state[SW_CANCEL])
    {
      heater_off();
      timer_stop();
      stm = ST_SETTING;
    }
    break;
  case ST_STOP:
    heater_off();
    if (ctrl_sw_state[SW_OK])
    {
      stm = ST_INIT;
    }
    break;
  case ST_ERROR:
    heater_off();
    break;
  }
}

void ctrl_heater(uint8_t temp)
{
  if (temp < (uint16_t)(exp_tempreture * 16.0))
  {
    heater_on();
  }
  else
  {
    heater_off();
  }
}

void ctrl_timer_cbk(void)
{
  stm = ST_STOP;
  lcd_set_timer(0);
}