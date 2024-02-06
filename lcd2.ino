#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "common.h"

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES 10  // Number of snowflakes in the animation example

#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16

uint16_t lcd_temp;
uint16_t lcd_timer;

uint8_t lcd_flag = 0;

void lcd_init(void) {
  lcd_flag = 0;
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(2);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(0, 0);              // Start at top-left corner
  display.cp437(true);                  // Use full 256 char 'Code Page 437' font
  display.print("begin");
  display.display();
}

void lcd_set_update_flag(void) {
  lcd_flag |= 1;
}

// char int2char(uint8_t value, uint8_t digit) {
//   uint8_t num = 0;
//   for (uint8_t i = 0; i < digit; i++) {
//     value /= 10;
//   }
//   num = value % 10;
//   return '0' + num;
// }

void lcd_set_tempreture(uint16_t temp) {
  lcd_temp = temp;
  lcd_set_update_flag();
}

void lcd_set_timer(uint16_t timer) {
  lcd_timer = timer;
  lcd_set_update_flag();
}

void lcd_main(void) {
  if (lcd_flag) {
    display.clearDisplay();
    display.setCursor(0, 0);
    lcd_print_temp();
    lcd_flag = 0;
  }
}

void lcd_print_temp(void) {
  display.print("temp : ");
  display.print(lcd_temp/16);
  display.print(".");
  display.print(((lcd_temp*10)/16)%10);
  display.display();
}