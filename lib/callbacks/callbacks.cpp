
#ifndef UNIT_TEST
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <debug.h>
#include <EEPROM.h>
#else
#include <iostream>
#include <fake-lcd.h>
#include <fake-eeprom.h>
#endif
#include <callbacks.h>
#include <menu.h>
#include <fsm.h>
#include <resource-manager.h>

namespace callbacks
{

void incrementDuration(void *iResourceManager)
{
    LOG_INFO("Callback: incrementDuration");
    if (iResourceManager != 0)
    {
        resource::Manager *aManager = (resource::Manager *)iResourceManager;
        LiquidCrystal_I2C *aLcd = (LiquidCrystal_I2C *)aManager->get(resource::TYPE::LCD);
        fsm::Fsm *aFsm = (fsm::Fsm *)aManager->get(resource::TYPE::FSM);

        int *aDuration = (int *)aManager->get(resource::TYPE::DURATION);
        if ((*aDuration) < 100)
        {
            (*aDuration)++;
            aLcd->setCursor(0, 1);
            aLcd->print(*aDuration);
            aLcd->print(" sec ");

            aFsm->exec(fsm::Event::WRITE_EEPROM);
        }
    }
}

void decrementDuration(void *iResourceManager)
{
    LOG_INFO("Callback: decrementDuration");
    if (iResourceManager != 0)
    {
        resource::Manager *aManager = (resource::Manager *)iResourceManager;
        LiquidCrystal_I2C *aLcd = (LiquidCrystal_I2C *)aManager->get(resource::TYPE::LCD);
        fsm::Fsm *aFsm = (fsm::Fsm *)aManager->get(resource::TYPE::FSM);

        int *aDuration = (int *)aManager->get(resource::TYPE::DURATION);
        if ((*aDuration) > 0)
        {
            (*aDuration)--;
            aLcd->setCursor(0, 1);
            aLcd->print(*aDuration);
            aLcd->print(" sec ");

            aFsm->exec(fsm::Event::WRITE_EEPROM);
        }
    }
}

void incrementTemperature(void *iResourceManager)
{
    LOG_INFO("Callback: incrementTemperature");
    if (iResourceManager != 0)
    {
        resource::Manager *aManager = (resource::Manager *)iResourceManager;
        LiquidCrystal_I2C *aLcd = (LiquidCrystal_I2C *)aManager->get(resource::TYPE::LCD);
        fsm::Fsm *aFsm = (fsm::Fsm *)aManager->get(resource::TYPE::FSM);

        int *aTemperatura = (int *)aManager->get(resource::TYPE::TEMPERATURE);

        if ((*aTemperatura) < 100)
        {
            (*aTemperatura)++;
            aLcd->setCursor(0, 1);
            aLcd->print(*aTemperatura);
            aLcd->print(" C ");
            aFsm->exec(fsm::Event::WRITE_EEPROM);
        }
    }
}
void decrementTemperature(void *iResourceManager)
{
    LOG_INFO("Callback: decrementTemperature");
    if (iResourceManager != 0)
    {
        resource::Manager *aManager = (resource::Manager *)iResourceManager;
        LiquidCrystal_I2C *aLcd = (LiquidCrystal_I2C *)aManager->get(resource::TYPE::LCD);
        fsm::Fsm *aFsm = (fsm::Fsm *)aManager->get(resource::TYPE::FSM);

        int *aTemperatura = (int *)aManager->get(resource::TYPE::TEMPERATURE);
        if ((*aTemperatura) > 0)
        {
            (*aTemperatura)--;
            aLcd->setCursor(0, 1);
            aLcd->print(*aTemperatura);
            aLcd->print(" C ");

            aFsm->exec(fsm::Event::WRITE_EEPROM);
        }
    }
}

void moveUP(void *iResourceManager)
{
    LOG_INFO("Move UP");
    if (iResourceManager != 0)
    {
        resource::Manager *aManager = (resource::Manager *)iResourceManager;
        menu::Menu *aMenu = (menu::Menu *)aManager->get(resource::TYPE::MENU);

        aMenu->moveUp();
        aMenu->display();
    }
}

void moveDOWN(void *iResourceManager)
{
    LOG_INFO("Callback: moveDOWN");
    if (iResourceManager != 0)
    {
        resource::Manager *aManager = (resource::Manager *)iResourceManager;
        menu::Menu *aMenu = (menu::Menu *)aManager->get(resource::TYPE::MENU);

        aMenu->moveDown();
        aMenu->display();
    }
}

void moveIN(void *iResourceManager)
{
    LOG_INFO("Callback: moveIN");
    if (iResourceManager != 0)
    {
        resource::Manager *aManager = (resource::Manager *)iResourceManager;
        menu::Menu *aMenu = (menu::Menu *)aManager->get(resource::TYPE::MENU);

        aMenu->select();
    }
}

void moveBACK(void *iResourceManager)
{
    LOG_INFO("Callback: moveBACK");
    if (iResourceManager != 0)
    {
        resource::Manager *aManager = (resource::Manager *)iResourceManager;
        menu::Menu *aMenu = (menu::Menu *)aManager->get(resource::TYPE::MENU);

        aMenu->moveBack();
        aMenu->display();
    }
}

void showMenu(void *iResourceManager)
{
    LOG_INFO("Callback: showMenu");
    if (iResourceManager != 0)
    {
        resource::Manager *aManager = (resource::Manager *)iResourceManager;
        menu::Menu *aMenu = (menu::Menu *)aManager->get(resource::TYPE::MENU);

        aMenu->display();
    }
}
void showReady(void *iResourceManager)
{
    LOG_INFO("Callback: showReady");
    if (iResourceManager != 0)
    {
        resource::Manager *aManager = (resource::Manager *)iResourceManager;
        LiquidCrystal_I2C *aLcd = (LiquidCrystal_I2C *)aManager->get(resource::TYPE::LCD);

        int *aTemperature = (int *)aManager->get(resource::TYPE::TEMPERATURE);
        int *aDuration = (int *)aManager->get(resource::TYPE::DURATION);

        aLcd->clear();
        aLcd->setCursor(0, 0);
        aLcd->print("Pronto");

        aLcd->setCursor(0, 1);
        aLcd->print("T:");
        aLcd->print(*aTemperature);
        aLcd->print(" D:");
        aLcd->print(*aDuration);
    }
}
} // namespace callbacks