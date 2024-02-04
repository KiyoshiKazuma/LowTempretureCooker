#include <MsTimer2.h>
#include <OneWire.h>
#include "common.h"

void TASK_INIT_2000(void);
void TASK_PRD_500(void);  //500ms task
void TASK_PRD_100(void);  //100ms task
void TASK(void);

uint8_t cnt_task;

void setup() {
  cnt_task=0;
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(PIN_DEBUG,OUTPUT);
  Serial.begin(9600);
  lcd_init();
  sensor_init();
  MsTimer2::set(100, TASK);
  MsTimer2::start();

  sensor_begin();
}

void loop() {
}

void TASK() {
  cnt_task++;

  TASK_PRD_100();

  if (cnt_task % 5 == 1) {  //500msタスク
    TASK_PRD_500();
  }
  if(cnt_task==20){
    TASK_INIT_2000();
  }
}

void TASK_PRD_100(void) {
  lcd_main();
  controler_main();
  sensor_main();
}
void TASK_PRD_500(void) {
  digitalWrite(13, !digitalRead(13));
}
void TASK_INIT_2000(void){
  lcd_enable();
}