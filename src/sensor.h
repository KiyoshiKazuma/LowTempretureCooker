#ifndef _SENSOR_H_
#define _SENSOR_H_
#include <stdint.h>

enum  {
  ST_SENSOR_STOP,
  ST_SENSOR_WAIT_CONNECT,
  ST_SENSOR_CONVERT,
  ST_SENSOR_WAIT_CONVERT,
  ST_SENSOR_READDATA
};
void sensor_init(void);
void sensor_main(void);
void sensor_begin(void);
void sensor_stop(void);
uint16_t sensor_get_value(void);
uint8_t sensor_check_state(void);

#endif // _SENSOR_H_