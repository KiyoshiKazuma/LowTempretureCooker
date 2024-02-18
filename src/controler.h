#ifndef _CONTROLER_H_
#define _CONTROLER_H_
enum {
  ST_INIT,
  ST_TO_SETTING,
  ST_SETTING,
  ST_TO_RUNNING,
  ST_RUNNING,
  ST_STOP,
  ST_ERROR
};

enum{
  PRM_TIMER,
  PRM_TEMP
};

void ctrl_init(void);
void ctrl_main(void);
uint8_t ctrl_get_stm(void);

#endif //_CONTROLER_H_