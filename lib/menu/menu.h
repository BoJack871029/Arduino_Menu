
#ifndef __MENU_H
#define __MENU_H
#ifndef UNIT_TEST
#include <Arduino.h>
#else
#include "arduino-desktop.h"
#endif
class LiquidCrystal_I2C;

namespace menu
{
class MenuItem
{
public:
    String _title;
    void (*_callback)(void *);
};

class Menu
{
public:
    enum ACTIONS
    {
        UP,
        DOWN,
        ENTER,
        BACK
    };

    Menu(LiquidCrystal_I2C *iLcd, MenuItem *iItems, size_t iItemsLength);

    virtual void setDisplayRows(int iRows);

    virtual int getPageIndex();

    virtual int getRowIndex();

    virtual bool isItemSelected();

    virtual void display() const;

    virtual void moveUp();

    virtual void moveDown();

    virtual void select();

    virtual void moveBack();

    virtual void setResourceManger(void *iResourceManager);

private:
    int _displayRows = 2;
    MenuItem *_items;
    int _itemsLength;
    LiquidCrystal_I2C *_lcd;
    int _rowIndex = 0;
    int _pageIndex = 0;
    int _isItemSelected = 0;
    void *_resourceManager;
};
} // namespace menu
#endif