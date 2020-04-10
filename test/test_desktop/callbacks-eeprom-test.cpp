#include "fake-callback.h"
// #include <menu.h>
#include "resource-manager.h"
#include <fake-lcd.h>
#include <fake-eeprom.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "callbacks.h"
#include "callbacks-eeprom.h"
namespace test
{
namespace
{

struct LcdMock : public LiquidCrystal_I2C
{
    MOCK_METHOD0(clear, void());
    MOCK_METHOD2(setCursor, void(uint8_t, uint8_t));
    MOCK_METHOD1(print, size_t(const String &));
};

struct EEPROMock : public EEPROMClass
{
    MOCK_METHOD0(clear, void());
    MOCK_METHOD2(write, void(const int, const uint8_t));
    MOCK_METHOD2(update, void(const int, const uint8_t));
    MOCK_METHOD1(read, uint8_t(const int));
};

class CallbackEEPROMTest : public ::testing::Test
{
protected:
    mocks::FakeCallback _fakeCallback;
    LcdMock _lcdMock;
    EEPROMock _eepromMock;
};

TEST_F(CallbackEEPROMTest, should_read_temperature_and_duration_from_eeprom)
{
    EXPECT_CALL(_eepromMock, read(callbacks::eeprom::EEPROM_TEMPERATURE_ADDRESS)).Times(1).WillOnce(testing::Return(10));
    EXPECT_CALL(_eepromMock, read(callbacks::eeprom::EEPROM_DURATION_ADDRESS)).Times(1).WillOnce(testing::Return(12));
    int aTemperature = 0;
    int aDuration = 0;
    resource::Resource aResourceTemperature = {resource::TYPE::TEMPERATURE, &aTemperature};
    resource::Resource aResourceDuration = {resource::TYPE::DURATION, &aDuration};

    resource::Resource aResourceEeprom = {resource::TYPE::EEPROM, &_eepromMock};

    resource::Manager aResourceManager;
    aResourceManager.addResource(&aResourceTemperature);
    aResourceManager.addResource(&aResourceEeprom);
    aResourceManager.addResource(&aResourceDuration);

    callbacks::eeprom::readSettingsFromEEPROM(&aResourceManager);
    EXPECT_EQ(aTemperature, 10);
    EXPECT_EQ(aDuration, 12);
}

TEST_F(CallbackEEPROMTest, should_write_temperature_and_duration_to_eeprom)
{
    int aTemperature = 10;
    int aDuration = 11;

    EXPECT_CALL(_eepromMock, update(callbacks::eeprom::EEPROM_TEMPERATURE_ADDRESS, aTemperature)).Times(1);
    EXPECT_CALL(_eepromMock, update(callbacks::eeprom::EEPROM_DURATION_ADDRESS, aDuration)).Times(1);

    resource::Resource aResourceTemperature = {resource::TYPE::TEMPERATURE, &aTemperature};
    resource::Resource aResourceDuration = {resource::TYPE::DURATION, &aDuration};
    resource::Resource aResourceEeprom = {resource::TYPE::EEPROM, &_eepromMock};

    resource::Manager aResourceManager;
    aResourceManager.addResource(&aResourceTemperature);
    aResourceManager.addResource(&aResourceEeprom);
    aResourceManager.addResource(&aResourceDuration);

    callbacks::eeprom::writeSettingsToEEPROM(&aResourceManager);
}

} // namespace
} // namespace test