#include "DeviceInfoManager.h"

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
bool DeviceInfoManager::ReadDeviceInfo()
{
    serialConsole.DebugOut("DeviceInfoManager::ReadDeviceInfo", "Start reading device infos");
    bool returnValue = false;
    uint8_t magicByte = EEPROM.read(DEVICE_INFO_MAGIC_BYTE_ADDRESS);
    if (magicByte != 0x01)
    {
        serialConsole.DebugOut("DeviceInfoManager::ReadDeviceInfo", "MagicByte not set, setting default device info.");
        strcpy(this->deviceInfo.serialNumber, "XXXXXXXXXX");
        strcpy(this->deviceInfo.productionDate, "19900101");
        this->deviceInfo.crc = 0;
        returnValue = false;
    }
    else
    {
        serialConsole.DebugOut("DeviceInfoManager::ReadDeviceInfo", "MagicByte set, reading device info from EEPROM.");
        EEPROM.get(DEVICE_INFO_ADDRESS, this->deviceInfo);
        uint16_t checksum = 0;
        for (int i = 0; i < strlen(this->deviceInfo.serialNumber); i++)
        {
            checksum += this->deviceInfo.serialNumber[i];
        }

        for (int i = 0; i < strlen(this->deviceInfo.productionDate); i++)
        {
            checksum += this->deviceInfo.productionDate[i];
        }

        if (this->deviceInfo.crc != checksum)
        {
            serialConsole.DebugOut("DeviceInfoManager::ReadDeviceInfo", "Checksum failed. Setting default informations.");
            strcpy(this->deviceInfo.serialNumber, "XXXXXXXXXX");
            strcpy(this->deviceInfo.productionDate, "19900101");
            this->deviceInfo.crc = 0;
            returnValue = false;
        }
        else
        {
            returnValue = true;
        }
    }

    serialConsole.DebugOut("DeviceInfoManager::ReadDeviceInfo", "Process finished.");
#ifdef DEBUG
    Serial.println(this->deviceInfo.toString());
#endif

    return returnValue;
}