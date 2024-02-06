#include "common.h"

OneWire ds(10);

uint8_t addr[8];
uint8_t data[9];
uint16_t temp;
uint8_t sensor_stm;
uint8_t sensor_cnt;

void sensor_init(void) {
  sensor_stm = ST_SENSOR_STOP;
  temp=0;
}

void sensor_begin(void) {
  sensor_stm = ST_SENSOR_WAIT_CONNECT;
}

void sensor_stop(void){
  sensor_stm =ST_SENSOR_STOP;
}

uint16_t sensor_get_value(void){
  return temp;
}

uint8_t sensor_check_state(void){
  switch(sensor_stm){
    case ST_SENSOR_CONVERT:
    case ST_SENSOR_WAIT_CONVERT:
    case ST_SENSOR_READDATA:
      return 1;
    }
    return 0;
}

void sensor_main(void) {
  switch (sensor_stm) {
    case ST_SENSOR_WAIT_CONNECT:
      if (!ds.search(addr)) {
        ds.reset_search();
      } else {
        if (OneWire::crc8(addr, 7) != addr[7]) {
          Serial.print("CRC is not valid!\n");
        } else {
          Serial.print("addr : ");
          for (int i = 0; i < 8; i++) {
            Serial.print(addr[i], HEX);
            Serial.print(" ");
          }
          Serial.println();
          sensor_stm = ST_SENSOR_CONVERT;
        }
      }
      break;

    case ST_SENSOR_CONVERT:
      ds.reset();
      ds.select(addr);
      ds.write(0x44);
      sensor_stm = ST_SENSOR_WAIT_CONVERT;
      break;
    case ST_SENSOR_WAIT_CONVERT:
      if (sensor_cnt > 1) {
       sensor_stm = ST_SENSOR_READDATA;
        sensor_cnt = 0;
      }
      sensor_cnt++;
      break;
    case ST_SENSOR_READDATA:
      ds.reset();
      ds.select(addr);
      ds.write(0xBE);
      for (int i = 0; i < 9; i++) {  // we need 9 bytes
        data[i] = ds.read();
      }

      temp = (data[1] << 8) + data[0];
      sensor_stm=ST_SENSOR_CONVERT;
  }
}