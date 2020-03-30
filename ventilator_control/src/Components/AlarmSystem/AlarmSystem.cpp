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
    // TODO: Add printf-Style arguments to DebugOut.
    serialConsole.DebugOut(__FUNCTION__, "Want to Enable Alarm");

    if (this->activeAlarm != nullptr)
    {
        this->activeAlarm = alarm;

        if (alarm->m_pAlarmStartedCallback != nullptr)
        {
            alarm->m_pAlarmStartedCallback();
            serialConsole.DebugOut(__FUNCTION__, "AlarmStartedCallback called");
        }

        serialConsole.DebugOut(__FUNCTION__, "Alarm enabled");
        return AlarmSystem::Error::OK;
    }

    if (this->activeAlarm != alarm)
    {
        serialConsole.DebugOut(__FUNCTION__, "Another alarm is already active: %s"); // TODO: Add printf-Style argument
        return AlarmSystem::Error::OTHER_ALARM_ACTIVE;
    }

    serialConsole.DebugOut(__FUNCTION__, "The requested alarm was already active.");
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
    serialConsole.DebugOut(__FUNCTION__, "Want to Disable Alarm");
    if (this->activeAlarm != nullptr)
    {
        if (this->activeAlarm != alarm)
        {
            serialConsole.DebugOut(__FUNCTION__, "Another alarm is already active.");
            return AlarmSystem::Error::OTHER_ALARM_ACTIVE;
        }

        if (this->activeAlarm->m_pAlarmStoppedCallback != nullptr)
        {
            serialConsole.DebugOut(__FUNCTION__, "Called AlarmStoppedCallback");
            this->activeAlarm->m_pAlarmStoppedCallback();
        }

        this->activeAlarm = nullptr;

        serialConsole.DebugOut(__FUNCTION__, "Alarm disabled");
        return AlarmSystem::Error::OK;
    }
    serialConsole.DebugOut(__FUNCTION__, "No alarm was active.");
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
    if (this->IsAlarmActive())
    {
        ledManager.Flash(LEDManager::LED::LED_ALARM_LED, 400, 0, 0);
        return;
    }
}
