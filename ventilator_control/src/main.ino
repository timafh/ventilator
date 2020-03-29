#include <Arduino.h>

#include "pindesc.h"

#include "Components/AlarmSystem/AlarmSystem.h"
#include "Components/Configuration/ConfigurationManager.h"
#include "Components/DeviceManagement/DeviceInfoManager.h"
#include "Modules/LEDManager/LEDManager.h"
#include "Modules/SingleButtonMenu/SingleButtonMenu.h"
#include "Modules/Ventilator/Ventilator.h"

// instanciate AlarmSystem
AlarmSystem alarmSystem;

// instanciate ConfigurationManager
ConfigurationManager configurationManager;
DeviceInfoManager deviceInfoManager;

SingleButtonMenu singleButtonMenu;
Ventilator ventilator;
LEDManager ledManager;

void setup()
{
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    sei();

    analogReference(INTERNAL); // sets reference to 1.1v

    Serial.begin(9600);

    delay(2000);

    configurationManager.ReadConfiguration();
    deviceInfoManager.ReadDeviceInfo();

    Serial.println("DEVICE DONE");

    singleButtonMenu.setup();
    ledManager.setup();
    ventilator.setup();
}

void loop()
{
    if (ventilator.isInitialized())
    {
    }
}

SIGNAL(TIMER0_COMPA_vect)
{
    ledManager.tick();
    ventilator.tick();
    singleButtonMenu.tick();
}