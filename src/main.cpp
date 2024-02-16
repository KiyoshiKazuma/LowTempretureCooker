#include <Arduino.h>
#include "task.h"
#include "pin.h"
#include "sensor.h"
#include "heater.h"
#include "lcd.h"
#include "controler.h"
#include "switch.h"
#include "timer.h"

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);

  timer_init();
  switch_init();
  ctrl_init();
  lcd_init();
  heater_init();
  sensor_begin();
  task_init();
}

void loop()
{
  if (task_lcd_flag)
  {
    lcd_main();
    task_lcd_flag = false;
  }
}
