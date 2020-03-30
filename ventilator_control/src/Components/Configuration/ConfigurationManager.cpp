#include "ConfigurationManager.h"

ConfigurationManager::ConfigurationManager()
{
    memset((void *)&this->configuration, 0, sizeof(Configuration));
}

/**
 * @brief Reads configuration from EEPROM and returns status
 * Also checks if the magic byte at position MAGIC_BYTE_ADDRESS
 * can be found and initializes the EEPROM with default values if not.
 * 
 * @return ConfigurationManager::Error 
 */
ConfigurationManager::Error ConfigurationManager::ReadConfiguration()
{

#ifdef DEBUG
#ifdef DEBUG_ERASE_EEPROM
    // Simple way to delete the EEPROM
    for (int i = 0; i < EEPROM.length(); i++)
    {
        EEPROM.write(i, 0);
    }
#endif
#endif

    serialConsole.DebugOut("ConfigurationManager::ReadConfiguration", "Reading configuration from EEPROM...");
    if (!this->CheckIfWrittenBefore())
    {
        serialConsole.DebugOut("ConfigurationManager::ReadConfiguration", "Magic byte not found. Was not initialized before...");

        // set standard values
        this->configuration.debugMode = 0;
        this->configuration.motorEnabled = 1;
        this->configuration.mode = 0;
        this->configuration.rate = 16;
        this->configuration.revision = 1;

        // write to eeprom
        // TODO: Check if write process was verified.
        this->WriteConfiguration();
        this->WriteMagicByte();
    }
    else
    {
        serialConsole.DebugOut("ConfigurationManager::ReadConfiguration", "Magic bytefound.");
    }
    serialConsole.DebugOut("ConfigurationManager::ReadConfiguration", "Reading from EEPROM...");
    EEPROM.get(CONFIGURATION_ADDRESS, this->configuration);
#ifdef DEBUG
    Serial.println(this->configuration.toString());
#endif
    serialConsole.DebugOut("ConfigurationManager::ReadConfiguration", "Process finished");
    return this->VerifyConfiguration();
}

/**
 * @brief Writes configuration to EEPROM and directly verifies writing process using CRC.
 * 
 * @return ConfigurationManager::Error 
 */
ConfigurationManager::Error ConfigurationManager::WriteConfiguration()
{
    serialConsole.DebugOut("ConfigurationManager::WriteConfiguration", "Writing configuration to EEPROM...");
    this->configuration.crc = CalculateCRC();
    EEPROM.put(CONFIGURATION_ADDRESS, this->configuration);

    Configuration validationConfig;
    EEPROM.get(CONFIGURATION_ADDRESS, validationConfig);

    if (validationConfig.crc != this->configuration.crc)
    {
        serialConsole.DebugOut("ConfigurationManager::WriteConfiguration", "Checksum for written data failed");

        return ConfigurationManager::Error::CRC_FAILED;
    }
    else
    {
        serialConsole.DebugOut("ConfigurationManager::WriteConfiguration", "Checksum for written data succeded");
    }

    serialConsole.DebugOut("ConfigurationManager::WriteConfiguration", "Process finished");

    return ConfigurationManager::Error::OK;
}

/**
 * @brief Verifies the crc of the current configuration object.
 * 
 * @return ConfigurationManager::Error 
 */
ConfigurationManager::Error ConfigurationManager::VerifyConfiguration()
{
    uint16_t calcedCRC = this->CalculateCRC();

    if (this->configuration.crc != calcedCRC)
        return ConfigurationManager::Error::CRC_FAILED;
    return ConfigurationManager::Error::OK;
}

/**
 * @brief Calculates CRC for the current configuration object without its CRC
 * 
 * @return uint16_t 
 */
uint16_t ConfigurationManager::CalculateCRC()
{
    uint16_t checksum = this->configuration.debugMode + this->configuration.motorEnabled + this->configuration.spare + this->configuration.mode + this->configuration.rate + this->configuration.speedState + this->configuration.revision;
    return checksum;
}

/**
 * @brief Checks if the EEPROM was written before
 * An 0x01 byte is written MAGIC_BYTE_ADDRESS of the EEPROM after the first writing process.
 * If the byte at MAGIC_BYTE_ADDRESS not equals 0x01, we assume that the EEPROM has not yet been written.
 * 
 * @return true if the magic byte was found
 * @return false if not
 */
bool ConfigurationManager::CheckIfWrittenBefore()
{
    uint8_t magicByte = EEPROM.read(MAGIC_BYTE_ADDRESS);
    if (magicByte != 0x01)
        return false;
    return true;
}

/**
 * @brief Writes the magic byte 0x01 at MAGIC_BYTE_ADDRESS of the EEPROM. * 
 */
void ConfigurationManager::WriteMagicByte()
{
    serialConsole.DebugOut("ConfigurationManager::WriteMagicByte", "Writing MagicByte");

    EEPROM.write(MAGIC_BYTE_ADDRESS, 0x01);
}