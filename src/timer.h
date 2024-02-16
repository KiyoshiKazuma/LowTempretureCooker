#ifndef _TIMER_H_
#define _TIMER_H_
#include <inttypes.h>

enum
{
    TM_INIT,
    TM_STOP,
    TM_RUNNING,
    TM_EXPIRATION
};

void timer_init(void);
void timer_main(void); // prd in 100 ms
void timer_set(uint32_t time);
void timer_start(void);
void timer_stop(void);
uint32_t timer_read(void);
uint8_t timer_get_state(void);
void timer_set_cbk(void (*pfunc)(void));

#endif // _TIMER_H_