#include <unity.h>
#include <mbed.h>
#include <fakeit.hpp>
#include "MbedTester.h"

using namespace fakeit;

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
void test_digital_out_read()
{
    // initialization
    Mock<DigitalOut> mock;
    Fake(Method(mock, read));
    DigitalOut &testPin = mock.get();

    // the test
    int testValue = testPin.read();
    
    // verification
    Verify(Method(mock, read)).Exactly(Once);
    VerifyNoOtherInvocations(mock);
}

// Equivalence Test
void test_digital_out_write()
{
    // initialization
    Mock<DigitalOut> mock;
    Fake(Method(mock, write));
    DigitalOut &testPin = mock.get();
    int testValue = 1;

    //the test
    testPin.write(testValue);
    
    // verification
    Verify(Method(mock, write).Using(testValue)).Exactly(Once);
    VerifyNoOtherInvocations(mock);
}

// Equivalence Test
void test_mbed_tester_digital_out_write()
{
    // initialization
    Mock<DigitalOut> mock;
    Fake(Method(mock, write));
    DigitalOut &testPin = mock.get();
    MbedTester mbedTester(testPin);
    int testValue = 1;

    // the test
    mbedTester.testDigitalOutWrite(testPin, testValue);
    
    // verification
    Verify(Method(mock, write).Using(testValue)).Exactly(Once);
    VerifyNoOtherInvocations(mock);
}

// Equivalence Test
void test_mbed_tester_digital_out_write_private_test_pin()
{
    // initialization
    Mock<DigitalOut> mock;
    Fake(Method(mock, write));
    DigitalOut &testPin = mock.get();
    MbedTester mbedTester(testPin);
    int testValue = 1;

    // the test
    mbedTester.testDigitalOutWrite(testValue);
    
    // verification
    Verify(Method(mock, write).Using(testValue)).Exactly(Once);
    VerifyNoOtherInvocations(mock);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_digital_out_read);
    RUN_TEST(test_digital_out_write);
    RUN_TEST(test_mbed_tester_digital_out_write);
    RUN_TEST(test_mbed_tester_digital_out_write_private_test_pin);
    UNITY_END();

#ifndef NATIVE
    while(1){}
#endif
}