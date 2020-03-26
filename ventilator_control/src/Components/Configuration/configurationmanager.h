#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H

#include <stdint.h>

#include "configuration.h"



class ConfigurationManager {
    public:
        enum Error {
            OK,
            NOTOKAY
        };

        ConfigurationManager() {

        }

        ConfigurationManager::Error ReadConfiguration();
        ConfigurationManager::Error WriteConfiguration();
        ConfigurationManager::Error VerifyConfiguration();

    private:
        uint16_t CalculateCRC();

    public:
        Configuration* configuration;
};

#endif
