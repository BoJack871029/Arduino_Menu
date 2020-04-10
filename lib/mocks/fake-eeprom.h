#ifdef UNIT_TEST
#include <arduino-desktop.h>
class EEPROMClass
{
public:
    virtual ~EEPROMClass();

    virtual uint8_t read(const int);

    virtual void write(const int, const uint8_t);

    virtual void update(const int, const uint8_t);
};

#endif