#ifndef COMMON_D
#define COMMON_D
  enum lcd_contents{
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

#endif //COMMON_D