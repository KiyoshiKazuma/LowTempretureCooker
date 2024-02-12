#ifndef COMMON_D
#define COMMON_D
enum {
  LC_NONE,
  LC_TEMP,
  LC_TIMER,
  LC_MODE,
  LC_HEATER_STATE,
  LC_INIT
};

enum sensor_states {
  ST_SENSOR_STOP,
  ST_SENSOR_WAIT_CONNECT,
  ST_SENSOR_CONVERT,
  ST_SENSOR_WAIT_CONVERT,
  ST_SENSOR_READDATA
};

enum mode_states {
  ST_INIT,
  ST_SETTING,
  ST_RUNNING,
  ST_STOP,
  ST_ERROR
};

enum {
  SW_OFF,
  SW_ON,
  SW_PUSHING,
  SW_PUSHED,
  SW_LONG_PUSH,
  SW_LONG_PUSHING
};

#define PIN_SIZE (4)

#define PIN_1 (7)
#define PIN_2 (6)
#define PIN_3 (5)
#define PIN_4 (8)

#define SW_OK (0)
#define SW_CANCEL (1)
#define SW_UP (2) 
#define SW_DOWN (3) 


#endif //COMMON_D