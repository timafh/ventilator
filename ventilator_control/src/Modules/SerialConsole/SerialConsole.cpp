#include "SerialConsole.h"

void SerialConsole::setup()
{
    Serial.begin(SERIAL_BAUDRATE);
}

void SerialConsole::tick()
{
}

void SerialConsole::DebugOutf(const char *scope, char *format, ...)
{
    char *traverse;
    char *output = malloc(1);
    unsigned int i;
    char *s;

    va_list arg;
    va_start(arg, format);

    for (traverse = format; *traverse != '\0'; traverse++)
    {
        while (*traverse != '%')
        {
            void *tmp = realloc(output, strlen(output) + 1);
        }
    }
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