#ifndef UNIT_TEST

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
    DURATION
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
    void *get(int iType);

private:
    int _resourceLength = 0;
    Resource *_resources[10];
};
} // namespace resource
#endif
#endif