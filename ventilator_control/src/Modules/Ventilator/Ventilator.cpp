#include "Ventilator.h"

void Ventilator::setup()
{
    pinMode(MOTOR_CURRENT_PIN, INPUT);
    analogReference(INTERNAL);

    //TODO: disable LED

    stateMachine = SETUP;
}

void Ventilator::tick()
{
    switch (stateMachine)
    {
    case WAITING:
        break;
    case SETUP:
        Serial.println("Initializing ESC...");
        this->servo.attach(MOTOR_SERVO_PIN, 1000, 2000);
        this->stateMachine = SETUP_SET_MAX;

        //TODO: fast blink LED

        if (configurationManager.configuration->debugMode && !configurationManager.configuration->motorEnabled)
        {
            Serial.println("System is in debug mode and motor is disabled. Bypassing motor initialization.");
            this->stateMachine = SETUP_FINISHED;
        }

        break;
    case SETUP_SET_MAX:
        this->servo.write(MAX_SPEED);

        this->timer = 3000;
        this->stateMachine = SETUP_WAIT_MAX;
        break;
    case SETUP_WAIT_MAX:
        if (this->timer > 0)
        {
            this->timer--;
        }
        else
        {
            this->stateMachine = SETUP_SET_MIN;
        }
        break;
    case SETUP_SET_MIN:
        this->servo.write(MIN_SPEED);

        this->timer = 2000;
        this->stateMachine = SETUP_WAIT_MIN;
        break;
    case SETUP_WAIT_MIN:
        if (this->timer > 0)
        {
            this->timer--;
        }
        else
        {
            this->initialized = true;
            this->stateMachine = RUNNING;
        }
        break;
    case SETUP_FINISHED:
        this->servo.write(PEEP_SPEED);
        Serial.println("Done");
        this->UpdateSettings();
        //TODO: SET LED ON
        break;
    case RUNNING:
        // handle breath in/out cycle at target rate/min
        this->cycleCounter += 1;
        if ((30 * 100) / configurationManager.configuration->rate < this->cycleCounter)
        {
            this->cyclePhase = (this->cyclePhase + 1) % 2;
            this->cycleCounter = 0;

            // TODO: Serial Output using dedicated module
            /*Serial.print(loop_count / 100.0);
            Serial.print("\tphase speed:");*/
            if (this->cyclePhase == 0)
            {
                if (!configurationManager.configuration->debugMode || !configurationManager.configuration->motorEnabled)
                    this->servo.write(this->targetSpeedHigh);
                // TODO: Serial Output using dedicated module
                //Serial.println(target_speed_high);
            }
            else
            {
                if (!configurationManager.configuration->debugMode || !configurationManager.configuration->motorEnabled)
                    this->servo.write(this->targetSpeedLow);
                // TODO: Serial Output using dedicated module
                //Serial.println(target_speed_low);
            }
        }
        break;
    }
}

void Ventilator::UpdateSettings()
{

    // approximate pressure mapping fro original blower. Other blowers will vary
    // 40 ~= 5cm/H2O
    // 60 ~= 10cm/H2O
    // 90 ~= 18cm/H2O
    // 120 ~= 32cm/H2O

    if (configurationManager.configuration->speedState == 0)
    {
        this->targetSpeedHigh = 60;
        this->targetSpeedLow = PEEP_SPEED;
    }
    if (configurationManager.configuration->speedState == 1)
    {
        this->targetSpeedHigh = 70;
        this->targetSpeedLow = PEEP_SPEED;
    }
    if (configurationManager.configuration->speedState == 2)
    {
        this->targetSpeedHigh = 80;
        this->targetSpeedLow = PEEP_SPEED;
    }
    if (configurationManager.configuration->speedState == 3)
    {
        this->targetSpeedHigh = 90;
        this->targetSpeedLow = PEEP_SPEED;
    }
    if (configurationManager.configuration->speedState == 4)
    {
        this->targetSpeedHigh = 100;
        this->targetSpeedLow = PEEP_SPEED;
    }

    //CPAP mode, both speed are the same
    if (configurationManager.configuration->mode == 0)
        this->targetSpeedLow = this->targetSpeedHigh;
}