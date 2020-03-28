#ifndef SINGLEBUTTONMENU_H
#define SINGLEBUTTONMENU_H

#include <stdint.h>

#include <Arduino.h>

#include "../../pindesc.h"
#include "../../Interfaces/BaseTickableComponent.h"
#include "../../Components/Configuration/ConfigurationManager.h"
#include "../Ventilator/Ventilator.h"
#include "../LEDManager/LEDManager.h"

class SingleButtonMenu : BaseTickableComponent
{
public:
    void setup();
    void tick();

private:
    uint8_t buttonState;
    uint8_t previousButtonState;
    uint8_t clickCount;
    uint8_t clickLoopCount;
    uint8_t loopCount;
};

#endif
