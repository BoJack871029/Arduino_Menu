#ifndef UNIT_TEST
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoSTL.h>
#include <map>
#include <keyboard.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,16,2) for 16x2 LCD.

const std::vector<int> _rowsPin = {2, 3, 4, 5, 6};
const std::vector<int> _colPin = {8, 9, 10, 11};

Keyboard _keyboard = Keyboard(_rowsPin, _colPin);

void setup()
{
  _keyboard.init();

  lcd.begin();

  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
  Serial.begin(9600);
  Serial.println("CIAO 1");
}

void loop()
{
  int aTastoPremuto = _keyboard.cerca_tasto_premuto();

  if (aTastoPremuto != -1)
  {
    String aTasto = _keyboard.converti_tasto(aTastoPremuto);

    Serial.print(aTastoPremuto);
    Serial.print("  -  ");
    Serial.println(aTasto);
    _keyboard.debounce();
  }
}
#endif