#ifndef _SWITCH_H_
#define _SENSOR_H_
#include "pin.h"

#define T_PUSH (10)
#define T_LONG_PUSH (40)
#define T_LONG_PUSHING (20)

enum {
  SW_OFF,
  SW_ON,
  SW_PUSHING,
  SW_PUSHED,
  SW_LONG_PUSH,
  SW_LONG_PUSHING
};

enum{
    SW_OK=0,
    SW_CANCEL,
    SW_UP,
    SW_DOWN
};

void switch_init(void);
void switch_main(void);
uint8_t switch_read(uint8_t i);

#endif //_SENSOR_H_