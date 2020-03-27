#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <stdint.h>

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

    uint8_t revision;
    uint16_t crc;
} Configuration;

#endif
