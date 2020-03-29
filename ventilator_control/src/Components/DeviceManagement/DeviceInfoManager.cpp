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
    Serial.println("Reading DeviceInfo");
    bool returnValue = false;
    uint8_t magicByte = EEPROM.read(DEVICE_INFO_MAGIC_BYTE_ADDRESS);
    if (magicByte != 0x01)
    {
        Serial.println("MagicByte not set, setting default device info.");
        strcpy(this->deviceInfo.serialNumber, "XXXXXXXXXX");
        strcpy(this->deviceInfo.productionDate, "19900101");
        this->deviceInfo.crc = 0;
        returnValue = false;
    }
    else
    {
        Serial.println("MagicByte set, reading device info from EEPROM.");
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
            Serial.println("Checksum failed. Setting default informations.");
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

    Serial.println(this->deviceInfo.toString());

    return returnValue;
}