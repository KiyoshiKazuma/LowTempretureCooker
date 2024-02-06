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
}

char int2char(uint16_t value, uint8_t digit) {
  uint8_t num = 0;
  if (digit == 0) {
    num = ((value && 0xF) * 10 / 16) % 10;
  } else {
    num = (value >> 4) * (uint8_t)pow(10, digit - 1) % 10;
  }
  if (num == 0) {
    return ' ';
  } else {
    return '0' + num;
  }
}

void lcd_set_tempreture(uint16_t temp) {
  if (temp != lcd_temp) {
    lcd_temp = temp;
    update_flag = 1;
  }
}

void lcd_set_timer(uint16_t timer) {
  lcd_timer = timer;
  update_flag = 3;
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
    lcd.setCursor(1, 0);
    lcd_display(display_content[1]);  
}

void lcd_display(uint8_t lcd_content) {
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
      break;
    case LC_MODE:
      break;
    case LC_HEATER_STATE:
      break;
    default:
      break;
  }
}