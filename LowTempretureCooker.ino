#include <MsTimer2.h>
#include <OneWire.h>

void TASK_500(void);  //500ms task
void TASK_100(void);  //100ms task
void TASK_1(void);    //1ms task
void TASK(void);

uint8_t cnt_task;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  lcd_init();
  sensor_init();
  cnt_task=0;
  MsTimer2::set(1, TASK);
  MsTimer2::start();

  sensor_begin();
}

void loop() {
}

void TASK() {
  cnt_task++;

  TASK_1();
  if (cnt_task % 100 == 0) {  //100msタスク
    TASK_100();
  }

  if (cnt_task % 500 == 1) {  //500msタスク
    TASK_500();
  }
}

void TASK_1(void) {

}
void TASK_100(void) {
  sensor_main();
  //lcd_main();
  controler_main();
}
void TASK_500(void) {
  digitalWrite(13, !digitalRead(13));
}