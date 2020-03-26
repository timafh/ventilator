#include "deviceinfomanager.h"

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
bool DeviceInfoManager::ReadDeviceInfo() {
    uint8_t magicByte = EEPROM.read(DEVICE_INFO_MAGIC_BYTE_ADDRESS);
    if(magicByte != 0x01) {

        strcpy(this->deviceInfo->serialNumber, "XXXXXXXXXX");
        strcpy(this->deviceInfo->productionDate, "19900101");
        this->deviceInfo->crc = 0;
        return false;
    } else {
        EEPROM.get(DEVICE_INFO_ADDRESS, this->deviceInfo);
        FastCRC16 CRC16;
        uint16_t calculatedCRC =  CRC16.ccitt((uint8_t*)this->deviceInfo, sizeof(DeviceInfo) - sizeof(uint16_t));
        if(this->deviceInfo->crc != calculatedCRC) {
            strcpy(this->deviceInfo->serialNumber, "XXXXXXXXXX");
            strcpy(this->deviceInfo->productionDate, "19900101");
            this->deviceInfo->crc = 0;
            return false;
        }
        return true;
    }  
}