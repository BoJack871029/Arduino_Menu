#include <unity.h>


void test_setup(void)
{
}

void test_loop(void)
{
}


int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_setup);
    RUN_TEST(test_loop);

    UNITY_END();

    return 0;
}