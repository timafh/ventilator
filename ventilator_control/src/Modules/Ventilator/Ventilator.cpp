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
        //TODO: SET LED ON
        break;
    case RUNNING:
        break;
    }
}