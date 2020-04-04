#include <menu_callbacks.h>
#include <debug.h>
#include <resource-manager.h>
#include <LiquidCrystal_I2C.h>
#include <fsm.h>
namespace menu_callbacks
{
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
} // namespace menu_callbacks