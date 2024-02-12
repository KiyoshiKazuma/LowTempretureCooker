#ifndef _CONTROLER_H_
#define _CONTROLER_H_
enum {
  ST_INIT,
  ST_SETTING,
  ST_RUNNING,
  ST_STOP,
  ST_ERROR
};

void ctrl_init(void);
void ctrl_main(void);
uint8_t ctrl_get_stm(void);

#endif //_CONTROLER_H_