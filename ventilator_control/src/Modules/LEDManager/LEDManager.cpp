#include "LEDManager.h"

void LEDManager::setup()
{
    this->leds[LED_INTERNAL_LED] = {
        PD_INFO_LED,
        OFF,
        LEDMODE_OFF,
        0};

    this->leds[LED_ALARM_LED] = {
        PD_ALARM_LED,
        OFF,
        LEDMODE_OFF,
        0};

    for (unsigned int i = 0; i < (sizeof(this->leds) / sizeof(this->leds[0])); i++)
    {
        pinMode(this->leds[i].LEDPin, OUTPUT);
        digitalWrite(this->leds[i].LEDPin, LOW);
    }
}

void LEDManager::tick()
{
}
