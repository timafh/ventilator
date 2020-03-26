#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H

#include <stdint.h>
#include <string.h>

#include <EEPROM.h>
#include <FastCRC.h>


#include "configuration.h"

#define MAGIC_BYTE_ADDRESS 0
#define CONFIGURATION_ADDRESS MAGIC_BYTE_ADDRESS + 1



class ConfigurationManager {
    public:
        enum Error {
            OK,
            NOTOKAY,
            NOT_INITIALIZED,
            CRC_FAILED
        };

        ConfigurationManager();

        /**
         * @brief Reads configuration from EEPROM and returns status
         * Also checks if the magic byte at position MAGIC_BYTE_ADDRESS
         * can be found and initializes the EEPROM with default values if not.
         * 
         * @return ConfigurationManager::Error 
         */
        ConfigurationManager::Error ReadConfiguration();

        /**
         * @brief Writes configuration to EEPROM and directly verifies writing process using CRC.
         * 
         * @return ConfigurationManager::Error 
         */
        ConfigurationManager::Error WriteConfiguration();

        /**
         * @brief Verifies the crc of the current configuration object.
         * 
         * @return ConfigurationManager::Error 
         */
        ConfigurationManager::Error VerifyConfiguration();
        
        ~ConfigurationManager() {
            configuration = nullptr;
        }

    private:
        /**
         * @brief Calculates CRC for the current configuration object without its CRC
         * 
         * @return uint16_t 
         */
        uint16_t CalculateCRC();

        /**
         * @brief Checks if the EEPROM was written before
         * An 0x01 byte is written MAGIC_BYTE_ADDRESS of the EEPROM after the first writing process.
         * If the byte at MAGIC_BYTE_ADDRESS not equals 0x01, we assume that the EEPROM has not yet been written.
         * 
         * @return true if the magic byte was found
         * @return false if not
         */
        bool CheckIfWrittenBefore();

        /**
        * @brief Writes the magic byte 0x01 at MAGIC_BYTE_ADDRESS of the EEPROM. * 
        */
        void WriteMagicByte();

    public:
        Configuration* configuration;
};

#endif
