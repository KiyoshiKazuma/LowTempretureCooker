#include <inttypes.h>
#include "lcd.h"
#include "pin.h"
#include "controler.h"
#include "heater.h"

void lcd_print_temp(void);
void lcd_print_timer(void);
void lcd_print_stm(void);
void lcd_print_heater_state(void);
void lcd_print_content(uint8_t content);
void lcd_update_blink(void);

struct s_lcd_flag
{
  unsigned update : 5;
  unsigned en_blink : 1;
  unsigned st_blink : 1;
};

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
s_lcd_flag lcd_flag;
uint16_t lcd_temp;
uint16_t lcd_timer;
uint8_t lcd_heater_state;
uint8_t lcd_blink_line;
uint8_t lcd_blink_cnt;
uint8_t lcd_contents[LCD_ROW];

void lcd_init(void)
{
  lcd_flag.update = 0;
  lcd_flag.st_blink = 0;
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);             // Start at top-left corner
  display.cp437(true);                 // Use full 256 char 'Code Page 437' font
  display.print("BEGIN");
  display.display();
  for (int i = 0; i < LCD_ROW; i++)
  {
    lcd_contents[i] = LC_NONE;
  }
}

void lcd_main(void)
{
  lcd_update_blink();
  if (lcd_flag.update)
  {
    display.clearDisplay();
    for (uint8_t i = 0; i < LCD_ROW; i++)
    {
      if (lcd_flag.en_blink == 1 && lcd_blink_line == i)
      {
        if (lcd_flag.st_blink == 1)
        {
          display.setCursor(0, i * 10);
          lcd_print_content(lcd_contents[i]);
        }
      }
      else
      {
        display.setCursor(0, i * 10);
        lcd_print_content(lcd_contents[i]);
      }
    }
    display.display();
    lcd_flag.update = 0;
  }
}

void lcd_set_tempreture(uint16_t temp)
{
  lcd_temp = temp;
  lcd_flag.update |= 0x01;
}

void lcd_set_timer(uint16_t timer)
{
  lcd_timer = timer;
  lcd_flag.update |= 0x02;
}

void lcd_set_heater_state(uint8_t on_off)
{
  lcd_heater_state = on_off;
  lcd_flag.update |= 0x04;
}

void lcd_set_content(uint8_t line, uint8_t content)
{
  if (line < LCD_ROW)
  {
    lcd_contents[line] = content;
    lcd_flag.update |= 0x08;
  }
}

void lcd_print_content(uint8_t content)
{
  switch (content)
  {

  case LC_NONE:
    break;
  case LC_TEMP:
    lcd_print_temp();
    break;
  case LC_TIMER:
    lcd_print_timer();
    break;
  case LC_STM:
    lcd_print_stm();
    break;
  case LC_HEATER_STATE:
    lcd_print_heater_state();
    break;
  case LC_INIT:
    break;

  default:
    break;
  }
}

void lcd_set_blink(uint8_t line)
{
  lcd_flag.en_blink = 1;
  lcd_blink_line = line;
}
void lcd_stop_blink(void)
{
  lcd_flag.en_blink = 0;
  lcd_flag.st_blink = 0;
  lcd_blink_cnt = 0;
}

void lcd_print_temp(void)
{
  display.print("Temp :");
  display.print(lcd_temp / 10);
  display.print(".");
  display.print(lcd_temp % 10);
  display.print(" C");
}

void lcd_print_timer(void)
{
  uint8_t hour, min, sec;
  hour = (lcd_timer / 60 / 60) % 100;
  min = (lcd_timer / 60) % 60;
  sec = lcd_timer % 60;
  display.print("Timer:");
  if (hour < 10)
  {
    display.print(0);
  }
  display.print(hour);
  display.print(":");
  if (min < 10)
  {
    display.print(0);
  }
  display.print(min);
  display.print(":");
  if (sec < 10)
  {
    display.print(0);
  }
  display.print(sec);
}

void lcd_print_stm(void)
{
  display.print("Mode :");
  switch (ctrl_get_stm())
  {
  case ST_INIT:
    display.print("INIT check sensor");
    break;
  case ST_SETTING:
    display.print("SETTING");
    break;
  case ST_RUNNING:
    display.print("RUNNING");
    break;
  case ST_STOP:
    display.print("STOP");
    break;
  case ST_ERROR:
    display.print("ERROR");
    break;
  default:
    break;
  }
}

void lcd_print_heater_state(void)
{
  if (lcd_heater_state)
  {
    display.print("POWER:ON");
  }
  else
  {
    display.print("POWER:OFF");
  }
}

void lcd_update_blink(void)
{
  if (lcd_flag.en_blink)
  {
    if (lcd_blink_cnt > BLINK_CYCLE)
    {
      lcd_blink_cnt = 0;
      lcd_flag.st_blink ^= 1;
      lcd_flag.update |= 1;
    }
    lcd_blink_cnt++;
  }
}