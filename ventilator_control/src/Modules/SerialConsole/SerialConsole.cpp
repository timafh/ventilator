#include "SerialConsole.h"

void SerialConsole::setup()
{
    Serial.begin(SERIAL_BAUDRATE);
}

void SerialConsole::tick()
{
}

void SerialConsole::DebugOutf(const char *scope, char *fmt, ...)
{
#ifdef DEBUG
    va_list va;
    va_start(va, fmt);
    char buf[vsnprintf(NULL, 0, fmt, va) + 1];
    vsprintf(buf, fmt, va);
    va_end(va);

    DebugOut(scope, buf);
#endif
}

void SerialConsole::DebugOut(const char *scope, const char *message)
{
#ifdef DEBUG
    size_t length = strlen(scope) + strlen(message);
    char *msg = (char *)malloc(length + 11);
    sprintf(msg, "[DEBUG][%s]: %s", scope, message);
    Serial.println(msg);
    free(msg);
#endif
}