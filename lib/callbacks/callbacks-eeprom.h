#ifndef __CALLBACKS_EEPROM_H
#define __CALLBACKS_EEPROM_H

#ifndef UNIT_TEST
#include <Arduino.h>
#else
#include "arduino-desktop.h"
#endif

namespace callbacks
{
namespace eeprom
{
static const int EEPROM_TEMPERATURE_ADDRESS = 0;
static const int EEPROM_DURATION_ADDRESS = 1;

void readSettingsFromEEPROM(void *iResourceManager);
void writeSettingsToEEPROM(void *iResourceManager);
} // namespace eeprom
} // namespace callbacks
#endif