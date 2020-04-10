#ifdef UNIT_TEST
#include <arduino-desktop.h>
class LiquidCrystal_I2C
{
public:
    virtual ~LiquidCrystal_I2C();

    virtual void clear();

    virtual void setCursor(uint8_t, uint8_t);

    virtual size_t print(const String &);

    virtual size_t print(const int &);
};
#endif