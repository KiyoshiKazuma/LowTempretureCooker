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

#define LCD_LINE (3)

uint16_t lcd_temp;
uint16_t lcd_timer;

uint8_t lcd_flag = 0;
uint8_t lcd_content[3];

void lcd_init(void) {
  lcd_flag = 0;
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
  for (int i = 0; i < LCD_LINE; i++) {
    lcd_content[i] = LC_NONE;
  }
  display.clearDisplay();
  display.setTextSize(2);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(0, 0);              // Start at top-left corner
  display.cp437(true);                  // Use full 256 char 'Code Page 437' font
  display.print("begin");
  display.display();
}


void set_line(uint8_t line,uint8_t content){

}

void lcd_set_tempreture(uint16_t temp) {
  lcd_temp = temp;
  lcd_flag |= 1;
}

void lcd_set_timer(uint16_t timer) {
  lcd_timer = timer;
  lcd_flag |= 2;
}

void lcd_main(void) {
  display.clearDisplay();
  for (uint8_t line = 0; line < LCD_LINE; line++) {
    display.setCursor(0, 20 * line);
    switch (lcd_content[line]) {
      case LC_TEMP:
        lcd_print_temp();
        break;
      case LC_TIMER:
        lcd_print_timer();
        break;
      case LC_NONE:
      case LC_MODE:
      case LC_HEATER_STATE:
      default:
        break;
    }
  }
  display.display();
  lcd_flag = 0;
}

void lcd_print_temp(void) {
  display.print("temp:");
  display.print(lcd_temp / 16);
  display.print(".");
  display.print(((lcd_temp * 10) / 16) % 10);
}

void lcd_print_timer(void) {
  uint8_t hour, min, sec;
  hour = (lcd_timer / 60 / 60) % 100;
  min = (lcd_timer / 60) % 60;
  sec = lcd_timer % 60;

  display.setCursor(0, 20);
  display.print("T:");
  display.print(hour);
  display.print(":");
  display.print(min);
  display.print(":");
  display.print(sec);
}