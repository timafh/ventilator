#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <stdint.h>

/**
 * @brief Configuration structure to read from eeprom or flash
 */
typedef struct Configuration {
    uint8_t debugMode : 1;
    uint8_t motorEnabled : 1;
    uint8_t spare : 6;

    uint8_t mode;

    uint16_t crc;
} Configuration;

#endif
