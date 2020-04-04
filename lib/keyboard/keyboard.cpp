#include "keyboard.h"

namespace keyboard
{
Keyboard::Keyboard(int *iRowPins, int iRowsLength, int *iColPins, int iColsLength)
{
    _rowPins = iRowPins;
    _colPins = iColPins;
    _rowsLength = iRowsLength;
    _colsLength = iColsLength;
}

void Keyboard::init()
{
    for (int i = 0; i < _rowsLength; ++i)
    {
        pinMode(_rowPins[i], OUTPUT);
    }

    for (int i = 0; i < _colsLength; ++i)
    {
        pinMode(_colPins[i], INPUT_PULLUP);
    }
}

void Keyboard::setDebounce(const int iValue)
{
    _debounce = iValue;
}

void Keyboard::doDebounce() const
{
    delay(_debounce);
}

int Keyboard::getKeyPressed() const
{
    int aKey = -1;

    for (int aRowIndex = 0; aRowIndex < _rowsLength; ++aRowIndex)
    {
        readRow(_rowPins[aRowIndex]);

        for (int aColIndex = 0; aColIndex < _colsLength; ++aColIndex)
        {
            if (readColumn(_colPins[aColIndex]))
            {
                aKey = (_rowPins[aRowIndex] - _rowPins[0]) + 5 * (_colPins[aColIndex] - _colPins[0]);
            }
        }
    }
    return aKey;
}

void Keyboard::readRow(const int &iRowPin) const
{
    for (int i = 0; i < _rowsLength; ++i)
    {
        digitalWrite(_rowPins[i], HIGH);
    }

    digitalWrite(iRowPin, LOW);
}

bool Keyboard::readColumn(const int &iColPin) const
{
    return digitalRead(iColPin) == 0 ? true : false;
}

String Keyboard::converti_tasto(const int &iTastoIndex) const
{
    String aValue = "NO_TASTO";

    if (iTastoIndex >= 0 && iTastoIndex < _keysLength)
    {
        aValue = _keysMap[iTastoIndex];
    }

    return aValue;
}
} // namespace keyboard