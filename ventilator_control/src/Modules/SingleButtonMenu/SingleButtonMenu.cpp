#include "SingleButtonMenu.h"

void SingleButtonMenu::setup()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void SingleButtonMenu::tick()
{
    this->previousButtonState = this->buttonState;
    this->buttonState = digitalRead(BUTTON_PIN);

    if (this->buttonState == LOW && this->previousButtonState == 1)
    {
        this->clickLoopCount = this->loopCount;
        this->clickCount++;
    }

    if (this->clickCount > 0)
    {
        if (this->clickLoopCount + 30 < this->loopCount)
        {
            if (this->clickCount == 1)
            {
                // Single click

                configurationManager.configuration->speedState = (configurationManager.configuration->speedState + 1) % 5;
                if (configurationManager.configuration->mode == 0)
                {
                    // cycle_counter = 10000;
                    // TODO: implement ventilation module and set cycleCounter
                }
            }
            else if (this->clickCount == 2)
            {
                // Double Click
                configurationManager.configuration->mode = (configurationManager.configuration->mode + 1) % 2;

                // cycle_counter = 10000;
                // cycle_phase = 0;
                // TODO: implement ventilation module and set cycleCounter and cyclePhase
            }

            // blink LED
            // TODO: Move to led manager to prevent delays
            digitalWrite(INFO_LED, LOW);
            delay(50);
            digitalWrite(INFO_LED, HIGH);

            // print state
            // TODO: move to own module
            Serial.print(this->loopCount / 100.0);
            if (configurationManager.configuration->mode == 0)
            {
                Serial.print("\tset to CPAP level: ");
                Serial.println(configurationManager.configuration->speedState);
            }
            if (configurationManager.configuration->mode == 1)
            {
                Serial.print("\tset to PEEP level: ");
                Serial.print(configurationManager.configuration->speedState);
                Serial.print("\tforced rate: ");
                Serial.print(configurationManager.configuration->rate);
                Serial.println("/min");
            }
            this->clickCount = 0;
        }
    }

    this->loopCount++;
}