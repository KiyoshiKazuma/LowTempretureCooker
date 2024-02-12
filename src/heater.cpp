#include <Arduino.h>
#include "heater.h"
#include "pin.h"

void heater_init(void)
{
    pinMode(PIN_HEATER, OUTPUT);
    heater_off();
}

void heater_on(void)
{
    digitalWrite(PIN_HEATER, HIGH);
}
void heater_off(void)
{
    digitalWrite(PIN_HEATER, LOW);
}