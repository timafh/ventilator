#ifndef VENTILATOR_H
#define VENTILATOR_H

#include <Arduino.h>
#include <Servo.h>

#include "../../Components/Configuration/ConfigurationManager.h"
#include "../LEDManager/LEDManager.h"

#include "../../Interfaces/BaseTickableComponent.h"

#include "../../pindesc.h"
//#include "../../globals.h"

#define MIN_SPEED 0
#define MAX_SPEED 180
#define PEEP_SPEED 40

class Ventilator : BaseTickableComponent
{
public:
    enum States
    {
        WAITING,
        SETUP,
        SETUP_SET_MAX,
        SETUP_WAIT_MAX,
        SETUP_SET_MIN,
        SETUP_WAIT_MIN,
        SETUP_FINISHED,
        RUNNING,
        PAUSED
    };

public:
    Ventilator() : cycleCounter(0), cyclePhase(0), timer(0), stateMachine(WAITING)
    {
    }

    void setup();
    void tick();

    void UpdateSettings();

    inline int getCycleCounter()
    {
        return this->cycleCounter;
    }

    inline void setCycleCounter(int value)
    {
        this->cycleCounter = value;
    }

    inline int getCyclePhase()
    {
        return this->cyclePhase;
    }

    inline void setCyclePhase(int value)
    {
        this->cyclePhase = value;
    }

    inline bool isInitialized()
    {
        return this->initialized;
    }

private:
    int cycleCounter;
    int cyclePhase;
    Servo servo;
    int targetSpeedLow;
    int targetSpeedHigh;

    bool initialized;

    int timer;

    Ventilator::States stateMachine;
};

extern Ventilator ventilator;

#endif
