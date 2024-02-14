#include <inttypes.h>
#include <Arduino.h>
#include "controler.h"
#include "sensor.h"
#include "pin.h"
#include "switch.h"
#include "heater.h"
#include "lcd.h"
#include "timer.h"

void ctrl_heater(uint16_t temp);
void ctrl_timer_cbk(void);

uint16_t exp_tempreture = 600;
uint32_t ctrl_timer;
uint16_t ctrl_temp;
uint8_t stm;
uint8_t prm_select;

void ctrl_heater_on(void)
{
  lcd_set_heater_state(HEATER_ON);
  heater_on();
}

void ctrl_heater_off(void)
{
  lcd_set_heater_state(HEATER_OFF);
  heater_off();
}

void ctrl_update_timer(void)
{
  uint32_t tmp_timer = timer_read();
  if (tmp_timer != ctrl_timer)
  {
    ctrl_timer = tmp_timer;
    lcd_set_timer(ctrl_timer);
  }
}

void ctrl_update_temp(void)
{
  uint16_t tmp_temp = sensor_get_value();
  if (tmp_temp != ctrl_temp)
  {
    ctrl_temp = tmp_temp;
    lcd_set_tempreture(ctrl_temp);
  }
}

void ctrl_init(void)
{
  stm = ST_INIT;
  timer_set_cbk(ctrl_timer_cbk);
  sensor_begin();
}

uint8_t ctrl_get_stm(void)
{
  return stm;
}

void ctrl_main(void)
{

  uint8_t ctrl_sw_state[PIN_SIZE];

  for (uint8_t i = 0; i < PIN_SIZE; i++)
  {
    ctrl_sw_state[i] = switch_read(i);
  }
  Serial.println(stm);

  switch (stm)
  {
  case ST_INIT:
    ctrl_heater_off();
    ctrl_timer = 60 * 60 * 3;
    prm_select = PRM_TEMP;
    if (sensor_check_state() == 1)
    {
      lcd_set_content(0, LC_STM);
      lcd_set_content(1, LC_TEMP);
      lcd_set_content(2, LC_TIMER);
      lcd_set_content(3, LC_HEATER_STATE);
      timer_set(ctrl_timer);
      lcd_set_timer(ctrl_timer);
      stm = ST_SETTING;
    }
    break;
  case ST_SETTING:
    if (ctrl_sw_state[SW_CANCEL] == SW_PUSHED)
    {
      stm = ST_INIT;
    }
    if (ctrl_sw_state[SW_OK])
    {
      timer_start();
      stm = ST_RUNNING;
    }

    switch (prm_select)
    {
    case PRM_TEMP:
      if (ctrl_sw_state[SW_CANCEL] == SW_LONG_PUSH)
      {
        prm_select = PRM_TIMER;
      }
      if (ctrl_sw_state[SW_UP])
      {
        if (exp_tempreture < 1000)
        {
          exp_tempreture += 10;
        }
      }
      if (ctrl_sw_state[SW_DOWN])
      {
        if (exp_tempreture > 0)
        {
          exp_tempreture -= 10;
        }
      }
      lcd_set_tempreture(exp_tempreture);

      break;
    case PRM_TIMER:
      if (ctrl_sw_state[SW_CANCEL] == SW_LONG_PUSH)
      {
        prm_select = PRM_TEMP;
      }
      if (ctrl_sw_state[SW_UP])
      {
        if (ctrl_timer < 6 * 60 * 60)
        {
          ctrl_timer += 600;
        }
      }
      if (ctrl_sw_state[SW_DOWN])
      {
        if (ctrl_timer > 0)
        {
          ctrl_timer -= 600;
        }
      }
      lcd_set_timer(ctrl_timer);
      break;

    default:
      prm_select = PRM_TEMP;
      break;
    }

    break;
  case ST_RUNNING:
    ctrl_update_timer();
    ctrl_update_temp();
    ctrl_heater(ctrl_temp);

    if (ctrl_sw_state[SW_CANCEL])
    {
      ctrl_heater_off();
      timer_stop();
      stm = ST_SETTING;
    }
    break;
  case ST_STOP:
    ctrl_heater_off();
    if (ctrl_sw_state[SW_OK])
    {
      stm = ST_INIT;
    }
    break;
  case ST_ERROR:
    ctrl_heater_off();
    break;
  }
}

void ctrl_heater(uint16_t temp)
{
  if (temp < exp_tempreture)
  {
    ctrl_heater_on();
  }
  else
  {
    ctrl_heater_off();
  }
}

void ctrl_timer_cbk(void)
{
  stm = ST_STOP;
  lcd_set_timer(0);
}