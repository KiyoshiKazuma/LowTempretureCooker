#ifndef _LCD_H_
#define _LCD_H_
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
#define NUMFLAKES 10  // Number of snowflakes in the animation example
#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16

#define LCD_ROW (6)
#define BLINK_CYCLE (1)

  enum lcd_contents{
  LC_NONE,
  LC_TEMP,
  LC_TIMER,
  LC_STM,
  LC_HEATER_STATE,
  LC_INIT
};

void lcd_set_content(uint8_t line,uint8_t content);
void lcd_init(void);
void lcd_main(void);
void lcd_set_tempreture(uint16_t temp);
void lcd_set_timer(uint16_t timer);
void lcd_set_heater_state(uint8_t on_off);
void lcd_set_blink(uint8_t line);
void lcd_stop_blink(void);

#endif //_LCD_H_