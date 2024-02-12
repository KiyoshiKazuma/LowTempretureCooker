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

  enum lcd_contents{
  LC_NONE,
  LC_TEMP,
  LC_TIMER,
  LC_MODE,
  LC_HEATER_STATE,
  LC_INIT
};

void lcd_init(void);
void lcd_main(void);
void lcd_set_tempreture(uint16_t temp);
void lcd_set_timer(uint16_t timer);


#endif //_LCD_H_