#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H

#include <stdint.h>
#include <string.h>

#include <EEPROM.h>
#include <FastCRC.h>


#include "configuration.h"

#define MAGIC_BYTE_ADDRESS 0
#define CONFIGURATION_ADDRESS 1
#define DEVICEINFORMATION_ADDRESS CONFIGURATION_ADDRESS+sizeof(Configuration)



class ConfigurationManager {
    public:
        enum Error {
            OK,
            NOTOKAY,
            NOT_INITIALIZED,
            CRC_FAILED
        };

        ConfigurationManager();

        ConfigurationManager::Error ReadConfiguration();
        ConfigurationManager::Error WriteConfiguration();
        ConfigurationManager::Error VerifyConfiguration();

    private:
        uint16_t CalculateCRC();
        bool CheckIfWrittenBefore();
        void WriteMagicByte();

    public:
        Configuration* configuration;
};

#endif
