#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// TODO: Maybe motor speed-pressure pair values should also be stored in EEPROM to keep the motor configuration away from the source code?

/**
 * @brief Configuration structure to read from eeprom or flash
 */
typedef struct Configuration
{
    uint8_t debugMode : 1;
    uint8_t motorEnabled : 1;
    uint8_t spare : 6;

    uint8_t mode;
    uint8_t speedState;
    uint8_t rate;

    uint8_t revision;
    uint16_t crc;

    char *toString()
    {
        size_t bytes = snprintf(NULL, 0, "debugMode: %i\nmotorEnabled: %i\nmode:%i\nspeedState: %i\nrate: %i", this->debugMode, this->motorEnabled, this->mode, this->speedState, this->rate);
        char *str = malloc(bytes);
        sprintf(str, "debugMode: %i\nmotorEnabled: %i\nmode:%i\nspeedState: %i\nrate: %i", this->debugMode, this->motorEnabled, this->mode, this->speedState, this->rate);
        return str;
    }
} Configuration;

#endif
