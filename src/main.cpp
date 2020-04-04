#ifndef UNIT_TEST
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <keyboard.h>
#include <menu.h>
#include <menu_callbacks.h>
#include <callbacks.h>
#include <fsm.h>
#include <resource-manager.h>
#include <MemoryFree.h>
#include <debug.h>

int _keyboardRowsPin[] = {2, 3, 4, 5, 6};
int _keyboardColsPin[] = {8, 9, 10, 11};
int _keyboardRowsPinLength = sizeof(_keyboardRowsPin) / sizeof(int);
int _keyboardColsPinLength = sizeof(_keyboardColsPin) / sizeof(int);

LiquidCrystal_I2C _lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,16,2) for 16x2 LCD.

menu::MenuItem _menuItems[] = {{"Temperatura", menu_callbacks::showTemperatureSetup}, {"Durata", menu_callbacks::showDurationSetup}, {"Setup", menu_callbacks::doSetup}};

keyboard::Keyboard _keyboard = keyboard::Keyboard(_keyboardRowsPin, _keyboardRowsPinLength, _keyboardColsPin, _keyboardColsPinLength);

menu::Menu _menu = menu::Menu(&_lcd, _menuItems, (sizeof(_menuItems) / sizeof(_menuItems[0])));

fsm::Fsm _fsm;
resource::Manager _resourcesManager;

int _temperature = 85;
int _duration = 5;

resource::Resource _resourceMenu = {resource::TYPE::MENU, &_menu};
resource::Resource _resourceKeyboard = {resource::TYPE::KEYBOARD, &_keyboard};
resource::Resource _resourceLcd = {resource::TYPE::LCD, &_lcd};
resource::Resource _resourceFsm = {resource::TYPE::FSM, &_fsm};
resource::Resource _resourceTemperature = {resource::TYPE::TEMPERATURE, &_temperature};
resource::Resource _resourceDuration = {resource::TYPE::DURATION, &_duration};

resource::Resource *_resources[] = {&_resourceMenu, &_resourceKeyboard, &_resourceLcd, &_resourceFsm, &_resourceTemperature, &_resourceDuration};

fsm::Event _mappingKeyEvent[20] = {fsm::Event::NO_EVENT, fsm::Event::NO_EVENT, fsm::Event::NO_EVENT, fsm::Event::NO_EVENT, fsm::Event::OPEN_MENU, fsm::Event::NO_EVENT, fsm::Event::NO_EVENT, fsm::Event::NO_EVENT, fsm::Event::NO_EVENT, fsm::Event::NO_EVENT, fsm::Event::NO_EVENT, fsm::Event::NO_EVENT, fsm::Event::NO_EVENT, fsm::Event::NO_EVENT, fsm::Event::NO_EVENT, fsm::Event::ENTER, fsm::Event::BACK, fsm::Event::DOWN, fsm::Event::UP, fsm::Event::NO_EVENT};

void setup()
{
  Serial.begin(9600);
  LOG_INFO("Initialization..");

  for (resource::Resource *aResource : _resources)
  {
    _resourcesManager.addResource(aResource);
  }

  _fsm.setResourceManger(&_resourcesManager);
  _menu.setResourceManger(&_resourcesManager);
  DEFINE_TRANSITION(_fsm, fsm::State::INIT, fsm::State::READY, fsm::Event::BEGIN, callbacks::showReady);
  DEFINE_TRANSITION(_fsm, fsm::State::READY, fsm::State::MENU, fsm::Event::OPEN_MENU, callbacks::showMenu);
  DEFINE_TRANSITION(_fsm, fsm::State::MENU, fsm::State::MENU, fsm::Event::UP, callbacks::moveUP);

  DEFINE_TRANSITION(_fsm, fsm::State::MENU, fsm::State::MENU, fsm::Event::DOWN, callbacks::moveDOWN);
  DEFINE_TRANSITION(_fsm, fsm::State::MENU, fsm::State::SETTINGS, fsm::Event::ENTER, callbacks::moveIN);
  DEFINE_TRANSITION(_fsm, fsm::State::TEMPERATURE, fsm::State::MENU, fsm::Event::BACK, callbacks::moveBACK);
  DEFINE_TRANSITION(_fsm, fsm::State::DURATA, fsm::State::MENU, fsm::Event::BACK, callbacks::moveBACK);
  DEFINE_TRANSITION(_fsm, fsm::State::SETUP, fsm::State::MENU, fsm::Event::BACK, callbacks::moveBACK);
  DEFINE_TRANSITION(_fsm, fsm::State::MENU, fsm::State::READY, fsm::Event::BACK, callbacks::showReady);

  DEFINE_TRANSITION(_fsm, fsm::State::TEMPERATURE, fsm::State::TEMPERATURE, fsm::Event::UP, callbacks::incrementTemperature);
  DEFINE_TRANSITION(_fsm, fsm::State::TEMPERATURE, fsm::State::TEMPERATURE, fsm::Event::DOWN, callbacks::decrementTemperature);
  DEFINE_TRANSITION(_fsm, fsm::State::DURATA, fsm::State::DURATA, fsm::Event::UP, callbacks::incrementDuration);
  DEFINE_TRANSITION(_fsm, fsm::State::DURATA, fsm::State::DURATA, fsm::Event::DOWN, callbacks::decrementDuration);

  _keyboard.init();

  _lcd.begin();

  LOG_INFO_VALUE("Initialization DONE. MemoryFree = ", getFreeMemory());

  _menu.display();

  _fsm.exec(fsm::Event::BEGIN);
}

void loop()
{
  int aKeyPressed = _keyboard.getKeyPressed();

  if (aKeyPressed != -1)
  {
    fsm::Event aEvent = _mappingKeyEvent[aKeyPressed];

    _fsm.exec(aEvent);

    _keyboard.doDebounce();
  }
}
#endif