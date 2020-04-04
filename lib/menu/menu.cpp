#include "menu.h"
#include <LiquidCrystal_I2C.h>

namespace menu
{
Menu::Menu(LiquidCrystal_I2C *iLcd, MenuItem *iItems, size_t iItemsLength)
{
    _items = iItems;
    _lcd = iLcd;
    _itemsLength = iItemsLength;
}

void Menu::setResourceManger(void *iResourceManager)
{
    _resourceManager = iResourceManager;
}

void Menu::display() const
{
    if (_isItemSelected != 0)
    {
        return;
    }

    _lcd->clear();

    for (int i = 0; i < _displayRows; ++i)
    {
        const int aIndex = i + (_pageIndex * _displayRows);

        if (aIndex < _itemsLength)
        {
            const MenuItem aItem = _items[aIndex];

            _lcd->setCursor(0, i);
            _lcd->print(aItem._title);

            if ((_rowIndex % _displayRows) == i)
            {
                _lcd->print(" <-");
            }
        }
    }
}

void Menu::moveUp()
{
    _rowIndex--;

    if (_rowIndex < 0)
    {
        _pageIndex--;
        _rowIndex = _displayRows - 1;
    }

    if (_pageIndex < 0)
    {
        _rowIndex = 0;
        _pageIndex = 0;
    }
}

void Menu::moveDown()
{
    const int aRemainingItems = _itemsLength - (_pageIndex * _displayRows);
    if (aRemainingItems <= _displayRows)
    {
        return;
    }
    _rowIndex++;
    if (_rowIndex > (_displayRows - 1))
    {
        _rowIndex = 0;
        _pageIndex++;
    }
}

void Menu::select()
{
    const int aIndex = _rowIndex + (_pageIndex * _displayRows);

    MenuItem aItem = _items[aIndex];
    if (aItem._callback)
    {
        aItem._callback(_resourceManager);
        _isItemSelected = 1;
    }
}

void Menu::moveBack()
{
    _isItemSelected = 0;
}

}