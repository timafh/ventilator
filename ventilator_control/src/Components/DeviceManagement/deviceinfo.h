#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <stdint.h>

/**
 * Structure written to the EEPROM, with information about the device,
 * to ensure unique identification of the devices in the field.
 * 
 * Data is only read out by the firmware and not written.
 * Writing the EEPROM with the DeviceInfo data is done by the bootloader
 * when uploading the firmware.
 */
typedef struct DeviceInfo {
    char serialNumber[10];
    char productionDate[8];
    uint16_t crc;
} DeviceInfo;

#endif