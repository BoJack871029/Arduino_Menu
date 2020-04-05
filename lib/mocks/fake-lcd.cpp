#ifdef UNIT_TEST
#include <fake-lcd.h>
#include <stdint.h>
#include <cstddef>
LiquidCrystal_I2C::~LiquidCrystal_I2C()
{
}

void LiquidCrystal_I2C::clear()
{
}

void LiquidCrystal_I2C::setCursor(uint8_t, uint8_t) {}

size_t LiquidCrystal_I2C::print(const String &)
{
    return 0;
};
#endif