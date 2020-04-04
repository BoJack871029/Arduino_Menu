#include <callbacks.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <resource-manager.h>
#include <LiquidCrystal_I2C.h>
#include <menu.h>
#include <debug.h>
#include <fsm.h>

namespace callbacks
{

void incrementDuration(void *iResourceManager)
{
    LOG_INFO("Callback: incrementDuration");
    if (iResourceManager != 0)
    {
        resource::Manager *aManager = (resource::Manager *)iResourceManager;
        LiquidCrystal_I2C *aLcd = (LiquidCrystal_I2C *)aManager->get(resource::TYPE::LCD);

        int *aDuration = (int *)aManager->get(resource::TYPE::DURATION);

        if ((*aDuration) < 100)
        {
            (*aDuration)++;
            aLcd->setCursor(0, 1);
            aLcd->print(String(*aDuration) + String(" sec  "));
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

        int *aDuration = (int *)aManager->get(resource::TYPE::DURATION);
        if ((*aDuration) > 0)
        {
            (*aDuration)--;
            aLcd->setCursor(0, 1);
            aLcd->print(String(*aDuration) + String(" sec  "));
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

        int *aTemperatura = (int *)aManager->get(resource::TYPE::TEMPERATURE);

        if ((*aTemperatura) < 100)
        {
            (*aTemperatura)++;
            aLcd->setCursor(0, 1);
            aLcd->print(String(*aTemperatura) + String(" C  "));
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

        int *aTemperatura = (int *)aManager->get(resource::TYPE::TEMPERATURE);
        if ((*aTemperatura) > 0)
        {
            (*aTemperatura)--;
            aLcd->setCursor(0, 1);
            aLcd->print(String(*aTemperatura) + String(" C  "));
        }
    }
}

void showTemperatureSetup(void *iResourceManager)
{
    LOG_INFO("Callback: temperatura");

    if (iResourceManager != 0)
    {
        resource::Manager *aManager = (resource::Manager *)iResourceManager;
        LiquidCrystal_I2C *aLcd = (LiquidCrystal_I2C *)aManager->get(resource::TYPE::LCD);

        fsm::Fsm *aFsm = (fsm::Fsm *)aManager->get(resource::TYPE::FSM);
        int *aTemperatura = (int *)aManager->get(resource::TYPE::TEMPERATURE);

        aFsm->setCurrentState(fsm::State::TEMPERATURE);
        aLcd->clear();
        aLcd->setCursor(0, 0);
        aLcd->print("Temperatura:");
        aLcd->setCursor(0, 1);
        aLcd->print(String(*aTemperatura) + String(" C  "));
    }
}

void showDurationSetup(void *iResourceManager)
{
    LOG_INFO("Callback: durata");
    if (iResourceManager != 0)
    {
        resource::Manager *aManager = (resource::Manager *)iResourceManager;
        LiquidCrystal_I2C *aLcd = (LiquidCrystal_I2C *)aManager->get(resource::TYPE::LCD);

        fsm::Fsm *aFsm = (fsm::Fsm *)aManager->get(resource::TYPE::FSM);
        aFsm->setCurrentState(fsm::State::DURATA);

        int *aDuration = (int *)aManager->get(resource::TYPE::DURATION);

        aLcd->clear();
        aLcd->setCursor(0, 0);
        aLcd->print("Durata:");

        aLcd->setCursor(0, 1);
        aLcd->print(String(*aDuration) + String(" sec  "));
    }
}

void doSetup(void *iResourceManager)
{
    LOG_INFO("Callback: doSetup");
    if (iResourceManager != 0)
    {
        resource::Manager *aManager = (resource::Manager *)iResourceManager;
        LiquidCrystal_I2C *aLcd = (LiquidCrystal_I2C *)aManager->get(resource::TYPE::LCD);

        fsm::Fsm *aFsm = (fsm::Fsm *)aManager->get(resource::TYPE::FSM);
        aFsm->setCurrentState(fsm::State::SETUP);

        aLcd->clear();
        aLcd->setCursor(0, 0);
        aLcd->print("Setup:");
        aLcd->setCursor(0, 1);
        aLcd->print("...");
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

} // namespace callbacks