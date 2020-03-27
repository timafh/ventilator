#ifndef SINGLEBUTTONMENU_H
#define SINGLEBUTTONMENU_H

#include <stdint.h>

#include <Arduino.h>

#include "../../globals.h"
#include "../../Interfaces/BaseTickableComponent.h"

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
