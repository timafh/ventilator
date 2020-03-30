#include "LEDManager.h"

/**
 * Initializes the individual LEDs.
 * Initializes both the hardware pins and the necessary structures for the LEDManager.
 */
void LEDManager::setup()
{
    this->leds[LED::LED_INTERNAL_LED] = {
        PD_INFO_LED,
        OFF,
        LEDMODE_OFF,
        0};

    this->leds[LED::LED_ALARM_LED] = {
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

/**
 * Performs the actions requested by the SwitchOff, SwitchOn, SwitchOnWithDuration and Flash methods.
 * Is called from SysTick every 1 millisecond.
 */
void LEDManager::tick()
{
    for (unsigned int i = 0; i < (sizeof(this->leds) / sizeof(this->leds[0])); i++)
    {
        LEDInfo *led = &this->leds[i];
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

            if (led->duration != -1)
            {
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
}

/**
 * @brief Switches off the LED indicated as target.
 * 
 * @param target The LED to switch off
 */
void LEDManager::SwitchOff(uint8_t target)
{
    LEDInfo *led = &this->leds[target];
    led->mode = LEDMODE_OFF;
    led->duration = -1;
    led->flashs = 0;
    led->flashCounter = 0;
    led->currentStatus = LOW;
    digitalWrite(led->LEDPin, LOW);
    serialConsole.DebugOut(__FUNCTION__, "Switching off LED");
}

/**
 * @brief Switches on the LED indicated as target.
 * 
 * @param target The LED to switch on
 */
void LEDManager::SwitchOn(uint8_t target)
{
    LEDInfo *led = &this->leds[target];
    led->mode = LEDMODE_ON;
    led->duration = -1;
    led->flashs = 0;
    led->flashCounter = 0;
    led->currentStatus = HIGH;
    digitalWrite(led->LEDPin, HIGH);
    serialConsole.DebugOut(__FUNCTION__, "Switch on LED");
}

/**
 * @brief Switches on the LED specified as target and switches it off automatically after a time period specified as duration.
 * 
 * @param led The led to switch on and off
 * @param duration The time in milliseconds after which the LED is switched off again.
 */
void LEDManager::SwitchOnWithDuration(uint8_t target, uint16_t duration)
{
    LEDInfo *led = &this->leds[target];
    led->mode = LEDMODE_ON;
    led->duration = duration;
    led->flashs = 0;
    led->flashCounter = 0;
    led->currentStatus = HIGH;
    digitalWrite(led->LEDPin, HIGH);
    serialConsole.DebugOut(__FUNCTION__, "Switching on LED with duration");
}

/**
 * @brief Makes the LED indicated as target blink.
 * 
 * @param target The LED to blink
 * @param duration The timespan for each flash in milliseconds
 * @param time If not equal to 0: The total time in milliseconds
 *             for which the flashing is to be executed.
 *             After the time has expired, the LED is switched off .
 * @param flashes If not equal to 0: The total number of flashes to be executed.
 *                After reaching the number, the LED is switched off.
 */
void LEDManager::Flash(uint8_t target, uint8_t duration, uint8_t time, uint8_t flashes)
{
    LEDInfo *led = &this->leds[target];
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
    serialConsole.DebugOut(__FUNCTION__, "Activate LED flashing");
}
