#include "keyboard.h"

Keyboard::Keyboard(const std::vector<int> &iRowPins, const std::vector<int> &iColPins)
{
    _rowPins = iRowPins;
    _colPins = iColPins;
}

void Keyboard::init()
{
    for (int aPin : _rowPins)
    {
        pinMode(aPin, OUTPUT);
    }

    for (int aPin : _colPins)
    {
        pinMode(aPin, INPUT_PULLUP);
    }
}

void Keyboard::setDebounce(const int iValue)
{
    _debounce = iValue;
}

void Keyboard::debounce() const
{
    delay(_debounce);
}

int Keyboard::cerca_tasto_premuto() const
{
    int aKey = -1;

    for (int aRow : _rowPins)
    {
        leggi_riga(aRow);

        for (int aCol : _colPins)
        {
            if (leggi_colonna(aCol))
            {
                aKey = (aRow - _rowPins.at(0)) + 5 * (aCol - _colPins.at(0));
            }
        }
    }
    return aKey;
}

void Keyboard::leggi_riga(const int &iIndex) const
{
    for (int aPin : _rowPins)
    {
        digitalWrite(aPin, HIGH);
    }
    digitalWrite(iIndex, LOW);
}

bool Keyboard::leggi_colonna(const int &iIndex) const
{
    return digitalRead(iIndex) == 0 ? true : false;
}

String Keyboard::converti_tasto(const int &iTasto) const
{
    String aValue = "NO_TASTO";

    if (_keysMap.count(iTasto) == 1)
    {
        aValue = _keysMap[iTasto];
    }

    return aValue;
}
