#include <fake-lcd.h>
#include "fake-callback.h"
#include <menu.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

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

class MenuTest : public ::testing::Test
{
protected:
    void createMenuItems(int iNumber, menu::MenuItem *oArray)
    {
        std::vector<menu::MenuItem> aMenuItems;
        for (int i = 0; i < iNumber; ++i)
        {
            aMenuItems.push_back({"Voce " + i, NULL});
        }

        std::copy(aMenuItems.begin(), aMenuItems.end(), oArray);
    }

    mocks::FakeCallback _fakeCallback;
    LcdMock _lcdMock;
};

TEST_F(MenuTest, shoud_be_correctly_initialized)
{
    LiquidCrystal_I2C aLcd;

    int aSize = 1;
    menu::MenuItem aMenuItems[aSize];
    createMenuItems(aSize, aMenuItems);

    menu::Menu aMenu = menu::Menu(&aLcd, aMenuItems, aSize);
    EXPECT_EQ(aMenu.getPageIndex(), 0);
    EXPECT_EQ(aMenu.getRowIndex(), 0);
}

TEST_F(MenuTest, should_not_move_up_when_on_first_element)
{
    LiquidCrystal_I2C aLcd;

    int aSize = 1;
    menu::MenuItem aMenuItems[aSize];
    createMenuItems(aSize, aMenuItems);

    menu::Menu aMenu = menu::Menu(&aLcd, aMenuItems, aSize);
    aMenu.moveUp();
    EXPECT_EQ(aMenu.getPageIndex(), 0);
    EXPECT_EQ(aMenu.getRowIndex(), 0);
}

TEST_F(MenuTest, should_move_up_by_one)
{
    LiquidCrystal_I2C aLcd;
    int aSize = 2;
    menu::MenuItem aMenuItems[aSize];
    createMenuItems(aSize, aMenuItems);
    menu::Menu aMenu = menu::Menu(&aLcd, aMenuItems, aSize);
    aMenu.moveDown();
    aMenu.moveUp();
    EXPECT_EQ(aMenu.getPageIndex(), 0);
    EXPECT_EQ(aMenu.getRowIndex(), 0);
}

TEST_F(MenuTest, should_move_up_by_two)
{
    LiquidCrystal_I2C aLcd;

    int aSize = 3;
    menu::MenuItem aMenuItems[aSize];
    createMenuItems(aSize, aMenuItems);

    menu::Menu aMenu = menu::Menu(&aLcd, aMenuItems, aSize);
    aMenu.moveDown();
    aMenu.moveDown();
    aMenu.moveUp();
    aMenu.moveUp();
    EXPECT_EQ(aMenu.getPageIndex(), 0);
    EXPECT_EQ(aMenu.getRowIndex(), 0);
}

TEST_F(MenuTest, should_not_move_down_when_one_element)
{
    LiquidCrystal_I2C aLcd;

    int aSize = 1;
    menu::MenuItem aMenuItems[aSize];
    createMenuItems(aSize, aMenuItems);

    menu::Menu aMenu = menu::Menu(&aLcd, aMenuItems, aSize);
    aMenu.moveDown();
    EXPECT_EQ(aMenu.getPageIndex(), 0);
    EXPECT_EQ(aMenu.getRowIndex(), 0);
}

TEST_F(MenuTest, should_not_move_down_when_on_last_element)
{
    LiquidCrystal_I2C aLcd;

    int aSize = 3;
    menu::MenuItem aMenuItems[aSize];
    createMenuItems(aSize, aMenuItems);

    menu::Menu aMenu = menu::Menu(&aLcd, aMenuItems, aSize);
    aMenu.moveDown();
    aMenu.moveDown();
    aMenu.moveDown();
    aMenu.moveDown();
    EXPECT_EQ(aMenu.getPageIndex(), 1);
    EXPECT_EQ(aMenu.getRowIndex(), 0);
}

TEST_F(MenuTest, should_move_down_by_one)
{
    LiquidCrystal_I2C aLcd;

    int aSize = 2;
    menu::MenuItem aMenuItems[aSize];
    createMenuItems(aSize, aMenuItems);

    menu::Menu aMenu = menu::Menu(&aLcd, aMenuItems, aSize);
    aMenu.moveDown();
    EXPECT_EQ(aMenu.getPageIndex(), 0);
    EXPECT_EQ(aMenu.getRowIndex(), 1);
}

TEST_F(MenuTest, should_move_down_by_two)
{
    LiquidCrystal_I2C aLcd;

    int aSize = 3;
    menu::MenuItem aMenuItems[aSize];
    createMenuItems(aSize, aMenuItems);

    menu::Menu aMenu = menu::Menu(&aLcd, aMenuItems, aSize);
    aMenu.moveDown();
    aMenu.moveDown();
    EXPECT_EQ(aMenu.getPageIndex(), 1);
    EXPECT_EQ(aMenu.getRowIndex(), 0);
}

TEST_F(MenuTest, should_increment_page_index)
{
    LiquidCrystal_I2C aLcd;

    int aSize = 3;
    menu::MenuItem aMenuItems[aSize];
    createMenuItems(aSize, aMenuItems);

    menu::Menu aMenu = menu::Menu(&aLcd, aMenuItems, aSize);
    aMenu.moveDown();
    ASSERT_EQ(aMenu.getPageIndex(), 0);
    ASSERT_EQ(aMenu.getRowIndex(), 1);

    aMenu.moveDown();
    EXPECT_EQ(aMenu.getPageIndex(), 1);
    ASSERT_EQ(aMenu.getRowIndex(), 0);
}

TEST_F(MenuTest, should_execute_item_callback)
{
    EXPECT_CALL(_fakeCallback, exec(testing::_)).Times(1);
    LiquidCrystal_I2C aLcd;

    int aSize = 1;
    menu::MenuItem aMenuItems[aSize] = {{"Item 1", mocks::fakeCallback}};

    menu::Menu aMenu = menu::Menu(&aLcd, aMenuItems, aSize);
    aMenu.setResourceManger(&_fakeCallback);
    aMenu.select();
}

TEST_F(MenuTest, should_deselect_item)
{
    LiquidCrystal_I2C aLcd;

    int aSize = 1;
    menu::MenuItem aMenuItems[aSize] = {{"Item 1", mocks::emptyCallback}};

    menu::Menu aMenu = menu::Menu(&aLcd, aMenuItems, aSize);
    aMenu.select();
    ASSERT_TRUE(aMenu.isItemSelected());

    aMenu.moveBack();
    EXPECT_FALSE(aMenu.isItemSelected());
}

TEST_F(MenuTest, should_not_display)
{
    EXPECT_CALL(_lcdMock, setCursor(testing::_, testing::_)).Times(0);
    EXPECT_CALL(_lcdMock, print(testing::_)).Times(0);
    EXPECT_CALL(_lcdMock, clear()).Times(0);

    int aSize = 1;
    menu::MenuItem aMenuItems[aSize] = {{"Item 1", mocks::emptyCallback}};

    menu::Menu aMenu = menu::Menu(&_lcdMock, aMenuItems, aSize);
    aMenu.select();
    ASSERT_TRUE(aMenu.isItemSelected());

    aMenu.display();
}

TEST_F(MenuTest, should_display_one_row)
{
    EXPECT_CALL(_lcdMock, setCursor(testing::_, testing::_)).Times(1);
    EXPECT_CALL(_lcdMock, print(testing::_)).Times(2);
    EXPECT_CALL(_lcdMock, clear()).Times(1);

    int aSize = 1;
    menu::MenuItem aMenuItems[aSize] = {{"Item 1", mocks::emptyCallback}};

    menu::Menu aMenu = menu::Menu(&_lcdMock, aMenuItems, aSize);

    aMenu.display();
}

TEST_F(MenuTest, should_display_correctly_when_display_has_four_rows)
{
    EXPECT_CALL(_lcdMock, setCursor(testing::_, testing::_)).Times(4);
    EXPECT_CALL(_lcdMock, print(testing::_)).Times(5);
    EXPECT_CALL(_lcdMock, clear()).Times(1);

    int aSize = 4;
    menu::MenuItem aMenuItems[aSize];
    createMenuItems(aSize, aMenuItems);

    menu::Menu aMenu = menu::Menu(&_lcdMock, aMenuItems, aSize);
    aMenu.setDisplayRows(4);

    aMenu.display();
}

TEST_F(MenuTest, should_display_increment_page_index_when_has_four_rows)
{
    int aSize = 5;
    menu::MenuItem aMenuItems[aSize];
    createMenuItems(aSize, aMenuItems);

    LiquidCrystal_I2C aLcd;
    menu::Menu aMenu = menu::Menu(&aLcd, aMenuItems, aSize);
    aMenu.setDisplayRows(4);

    aMenu.moveDown();
    aMenu.moveDown();
    aMenu.moveDown();
    aMenu.moveDown();
    EXPECT_EQ(aMenu.getPageIndex(), 1);
    EXPECT_EQ(aMenu.getRowIndex(), 0);
}
} // namespace
} // namespace test