// #include <LiquidCrystal_I2C.h>
// #include <math.h>
// #include <string.h>
// #include "common.h"

// LiquidCrystal_I2C lcd(0x3F, 16, 2);

// enum lcd_contents display_content[2] = { LC_NONE, LC_NONE };

// uint16_t lcd_temp;
// uint16_t lcd_timer;
// uint8_t update_flag;
// char line1[16];
// char line2[16];

// void lcd_init(void) {
//   lcd.init();
//   lcd.begin(16, 2);
//   lcd.backlight();
//   lcd.setCursor(0, 0);
//   lcd.blink();
//   lcd.print("begin");
//   display_content[0] = LC_TEMP;
//   update_flag = 3;
// }

// char int2char(uint8_t value, uint8_t digit) {
//   uint8_t num = 0;
//   for (uint8_t i = 0; i < digit; i++) {
//     value /= 10;
//   }
//   num = value % 10;
//   return '0' + num;
// }


// void lcd_set_tempreture(uint16_t temp) {
//   lcd_temp = temp;
//   Serial.print("tempreture set :");
//   Serial.println(temp);
//   update_flag = 1;
// }

// void lcd_set_timer(uint16_t timer) {
//   lcd_timer = timer;
//   update_flag = 3;
// }

// void lcd_display(uint8_t line) {
//   Serial.print("temp:");
//   Serial.println(lcd_temp);
//   /*
//   if (line == 1) {
//     lcd.setCursor(0, 0);
//   }else if (line == 2) {
//     lcd.setCursor(1, 0);
//   }else{
//     return;
//   }
  
//   switch(display_content[line-1]){
//     case LC_TEMP:
//       lcd.print("temp:");
//       lcd.write(int2char((uint8_t)(lcd_temp>>4),2));
//       lcd.write(int2char((uint8_t)(lcd_temp>>4),1));
//       lcd.write(int2char((uint8_t)(lcd_temp>>4),0));
//     break;
//   }
//   */
// }

// void lcd_main(void) {
//   digitalWrite(PIN_DEBUG, HIGH);
//   Serial.println("lcd main start");
//   lcd.clear();
//   lcd.print("a");
//   /*
//   if (update_flag) {
//     if (update_flag && 0x1) {
//       lcd_display(1);
//     }
//     if (update_flag && 0x2) {
//       lcd_display(2);
//     }
//     update_flag = 0;
//   }
//   */
//   Serial.println("lcd main end");
//   digitalWrite(PIN_DEBUG, LOW);
// }

// void lcd_set_display(uint8_t line, uint8_t lcd_content) {
//   switch (line) {
//     case 1:
//     case 2:
//       switch (lcd_content) {
//         case LC_NONE:
//         case LC_TEMP:
//         case LC_TIMER:
//         case LC_MODE:
//         case LC_HEATER_STATE:
//           display_content[line] = lcd_content;
//           break;
//         default:
//           break;
//       }
//       break;
//     default:
//       break;
//   }
// }