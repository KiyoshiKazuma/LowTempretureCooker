#include <LiquidCrystal_I2C.h>
#include <math.h>
#include <string.h>
#include "common.h"

LiquidCrystal_I2C lcd(0x3F, 16, 2);

enum lcd_contents display_content[2] = { LC_NONE, LC_NONE };

uint16_t lcd_temp;
uint16_t lcd_timer;
uint8_t update_flag;
char line1[16];
char line2[16];
char initstr[16]="init";

void lcd_init(void) {
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  strcpy(line1,initstr);
  update_flag=3;
}

char int2char(uint16_t value,uint8_t digit){
  uint8_t num =0;
  if(digit==0){
    num=((value&&0xF)*10/16)%10;
  }else{
    num=(value>>4)*(uint8_t)pow(10,digit-1)%10;
  }
  if(num==0){
    return ' ';
  }else{
    return '0'+num;
  }
}


void lcd_set_tempreture(uint16_t temp) {
  lcd_temp = temp;
  update_flag=3;
}

void lcd_set_timer(uint16_t timer) {
  lcd_timer = timer;
  update_flag=3;
}
/*
void lcd_set_line(void) {
  char * tmp=NULL;
  for (uint8_t i = 0; i < 2; i++) {
    if(i==0){
      tmp=line1;
      update_flag |= 1;
    }else if(i==1){
      tmp=line2;
      update_flag |= 2;
    }
    switch (display_content[i]) {
      case LC_NONE:
        tmp="";
        break;
      case LC_TEMP:
        tmp="temp:";
        tmp[5]=int2char(lcd_temp,3);
        tmp[6]=int2char(lcd_temp,2);
        tmp[7]=int2char(lcd_temp,1);
        tmp[8]='.';
        tmp[9]=int2char(lcd_temp,0);        
        break;
      case LC_TIMER:
        break;
      case LC_MODE:
        break;
      case LC_HEATER_STATE:
        break;
      case LC_INIT:
        tmp="STARTING";
        break;
    }
  }
}
*/
void lcd_display(uint8_t line) {
  if (line == 1) {
    lcd.setCursor(0, 0);
    lcd.printstr(line2);
  }
  if (line == 2) {
    lcd.setCursor(1, 0);
    lcd.printstr(line2);
  }
  Serial.println("LCD");
  Serial.println(line1);
  Serial.println(line2);
  
}

void lcd_main(void) {
  if (update_flag) {
    if (update_flag && 0x1) {
      lcd_display(1);
    }
    if (update_flag && 0x2) {
      lcd_display(2);
    }
    update_flag = 0;
  }
}

void lcd_set_display(uint8_t line, uint8_t lcd_content) {
  switch (line) {
    case 1:
    case 2:
      switch (lcd_content) {
        case LC_NONE:
        case LC_TEMP:
        case LC_TIMER:
        case LC_MODE:
        case LC_HEATER_STATE:
          display_content[line] = lcd_content;
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}