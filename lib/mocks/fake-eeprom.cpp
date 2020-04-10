#ifdef UNIT_TEST
#include <fake-eeprom.h>
#include <stdint.h>
#include <cstddef>
EEPROMClass::~EEPROMClass()
{
}

uint8_t EEPROMClass::read(const int iAddress)
{
    return 0;
};

void EEPROMClass::write(const int iAddress, uint8_t iValue)
{
}

void EEPROMClass::update(const int iAddress, uint8_t iValue)
{
}

#endif