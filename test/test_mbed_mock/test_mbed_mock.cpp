#include <unity.h>
#include <mbed.h>

// Called before every test
void setUp()
{
    
}

// Called after every test
void tearDown()
{
    
}

// Write all tests here

// Equivalence Test
void test_digital_out_read_0()
{
    DigitalOut testPin(PA_0);
    int expectedValue = 0;
    int testValue = testPin.read();
    TEST_ASSERT_EQUAL(expectedValue, testValue);
}

// Equivalence Test
void test_digital_out_write_1()
{
    DigitalOut testPin(PA_0);
    testPin.write(1);
    int expectedValue = 1;
    int testValue = testPin.read();
    TEST_ASSERT_EQUAL(expectedValue, testValue);
}

// Equivalence Test
void test_digital_out_equals_1()
{
    DigitalOut testPin(PA_0);
    testPin = 1;
    int expectedValue = 1;
    int testValue = testPin.read();
    TEST_ASSERT_EQUAL(expectedValue, testValue);
}

// Equivalence Test
void test_digital_out_int_0()
{
    DigitalOut testPin(PA_0);
    int expectedValue = 0;
    int testValue = testPin;
    TEST_ASSERT_EQUAL(expectedValue, testValue);
}

// // Boundary Test
// void test_digital_out_same_pin()
// {
//     DigitalOut testPin1(PA_0);
//     DigitalOut testPin2(PA_0);
//     testPin1 = 1;
//     int expectedValue = 1;
//     int testValue = testPin2;
//     TEST_ASSERT_EQUAL(expectedValue, testValue);
// }

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_digital_out_read_0);
    RUN_TEST(test_digital_out_write_1);
    RUN_TEST(test_digital_out_equals_1);
    RUN_TEST(test_digital_out_int_0);
    // RUN_TEST(test_digital_out_same_pin);
    UNITY_END();

#ifndef NATIVE
    while(1){}
#endif
}