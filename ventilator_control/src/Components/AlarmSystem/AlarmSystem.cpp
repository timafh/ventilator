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
    serialConsole.DebugOut(__FUNCTION__, "Want to Enable Alarm %i", alarm->m_iAlarmId);

    if (this->activeAlarm != nullptr)
    {
        this->activeAlarm = alarm;

        if (alarm->m_pAlarmStartedCallback != nullptr)
        {
            alarm->m_pAlarmStartedCallback();
            serialConsole.DebugOut(__FUNCTION__, "AlarmStartedCallback called for alarm %i", alarm->m_iAlarmId);
        }

        serialConsole.DebugOut(__FUNCTION__, "Alarm enabled");
        return AlarmSystem::Error::OK;
    }

    if (this->activeAlarm != alarm)
    {
        serialConsole.DebugOut(__FUNCTION__, "Another alarm is already active: %i", this->activeAlarm->m_iAlarmId);
        return AlarmSystem::Error::OTHER_ALARM_ACTIVE;
    }

    serialConsole.DebugOut(__FUNCTION__, "The requested alarm (%i) was already active.", alarm->m_iAlarmId);
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
    serialConsole.DebugOut(__FUNCTION__, "Want to Disable Alarm %i", alarm->m_iAlarmId);
    if (this->activeAlarm != nullptr)
    {
        if (this->activeAlarm != alarm)
        {
            serialConsole.DebugOut(__FUNCTION__, "Another alarm (%i) is already active.", this->activeAlarm->m_iAlarmId);
            return AlarmSystem::Error::OTHER_ALARM_ACTIVE;
        }

        if (this->activeAlarm->m_pAlarmStoppedCallback != nullptr)
        {
            serialConsole.DebugOut(__FUNCTION__, "Called AlarmStoppedCallback for alarm %i", alarm->m_iAlarmId);
            this->activeAlarm->m_pAlarmStoppedCallback();
        }

        this->activeAlarm = nullptr;

        serialConsole.DebugOut(__FUNCTION__, "Alarm %i disabled", alarm->m_iAlarmId);
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
