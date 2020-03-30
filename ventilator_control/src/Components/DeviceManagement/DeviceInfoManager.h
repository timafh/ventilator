#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <EEPROM.h>

#include "DeviceInfo.h"
#include "../Configuration/ConfigurationManager.h"
#include "../../Modules/SerialConsole/SerialConsole.h"

#define DEVICE_INFO_MAGIC_BYTE_ADDRESS CONFIGURATION_ADDRESS + sizeof(Configuration)
#define DEVICE_INFO_ADDRESS DEVICE_INFO_MAGIC_BYTE_ADDRESS + 1

class DeviceInfoManager
{
public:
    DeviceInfoManager()
    {
        memset(&this->deviceInfo, 0, sizeof(DeviceInfo));
    }

    /**
         * Reads the device information from the EEPROM and verifies the CRC checksum
         * The read data is stored in deviceInfo.
         * 
         * Returns true if the device information was readable and false if not.
         * In the event of an error, standard data (serial number XXXXXXXXX and date of manufacture 19900101)
         * is stored in deviceInfo.
         * 
         * @return true sucess
         * @return false not successful
         */
    bool ReadDeviceInfo();

public:
    DeviceInfo deviceInfo;
};

#endif