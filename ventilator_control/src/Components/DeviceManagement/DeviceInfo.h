#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

/**
 * Structure written to the EEPROM, with information about the device,
 * to ensure unique identification of the devices in the field.
 * 
 * Data is only read out by the firmware and not written.
 * Writing the EEPROM with the DeviceInfo data is done by the bootloader
 * when uploading the firmware.
 */
typedef struct DeviceInfo
{
    char serialNumber[11];
    char productionDate[9];
    uint16_t crc;

    char *toString()
    {
        size_t bytes = snprintf(NULL, 0, "serialNumber: %s\nproductionDate: %s\n", this->serialNumber, this->productionDate);
        char *str = malloc(bytes);
        sprintf(str, "serialNumber: %s\nproductionDate: %s\n", this->serialNumber, this->productionDate);
        return str;
    }
} DeviceInfo;

#endif