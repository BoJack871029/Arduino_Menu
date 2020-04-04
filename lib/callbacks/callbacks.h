#ifndef __CALLBACKS_H
#define __CALLBACKS_H

#ifndef UNIT_TEST
#include <Arduino.h>
#endif

namespace callbacks
{
void showTemperatureSetup(void *iResourceManager);
void showDurationSetup(void *iResourceManager);
void doSetup(void *iResourceManager);
void moveUP(void *iResourceManager);
void moveDOWN(void *iResourceManager);
void moveIN(void *iResourceManager);
void moveBACK(void *iResourceManager);
void showMenu(void *iResourceManager);

void incrementTemperature(void *iResourceManager);
void decrementTemperature(void *iResourceManager);

void incrementDuration(void *iResourceManager);
void decrementDuration(void *iResourceManager);

} // namespace callbacks

#endif