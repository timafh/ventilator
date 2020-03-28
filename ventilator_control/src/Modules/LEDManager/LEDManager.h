#ifndef LEDMANAGER_H
#define LEDMANAGER_H

#include <Arduino.h>
#include <stdint.h>

#include "../../pindesc.h"

#include "../../Interfaces/BaseTickableComponent.h"

#define LED_INTERNAL_LED 0
#define LED_ALARM_LED 1

#define ON HIGH
#define OFF LOW

class LEDManager : BaseTickableComponent
{
public:
    enum LEDMode
    {
        LEDMODE_FLASHING = 0,
        LEDMODE_ON = 1,
        LEDMODE_OFF = 2
    };
    struct LED
    {
        uint8_t LEDPin;
        uint8_t currentStatus;
        LEDMode mode;
        uint32_t duration;
        uint16_t flashs;
        uint16_t flashCounter;
    };

    void setup();

    void tick();

    void LEDManager::SwitchOff(uint8_t led);
    void LEDManager::SwitchOn(uint8_t led);
    void LEDManager::SwitchOnWithDuration(uint8_t led, uint16_t duration);
    void LEDManager::Flash(uint8_t led, uint8_t duration, uint8_t time = 0, uint8_t flashes = 0);

private:
    LED leds[2];
};

#endif
