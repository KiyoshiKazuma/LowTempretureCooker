#include <MsTimer2.h>
#include <OneWire.h>

void TASK_1000(void);
void TASK_500(void);  //500ms task
void TASK_100(void);  //100ms task
void TASK_10(void);    //1ms task
void TASK(void);

uint32_t cnt_task;
bool task_lcd_flag;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  sensor_init();
  lcd_init();
  cnt_task=0;
  MsTimer2::set(10, TASK);
  MsTimer2::start();

  sensor_begin();
}

void loop() {
  if(task_lcd_flag){
    lcd_main();
    task_lcd_flag=false;
  }
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

}
void TASK_100(void) {
  sensor_main();
  controler_main();
}
void TASK_500(void) {
  digitalWrite(13, !digitalRead(13));
}

void TASK_1000(void) {
  static uint16_t time_cnt=0;
  time_cnt++;
  lcd_set_timer(time_cnt);
  task_lcd_flag=true;
}