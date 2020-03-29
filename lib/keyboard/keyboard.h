#ifndef __KEYBOARD_H
#define __KEYBOARD_H
#include <Arduino.h>
#include <map>
#include <vector>
class Keyboard
{
public:
    Keyboard(const std::vector<int> &iRowPins, const std::vector<int> &iColPins);

    int cerca_tasto_premuto() const;

    String converti_tasto(const int &iTasto) const;

    void init();

    void debounce() const;

    void setDebounce(const int iValue);

private:
    void leggi_riga(const int &iIndex) const;

    bool leggi_colonna(const int &iIndex) const;

    int _debounce = 300;
    std::vector<int> _rowPins;
    std::vector<int> _colPins;
    const std::map<int, String> _keysMap = {{0, "Left Arrow"}, {1, "7"}, {2, "4"}, {3, "1"}, {4, "F1"}, {5, "0"}, {6, "8"}, {7, "5"}, {8, "2"}, {9, "F2"}, {10, "Right Arrow"}, {11, "9"}, {12, "6"}, {13, "3"}, {14, "#"}, {15, "Ent"}, {16, "Esc"}, {17, "Down Arrow"}, {18, "Up Arrow"}, {19, "*"}};
};

#endif