#include <stdio.h>
#include "timer.h"
#include "lcd.h"

uint32_t timer_cnt;
uint8_t timer_state;
uint8_t timer_cnt_millis;

void (*p_timer_cbk_func)(void);

void timer_init(void)
{
    timer_cnt = 0;
    timer_state = 0;
    timer_cnt_millis = 0;
    p_timer_cbk_func = NULL;
}

void timer_main(void)
{ // prd in 100 ms
    switch (timer_state)
    {
    case TM_INIT:
        if (timer_cnt > 0)
        {
            timer_state = TM_STOP;
        }
        break;
    case TM_STOP:
        break;
    case TM_RUNNING:
        timer_cnt_millis++;
        if (timer_cnt_millis == 10)
        {
            timer_cnt--;
            timer_cnt_millis = 0;
        }
        if (timer_cnt == 0)
        {
            timer_state = TM_EXPIRATION;
            if (p_timer_cbk_func != NULL)
            {
                p_timer_cbk_func();
            }
        }
        break;
    case TM_EXPIRATION:
        if (timer_cnt > 0)
        {
            timer_state = TM_STOP;
        }
        break;
    default:
        timer_state = TM_INIT;
        break;
    }
}

void timer_set(uint32_t time){
    timer_cnt=time;
}

void timer_start(void){
    if(timer_state==TM_STOP){
        timer_state=TM_RUNNING;
    }
}

void timer_stop(void){
    if(timer_state==TM_RUNNING){
        timer_state=TM_STOP;
    }
}

uint32_t timer_read(void){
    return timer_cnt;
}

uint8_t timer_get_state(void){
    return timer_state;
}

void timer_set_cbk(void (* pfunc)(void)){
    p_timer_cbk_func=pfunc;
}