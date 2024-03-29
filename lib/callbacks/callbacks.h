#ifndef __CALLBACKS_H
#define __CALLBACKS_H

#ifndef UNIT_TEST
#include <Arduino.h>
#else
#include "arduino-desktop.h"
#endif

namespace callbacks
{
void showReady(void *iResourceManager);

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