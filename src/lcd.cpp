#include <inttypes.h>
#include "lcd.h"
void lcd_print_temp(void);
void lcd_print_timer(void);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
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
  display.print("BEGIN");
  display.display();
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
  lcd_print_temp();
  lcd_print_timer();
  display.display();
  lcd_flag=0;
}

void lcd_print_temp(void) {
  display.setCursor(0, 0);
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