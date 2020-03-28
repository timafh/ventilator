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
    for (unsigned int i = 0; i < (sizeof(this->leds) / sizeof(this->leds[0])); i++)
    {
        LED *led = &this->leds[i];
        if (led->mode == LEDMODE_OFF)
        {
            if (led->currentStatus != LOW)
            {
                digitalWrite(led->LEDPin, LOW);
                led->currentStatus = LOW;
            }
        }
        else if (led->mode == LEDMODE_ON)
        {

            if (led->currentStatus != HIGH)
            {
                digitalWrite(led->LEDPin, HIGH);
                led->currentStatus = HIGH;
            }

            if (led->duration > 0)
            {
                led->duration--;
            }
            else
            {
                led->mode = LEDMODE_OFF;
                led->duration = 0;
                led->currentStatus = LOW;
                digitalWrite(led->LEDPin, LOW);
            }
        }
        else if (led->mode == LEDMODE_FLASHING)
        {
            if (led->duration > 0)
            {
                led->duration--;
            }
            else
            {
                if (led->flashs > 0)
                {
                    led->flashCounter++;
                    if (led->flashCounter == led->flashs)
                    {
                        led->mode = LEDMODE_OFF;
                        led->duration = 0;
                        led->flashs = 0;
                        led->flashCounter = 0;
                    }
                }

                if (led->timedFlash)
                {
                    led->flashTimeSum -= led->flashDuration;

                    if (led->flashTimeSum <= 0)
                    {
                        led->mode = LEDMODE_OFF;
                        led->duration = 0;
                        led->flashs = 0;
                        led->flashCounter = 0;
                    }
                }
            }

            if (led->mode == LEDMODE_FLASHING)
            {
                led->currentStatus = led->currentStatus == HIGH ? LOW : HIGH;
                led->duration = led->flashDuration;
            }
            else
            {
                led->currentStatus = LOW;
            }

            digitalWrite(led->LEDPin, led->currentStatus);
        }
    }
}

void LEDManager::SwitchOff(uint8_t target)
{
    LED *led = &this->leds[target];
    led->mode = LEDMODE_OFF;
    led->duration = 0;
    led->flashs = 0;
    led->flashCounter = 0;
    led->currentStatus = LOW;
    digitalWrite(led->LEDPin, LOW);
}

void LEDManager::SwitchOn(uint8_t target)
{
    LED *led = &this->leds[target];
    led->mode = LEDMODE_ON;
    led->duration = 0;
    led->flashs = 0;
    led->flashCounter = 0;
    led->currentStatus = HIGH;
    digitalWrite(led->LEDPin, HIGH);
}

void LEDManager::SwitchOnWithDuration(uint8_t target, uint16_t duration)
{
    LED *led = &this->leds[target];
    led->mode = LEDMODE_ON;
    led->duration = duration;
    led->flashs = 0;
    led->flashCounter = 0;
    led->currentStatus = HIGH;
    digitalWrite(led->LEDPin, HIGH);
}

void LEDManager::Flash(uint8_t target, uint8_t duration, uint8_t time, uint8_t flashes)
{
    LED *led = &this->leds[target];
    led->mode = LEDMODE_FLASHING;
    led->flashDuration = duration;
    led->flashTimeSum = time;
    if (time > 0)
    {
        led->timedFlash = true;
    }
    led->duration = duration;

    led->flashs = flashes;
    led->flashCounter = 0;
    led->currentStatus = HIGH;
    digitalWrite(led->LEDPin, HIGH);
}