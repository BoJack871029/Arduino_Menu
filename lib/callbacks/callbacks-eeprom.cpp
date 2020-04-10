
#ifndef UNIT_TEST
#include <Arduino.h>
#include <debug.h>
#include <EEPROM.h>
#else
#include <iostream>
#include <fake-eeprom.h>
#endif
#include <callbacks-eeprom.h>
#include <resource-manager.h>

namespace callbacks
{
namespace eeprom
{
void readSettingsFromEEPROM(void *iResourceManager)
{
    LOG_INFO("Callback: readSettingsFromEEPROM");
    if (iResourceManager != 0)
    {
        resource::Manager *aManager = (resource::Manager *)iResourceManager;
        EEPROMClass *aEeprom = (EEPROMClass *)aManager->get(resource::TYPE::EEPROM);

        int *aTemperature = (int *)aManager->get(resource::TYPE::TEMPERATURE);
        int *aDuration = (int *)aManager->get(resource::TYPE::DURATION);

        *aTemperature = aEeprom->read(EEPROM_TEMPERATURE_ADDRESS);
        *aDuration = aEeprom->read(EEPROM_DURATION_ADDRESS);
    }
}

void writeSettingsToEEPROM(void *iResourceManager)
{
    LOG_INFO("Callback: readSettingsFromEEPROM");
    if (iResourceManager != 0)
    {
        resource::Manager *aManager = (resource::Manager *)iResourceManager;
        EEPROMClass *aEeprom = (EEPROMClass *)aManager->get(resource::TYPE::EEPROM);

        int *aTemperature = (int *)aManager->get(resource::TYPE::TEMPERATURE);
        int *aDuration = (int *)aManager->get(resource::TYPE::DURATION);

        aEeprom->update(EEPROM_TEMPERATURE_ADDRESS, (uint8_t)*aTemperature);
        aEeprom->update(EEPROM_DURATION_ADDRESS, (uint8_t)*aDuration);
    }
}
} // namespace eeprom
} // namespace callbacks