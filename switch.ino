#include "common.h"

#define T_PUSH (10)
#define T_LONG_PUSH (40)
#define T_LONG_PUSHING (20)

uint8_t sw_state[PIN_SIZE];
uint8_t sw_cnt[PIN_SIZE];
uint8_t sw_pin[PIN_SIZE] = {
  PIN_1,
  PIN_2,
  PIN_3,
  PIN_4
};

void switch_init(void) {
  for (int i = 0; i < PIN_SIZE; i++) {
    sw_state[i] = SW_OFF;
    sw_cnt[i] = 0;
    ;
  }
}

void switch_main(void) {
  for (int i = 0; i < PIN_SIZE; i++) {
    uint8_t cur_state = digitalRead(sw_pin[i]);
    if (cur_state == LOW) {
      sw_cnt[i]++;
    }

    switch (sw_state[i]) {
      case SW_OFF:
        if (cur_state == LOW) {
          sw_state[i] = SW_ON;
        }
        sw_cnt[i] = 0;
        break;

      case SW_ON:
        if (cur_state != LOW) {
          sw_state[i] = SW_OFF;
        } else if (sw_cnt[i] > T_PUSH) {
          sw_state[i] = SW_PUSHING;
        }
        break;

      case SW_PUSHING:
        if (cur_state != LOW) {
          sw_state[i] = SW_PUSHED;
        } else if (sw_cnt[i] > T_LONG_PUSH) {
          sw_state[i] = SW_LONG_PUSH;
        }
        break;

      case SW_PUSHED:
        if (cur_state == LOW) {
          sw_state[i] = SW_PUSHING;
        }
        break;

      case SW_LONG_PUSH:
        if (cur_state != LOW) {
          sw_state[i] = SW_OFF;
        }
        break;

      case SW_LONG_PUSHING:
        if (cur_state != LOW) {
          sw_state[i] = SW_OFF;
        }
        break;

      default:
        sw_state[i] = SW_OFF;
        break;
    }
  }
}

uint8_t switch_read(uint8_t i) {
  switch (sw_state[i]) {
    case SW_PUSHED:
      sw_state[i]=SW_OFF;
      return 1;

    case SW_LONG_PUSH:
      sw_state[i]=SW_LONG_PUSHING;
      sw_cnt[i]-=T_LONG_PUSH;
      return 2;

    case SW_LONG_PUSHING:
      if(sw_cnt[i]>T_LONG_PUSHING){
        sw_cnt[i]-=T_LONG_PUSHING;
        return 3;
      }
      return 0;

    case SW_OFF:
    case SW_ON:
    case SW_PUSHING:
    default :
      return 0;
  }
}