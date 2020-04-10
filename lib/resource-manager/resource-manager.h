#ifndef __RESOURCEMANAGER_H
#define __RESOURCEMANAGER_H

#ifndef UNIT_TEST
#include <Arduino.h>
#endif

namespace resource
{
enum TYPE
{
    LCD,
    MENU,
    KEYBOARD,
    FSM,
    TEMPERATURE,
    DURATION,
    EEPROM
};

struct Resource
{
    int _type;
    void *_value;
};

class Manager
{
public:
    void addResource(Resource *iResource);
    bool hasResource(resource::TYPE iType);
    void *get(int iType);

private:
    int _resourceLength = 0;
    Resource *_resources[10];
};
} // namespace resource
#endif