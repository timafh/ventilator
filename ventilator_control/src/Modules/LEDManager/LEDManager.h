#ifndef LEDMANAGER_H
#define LEDMANAGER_H

#include <Arduino.h>
#include <stdint.h>

#include "../../pindesc.h"

#include "../../Interfaces/BaseTickableComponent.h"
#include "../../Modules/SerialConsole/SerialConsole.h"

#define ON HIGH
#define OFF LOW

class LEDManager : BaseTickableComponent
{
public:
    enum LED
    {
        LED_INTERNAL_LED = 0,
        LED_ALARM_LED,
        LED_ALL
    };
    enum LEDMode
    {
        LEDMODE_FLASHING = 0,
        LEDMODE_ON = 1,
        LEDMODE_OFF = 2
    };
    struct LEDInfo
    {
        uint8_t LEDPin;
        uint8_t currentStatus;
        LEDMode mode;
        int32_t duration;
        uint16_t flashs;
        uint16_t flashCounter;
        uint32_t flashDuration;
        uint32_t flashTimeSum;
        bool timedFlash;
    };

    /**
     * Initializes the individual LEDs.
     * Initializes both the hardware pins and the necessary structures for the LEDManager.
     */
    void setup();

    /**
     * Performs the actions requested by the SwitchOff, SwitchOn, SwitchOnWithDuration and Flash methods.
     * Is called from SysTick every 1 millisecond.
     */
    void tick();

    /**
    * @brief Switches off the LED indicated as target.
    * 
    * @param target The LED to switch off
    */
    void SwitchOff(uint8_t target);

    /**
     * @brief Switches on the LED indicated as target.
     * 
     * @param target The LED to switch on
     */
    void SwitchOn(uint8_t target);

    /**
     * @brief Switches on the LED specified as target and switches it off automatically after a time period specified as duration.
     * 
     * @param led The led to switch on and off
     * @param duration The time in milliseconds after which the LED is switched off again.
     */
    void SwitchOnWithDuration(uint8_t led, uint16_t duration);

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
    void Flash(uint8_t led, uint8_t duration, uint8_t time = 0, uint8_t flashes = 0);

private:
    LEDInfo leds[LED::LED_ALL];
};

extern LEDManager ledManager;

#endif
