#ifndef SERIALCONSOLE_H
#define SERIALCONSOLE_H

#include <Arduino.h>
#include "../../Interfaces/BaseTickableComponent.h"

class SerialConsole : BaseTickableComponent
{

    void setup();
    void tick();
};

#endif