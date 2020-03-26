#ifndef ALARM_H
#define ALARM_H

/**
 * @brief Alarm represents a Alarm situation in the system.
 * It cointains an unique ID, a priority and two callback function pointers to define actions executed once the alarm has been
 * enabled or disabled.
 */
class Alarm
{
public:
    typedef void (*CallbackFunctionPointer)();
    // individual ID for each alarm
    int m_iAlarmId;

    // The priority of this alarm
    int m_iAlarmPriority;

    // a Callback to call, whenever this alarm is triggered (eg. to stop ventilation in case of an emergency)
    CallbackFunctionPointer m_pAlarmStartedCallback;
    // a Callback to call, whenever this alarm is stopped (eg. to restart ventilation after it was stopped by alarmStartedCallback)
    CallbackFunctionPointer m_pAlarmStoppedCallback;

public:
    Alarm(int id, int priority, CallbackFunctionPointer startedCallback, CallbackFunctionPointer stoppedCallback) : m_iAlarmId(id), m_iAlarmPriority(priority), m_pAlarmStartedCallback(startedCallback), m_pAlarmStoppedCallback(stoppedCallback)
    {
    }

    Alarm(int id, int priority) : m_iAlarmId(id), m_iAlarmPriority(priority), m_pAlarmStartedCallback(nullptr), m_pAlarmStoppedCallback(nullptr)
    {
    }

    inline friend bool operator==(const Alarm &lhs, const Alarm &rhs)
    {
        return lhs.m_iAlarmId == rhs.m_iAlarmId;
    }
};

#endif
