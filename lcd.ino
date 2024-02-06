#include <LiquidCrystal_I2C.h>
#include <math.h>
#include "common.h"

LiquidCrystal_I2C lcd(0x3F, 16, 2);

uint8_t display_content[2] = { LC_NONE, LC_NONE };

uint16_t lcd_temp;
uint16_t lcd_timer;
uint8_t update_flag;
uint8_t line1_cnt;
uint8_t line2_cnt;

void lcd_init(void) {
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  update_flag = 0;
  line1_cnt = 0x10;
  line2_cnt = 0x10;
  
  display_content[0]=LC_TEMP;
  display_content[1]=LC_TIMER;
}

void lcd_set_tempreture(uint16_t temp) {
  if (temp != lcd_temp) {
    lcd_temp = temp;
    update_flag = 1;
  }
}

void lcd_set_timer(uint16_t timer) {
  lcd_timer = timer;
  update_flag = 1;
}

void lcd_main(void) {
  if (update_flag) {
    lcd_update();
    update_flag = 0;
  }
}

void lcd_update(void){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd_display(display_content[0]);
    lcd.setCursor(0, 1);
    lcd_display(display_content[1]);  
}

void print_time(uint8_t num){
  if(num>=10){
    lcd.print(num);
  }else if(num<10){
    lcd.print(0);
    lcd.print(num);
  }
}
void lcd_display(uint8_t lcd_content) {
  uint8_t hour,min,sec;
  switch (lcd_content) {
    case LC_NONE:
      break;
    case LC_TEMP:
      lcd.print("temp : ");
      lcd.print(lcd_temp / 16);
      lcd.print(".");
      lcd.print(((lcd_temp * 10) / 16) % 10);
      lcd.print(" 'C");
      break;
    case LC_TIMER:
      hour=((lcd_timer/60)/60)%100;
      min=(lcd_timer/60)%60;
      sec=lcd_timer%60;

      lcd.print("TIME : ");
      print_time(hour);
      lcd.print(":");
      print_time(min);
      lcd.print(":");
      print_time(sec);

      break;
    case LC_MODE:
      break;
    case LC_HEATER_STATE:
      break;
    default:
      break;
  }
}