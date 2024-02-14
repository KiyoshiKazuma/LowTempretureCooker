#include <Arduino.h>
#include <MsTimer2.h>
#include <inttypes.h>
#include "task.h"
#include "sensor.h"
#include "controler.h"
#include "switch.h"

void TASK_1000(void); //1000ms task
void TASK_500(void);  //500ms task
void TASK_100(void);  //100ms task
void TASK_10(void);   //10ms task
void TASK(void);

bool task_lcd_flag=true;
static uint32_t cnt_task;

void task_init(void){    
  cnt_task=0;
  MsTimer2::set(10, TASK);  
  MsTimer2::start();
}

void TASK() {
  cnt_task++;

  TASK_10();
  if (cnt_task % 10 == 0) {  //100msタスク
    TASK_100();
  }

  if (cnt_task % 50 == 1) {  //500msタスク
    TASK_500();
  }
  
  if (cnt_task % 100 == 2) {  //1000msタスク
    TASK_1000();
  }
}

void TASK_10(void) {
  switch_main();
}
void TASK_100(void) {
  sensor_main();
  ctrl_main();
  //timer_main();
}
void TASK_500(void) {
  digitalWrite(13, !digitalRead(13));
}

void TASK_1000(void) {
  // static uint16_t time_cnt=0;
  // time_cnt++;
  // lcd_set_timer(time_cnt);
  task_lcd_flag=true;
  
  for(int i=0;i<4;i++){
    Serial.print(switch_read(i));
    Serial.print("  ");
  }
  Serial.println("");

}