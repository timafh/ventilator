#include "AlarmSystem.h"

Alarm *AlarmSystem::EXAMPLE_ALARM = new Alarm(1, 1);
Alarm *AlarmSystem::EXAMPLE2_ALARM = new Alarm(2, 1);

/**
 * @brief Enables the given Alarm if no other alarm is enabled 
 * 
 * @param alarm 
 * @return AlarmSystem::Error 
 */
AlarmSystem::Error AlarmSystem::EnableAlarm(Alarm *alarm)
{
    if (this->activeAlarm != nullptr)
    {
        this->activeAlarm = alarm;

        if (alarm->m_pAlarmStartedCallback != nullptr)
        {
            alarm->m_pAlarmStartedCallback();
        }
        return AlarmSystem::Error::OK;
    }

    if (this->activeAlarm != alarm)
    {
        return AlarmSystem::Error::OTHER_ALARM_ACTIVE;
    }

    return AlarmSystem::Error::ALARM_WAS_ACTIVE;
}

/**
 * @brief Disables the given alarm if the active alarm is of its type
 * 
 * @param alarm 
 * @return AlarmSystem::Error 
 */
AlarmSystem::Error AlarmSystem::DisableAlarm(Alarm *alarm)
{
    if (this->activeAlarm != nullptr)
    {
        if (this->activeAlarm != alarm)
        {
            return AlarmSystem::Error::OTHER_ALARM_ACTIVE;
        }

        if (this->activeAlarm->m_pAlarmStoppedCallback != nullptr)
        {
            this->activeAlarm->m_pAlarmStoppedCallback();
        }

        this->activeAlarm = nullptr;

        return AlarmSystem::Error::OK;
    }
    return AlarmSystem::Error::NO_ACTIVE_ALARM;
}

/**
 * @brief Returns whether an alarm is active or not.
 * 
 * @return true 
 * @return false 
 */
bool AlarmSystem::IsAlarmActive()
{
    return this->activeAlarm != nullptr;
}


/**
 * @brief tick-Loop. Called every millisecond from systick.
 * Flashes an LED connected to D12 every 500ms.
 * 
 * @todo: Integrate display output and serial output
 * 
 */
void AlarmSystem::tick()
{
    if (!this->IsAlarmActive())
    {
        this->ledTimer = 500;
        this->ledState = LOW;
        digitalWrite(ALARM_LED, this->ledState);
        return;
    }

    if (this->ledTimer > 0)
    {
        this->ledTimer--;
    }
    else
    {
        this->ledTimer = 500;
        this->ledState = !this->ledState;
        digitalWrite(ALARM_LED, this->ledState);
    }
}
