#ifndef UNIT_TEST

#ifndef __MENU_CALLBACKS_H
#define __MENU_CALLBACKS_H

#ifndef UNIT_TEST
#include <Arduino.h>
#endif

namespace menu_callbacks
{
void showTemperatureSetup(void *iResourceManager);
void showDurationSetup(void *iResourceManager);
void doSetup(void *iResourceManager);
} // namespace menu_callbacks

#endif
#endif