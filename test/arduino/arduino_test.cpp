#ifdef UNIT_TEST

#include <unity.h>
#include <keyboard.h>
#include <ArduinoSTL.h>

void test1()
{
    std::vector<int> aRowPins = {2, 3, 4, 5};
    std::vector<int> aColPins = {7, 8, 9, 10, 11};
    Keyboard aKeyboard = Keyboard(aRowPins, aColPins);
    aKeyboard.init();

    int aKey = aKeyboard.cerca_tasto_premuto();
    TEST_ASSERT_EQUAL(-1, aKey);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);

    digitalWrite(8, LOW);
    aKey = aKeyboard.cerca_tasto_premuto();
    TEST_ASSERT_EQUAL(0, aKey);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test1);

    UNITY_END();
}

#endif