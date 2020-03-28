#ifndef ALARMSYSTEM_H
#define ALARMSYSTEM_H

#include <stdint.h>

#include <Arduino.h>

#include "Alarm.h"
#include "../../Interfaces/BaseTickableComponent.h"
#include "../../Modules/LEDManager/LEDManager.h"

// TODO: Should the system handle multiple concurrent alarms or only one alarm at a time?
// Lets start withj one alarm at a time and later extend it to a fullblown alarm system.

/**
 * @brief AlarmSystem is the control component for Alarms within the system
 * 
 */
class AlarmSystem : BaseTickableComponent
{
public:
    /**
     * @brief Contains return stati for methods within this class.
     */
    enum Error
    {
        OK,
        ALARM_WAS_ACTIVE,
        NO_ACTIVE_ALARM,
        OTHER_ALARM_ACTIVE
    };

    AlarmSystem()
    {
    }

    /**
     * @brief 
     * 
     * @param alarm 
     * @return AlarmSystem::Error 
     */
    AlarmSystem::Error EnableAlarm(Alarm *alarm);

    /**
     * @brief 
     * 
     * @param alarm 
     * @return AlarmSystem::Error 
     */
    AlarmSystem::Error DisableAlarm(Alarm *alarm);

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    bool IsAlarmActive();

    /**
     * @brief 
     * 
     */
    void tick();

    /**
     * @brief Destroy the Alarm System object
     * 
     */
    ~AlarmSystem()
    {
        if (this->activeAlarm != nullptr)
        {
            this->DisableAlarm(this->activeAlarm);
        }
    }

private:
    /// the current active alarm. nullptr if no alarm is active
    Alarm *activeAlarm;

public:
    /// EXAMPLE_ALARM
    static Alarm *EXAMPLE_ALARM;
    /// EXAMPLE_ALARM2
    static Alarm *EXAMPLE2_ALARM;
};

extern AlarmSystem alarmSystem;

#endif
