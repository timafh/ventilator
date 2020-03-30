#ifndef SERIALCONSOLE_H
#define SERIALCONSOLE_H

#include <Arduino.h>
#include "../../Interfaces/BaseTickableComponent.h"

#include "../../pindesc.h"

class SerialConsole : BaseTickableComponent
{
public:
    void setup();
    void tick();
    void DebugOut(const char *scope, const char *message);
    void DebugOutf(const char *scope, const char *format, ...);
};

extern SerialConsole serialConsole;

#endif