#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#ifndef UNIT_TEST
#include <Arduino.h>
#endif

#include <map>
#include <vector>
namespace keyboard
{
enum Keys
{
    LEFT_ARROW,
    SEVEN,
    FOUR,
    ONE,
    F1,
    ZERO,
    EIGHT,
    FIVE,
    TWO,
    F2,
    RIGHT_ARROW,
    NINE,
    SIX,
    THREE,
    DASH,
    ENTER,
    ESC,
    DOWN_ARROW,
    UP_ARROW,
    STAR
};

class Keyboard
{
public:
    Keyboard(int *iRowPins, int iRowsLength, int *iColPins, int iColsLength);

    int getKeyPressed() const;

    String converti_tasto(const int &iTasto) const;

    void init();

    void doDebounce() const;

    void setDebounce(const int iValue);

private:
    void readRow(const int &iIndex) const;

    bool readColumn(const int &iIndex) const;

    int _debounce = 300;
    int *_rowPins;
    int *_colPins;

    int _rowsLength;
    int _colsLength;
    int _keysMap[20] = {Keys::LEFT_ARROW, Keys::SEVEN, Keys::FOUR, Keys::ONE, Keys::F1, Keys::ZERO, Keys::EIGHT, Keys::FIVE, Keys::TWO, Keys::F2, Keys::RIGHT_ARROW, Keys::NINE, Keys::SIX, Keys::THREE, Keys::DASH, Keys::ENTER, Keys::ESC, Keys::DOWN_ARROW, Keys::UP_ARROW, Keys::STAR};
    int _keysLength = 20;
};
} // namespace keyboard
#endif