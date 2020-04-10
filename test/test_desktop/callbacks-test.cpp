#include "fake-callback.h"
#include "resource-manager.h"
#include <fake-lcd.h>
#include <fake-eeprom.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "callbacks.h"
#include "callbacks-eeprom.h"
#include <fsm.h>
#include <menu.h>
namespace test
{
namespace
{
struct LcdMock : public LiquidCrystal_I2C
{
    MOCK_METHOD0(clear, void());
    MOCK_METHOD2(setCursor, void(uint8_t, uint8_t));
    MOCK_METHOD1(print, size_t(const String &));
    MOCK_METHOD1(print, size_t(const int &));
};

struct FsmMock : public fsm::Fsm
{
    MOCK_METHOD1(exec, int(const fsm::Event iEvent));
};

struct MenuMock : public menu::Menu
{
    MenuMock() : menu::Menu{NULL, NULL, 0} {}
    MOCK_METHOD0(moveUp, void());
    MOCK_METHOD0(moveDown, void());
    MOCK_METHOD0(moveBack, void());
    MOCK_METHOD0(select, void());
    MOCK_METHOD0(display, void());
};

class CallbackTest : public ::testing::Test
{
protected:
    mocks::FakeCallback _fakeCallback;
    LcdMock _lcdMock;
};

TEST_F(CallbackTest, should_increment_duration)
{
    LiquidCrystal_I2C aLcd;
    fsm::Fsm aFsm;
    FsmMock aFsmMock;

    EXPECT_CALL(aFsmMock, exec(fsm::Event::WRITE_EEPROM)).Times(1);

    int aDuration = 0;
    resource::Resource aResourceDuration = {resource::TYPE::DURATION, &aDuration};
    resource::Resource aResourceLcd = {resource::TYPE::LCD, &aLcd};
    resource::Resource aResourceFsm = {resource::TYPE::FSM, &aFsmMock};

    resource::Manager aResourceManager;
    aResourceManager.addResource(&aResourceDuration);
    aResourceManager.addResource(&aResourceLcd);
    aResourceManager.addResource(&aResourceFsm);

    callbacks::incrementDuration(&aResourceManager);
    EXPECT_EQ(aDuration, 1);
}

TEST_F(CallbackTest, should_not_increment_duration_when_greater_then_100)
{
    LiquidCrystal_I2C aLcd;
    fsm::Fsm aFsm;
    FsmMock aFsmMock;

    EXPECT_CALL(aFsmMock, exec(fsm::Event::WRITE_EEPROM)).Times(0);

    int aDuration = 100;
    resource::Resource aResourceDuration = {resource::TYPE::DURATION, &aDuration};
    resource::Resource aResourceLcd = {resource::TYPE::LCD, &aLcd};
    resource::Resource aResourceFsm = {resource::TYPE::FSM, &aFsmMock};

    resource::Manager aResourceManager;
    aResourceManager.addResource(&aResourceDuration);
    aResourceManager.addResource(&aResourceLcd);
    aResourceManager.addResource(&aResourceFsm);

    callbacks::incrementDuration(&aResourceManager);
    EXPECT_EQ(aDuration, 100);
}

TEST_F(CallbackTest, should_decrement_duration)
{
    LiquidCrystal_I2C aLcd;
    fsm::Fsm aFsm;
    FsmMock aFsmMock;

    EXPECT_CALL(aFsmMock, exec(fsm::Event::WRITE_EEPROM)).Times(1);

    int aDuration = 5;
    resource::Resource aResourceDuration = {resource::TYPE::DURATION, &aDuration};
    resource::Resource aResourceLcd = {resource::TYPE::LCD, &aLcd};
    resource::Resource aResourceFsm = {resource::TYPE::FSM, &aFsmMock};

    resource::Manager aResourceManager;
    aResourceManager.addResource(&aResourceDuration);
    aResourceManager.addResource(&aResourceLcd);
    aResourceManager.addResource(&aResourceFsm);

    callbacks::decrementDuration(&aResourceManager);
    EXPECT_EQ(aDuration, 4);
}

TEST_F(CallbackTest, should_not_decrement_duration_when_zero)
{
    LiquidCrystal_I2C aLcd;
    fsm::Fsm aFsm;
    FsmMock aFsmMock;

    EXPECT_CALL(aFsmMock, exec(fsm::Event::WRITE_EEPROM)).Times(0);

    int aDuration = 0;
    resource::Resource aResourceDuration = {resource::TYPE::DURATION, &aDuration};
    resource::Resource aResourceLcd = {resource::TYPE::LCD, &aLcd};
    resource::Resource aResourceFsm = {resource::TYPE::FSM, &aFsmMock};

    resource::Manager aResourceManager;
    aResourceManager.addResource(&aResourceDuration);
    aResourceManager.addResource(&aResourceLcd);
    aResourceManager.addResource(&aResourceFsm);

    callbacks::decrementDuration(&aResourceManager);
    EXPECT_EQ(aDuration, 0);
}

TEST_F(CallbackTest, should_increment_temperature)
{
    LiquidCrystal_I2C aLcd;
    fsm::Fsm aFsm;
    FsmMock aFsmMock;

    EXPECT_CALL(aFsmMock, exec(fsm::Event::WRITE_EEPROM)).Times(1);

    int aTemperature = 0;
    resource::Resource aResourceTemperature = {resource::TYPE::TEMPERATURE, &aTemperature};
    resource::Resource aResourceLcd = {resource::TYPE::LCD, &aLcd};
    resource::Resource aResourceFsm = {resource::TYPE::FSM, &aFsmMock};

    resource::Manager aResourceManager;
    aResourceManager.addResource(&aResourceTemperature);
    aResourceManager.addResource(&aResourceLcd);
    aResourceManager.addResource(&aResourceFsm);

    callbacks::incrementTemperature(&aResourceManager);
    EXPECT_EQ(aTemperature, 1);
}

TEST_F(CallbackTest, should_not_increment_temperature_when_greater_then_100)
{
    LiquidCrystal_I2C aLcd;
    fsm::Fsm aFsm;
    FsmMock aFsmMock;

    EXPECT_CALL(aFsmMock, exec(fsm::Event::WRITE_EEPROM)).Times(0);

    int aTemperature = 100;
    resource::Resource aResourceTemperature = {resource::TYPE::TEMPERATURE, &aTemperature};
    resource::Resource aResourceLcd = {resource::TYPE::LCD, &aLcd};
    resource::Resource aResourceFsm = {resource::TYPE::FSM, &aFsmMock};

    resource::Manager aResourceManager;
    aResourceManager.addResource(&aResourceTemperature);
    aResourceManager.addResource(&aResourceLcd);
    aResourceManager.addResource(&aResourceFsm);

    callbacks::incrementTemperature(&aResourceManager);
    EXPECT_EQ(aTemperature, 100);
}

TEST_F(CallbackTest, should_decrement_temperature)
{
    LiquidCrystal_I2C aLcd;
    fsm::Fsm aFsm;
    FsmMock aFsmMock;

    EXPECT_CALL(aFsmMock, exec(fsm::Event::WRITE_EEPROM)).Times(1);

    int aTemperature = 5;
    resource::Resource aResourceTemperature = {resource::TYPE::TEMPERATURE, &aTemperature};
    resource::Resource aResourceLcd = {resource::TYPE::LCD, &aLcd};
    resource::Resource aResourceFsm = {resource::TYPE::FSM, &aFsmMock};

    resource::Manager aResourceManager;
    aResourceManager.addResource(&aResourceTemperature);
    aResourceManager.addResource(&aResourceLcd);
    aResourceManager.addResource(&aResourceFsm);

    callbacks::decrementTemperature(&aResourceManager);
    EXPECT_EQ(aTemperature, 4);
}

TEST_F(CallbackTest, should_call_menu_moveup_and_display)
{
    MenuMock aMenuMock;

    EXPECT_CALL(aMenuMock, moveUp()).Times(1);
    EXPECT_CALL(aMenuMock, display()).Times(1);

    int aTemperature = 0;
    resource::Resource aResourceMenu = {resource::TYPE::MENU, &aMenuMock};

    resource::Manager aResourceManager;
    aResourceManager.addResource(&aResourceMenu);

    callbacks::moveUP(&aResourceManager);
}

TEST_F(CallbackTest, should_call_menu_movedown_and_display)
{
    MenuMock aMenuMock;

    EXPECT_CALL(aMenuMock, moveDown()).Times(1);
    EXPECT_CALL(aMenuMock, display()).Times(1);

    int aTemperature = 0;
    resource::Resource aResourceMenu = {resource::TYPE::MENU, &aMenuMock};

    resource::Manager aResourceManager;
    aResourceManager.addResource(&aResourceMenu);

    callbacks::moveDOWN(&aResourceManager);
}

TEST_F(CallbackTest, should_call_menu_movein)
{
    MenuMock aMenuMock;

    EXPECT_CALL(aMenuMock, select()).Times(1);

    int aTemperature = 0;
    resource::Resource aResourceMenu = {resource::TYPE::MENU, &aMenuMock};

    resource::Manager aResourceManager;
    aResourceManager.addResource(&aResourceMenu);

    callbacks::moveIN(&aResourceManager);
}

TEST_F(CallbackTest, should_call_menu_move_back_and_display)
{
    MenuMock aMenuMock;

    EXPECT_CALL(aMenuMock, moveBack()).Times(1);
    EXPECT_CALL(aMenuMock, display()).Times(1);

    int aTemperature = 0;
    resource::Resource aResourceMenu = {resource::TYPE::MENU, &aMenuMock};

    resource::Manager aResourceManager;
    aResourceManager.addResource(&aResourceMenu);

    callbacks::moveBACK(&aResourceManager);
}

TEST_F(CallbackTest, should_call_menu_displayy)
{
    MenuMock aMenuMock;

    EXPECT_CALL(aMenuMock, display()).Times(1);

    int aTemperature = 0;
    resource::Resource aResourceMenu = {resource::TYPE::MENU, &aMenuMock};

    resource::Manager aResourceManager;
    aResourceManager.addResource(&aResourceMenu);

    callbacks::showMenu(&aResourceManager);
}

TEST_F(CallbackTest, should_diplay_main_page)
{
    LcdMock aLcdMock;
    int aTemperature = 12;
    int aDuration = 11;

    EXPECT_CALL(aLcdMock, clear()).Times(1);
    EXPECT_CALL(aLcdMock, setCursor(0, 0)).Times(1);
    EXPECT_CALL(aLcdMock, print("Pronto")).Times(1);
    EXPECT_CALL(aLcdMock, setCursor(0, 1)).Times(1);
    EXPECT_CALL(aLcdMock, print("T:")).Times(1);
    EXPECT_CALL(aLcdMock, print(aTemperature)).Times(1);
    EXPECT_CALL(aLcdMock, print(" D:")).Times(1);
    EXPECT_CALL(aLcdMock, print(aDuration)).Times(1);

    resource::Resource aResourceLcd = {resource::TYPE::LCD, &aLcdMock};
    resource::Resource aResourceTemperature = {resource::TYPE::TEMPERATURE, &aTemperature};
    resource::Resource aResourceDuration = {resource::TYPE::DURATION, &aDuration};

    resource::Manager aResourceManager;
    aResourceManager.addResource(&aResourceLcd);
    aResourceManager.addResource(&aResourceTemperature);
    aResourceManager.addResource(&aResourceDuration);

    callbacks::showReady(&aResourceManager);
}
} // namespace
} // namespace test