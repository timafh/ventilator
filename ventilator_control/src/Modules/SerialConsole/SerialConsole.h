#ifndef SERIALCONSOLE_H
#define SERIALCONSOLE_H

#include <Arduino.h>
#include <stdarg.h>
#include <stdio.h>

#include "../../Interfaces/BaseTickableComponent.h"

#include "../../pindesc.h"

class SerialConsole : BaseTickableComponent
{
public:
    void setup();
    void tick();
    void DebugOut(const char *scope, const char *fmt, ...);
};

extern SerialConsole serialConsole;

#endif