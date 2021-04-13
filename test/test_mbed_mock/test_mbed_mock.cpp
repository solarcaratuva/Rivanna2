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

// Equivalence Test
void test_can_read()
{
    // initialization
    Mock<CAN> mockCAN;
    Fake(Method(mockCAN, read));
    CANMessage testCANMessage;
    CAN &testCAN = mockCAN.get();
    
    // the test
    testCAN.read(testCANMessage);
    
    // verification
    Verify(Method(mockCAN, read).Using(_, 0)).Exactly(Once);    // FakeIt has a known limitation for spying the usage of reference arguments, so we use _ to indicate any value
    VerifyNoOtherInvocations(mockCAN);
}

// Equivalence Test
void test_can_write()
{
    // initialization
    Mock<CAN> mockCAN;
    Fake(Method(mockCAN, write));
    CANMessage testCANMessage;
    CAN &testCAN = mockCAN.get();
    
    // the test
    testCAN.write(testCANMessage);

    // verification
    Verify(Method(mockCAN, write).Using(testCANMessage)).Exactly(Once);
    VerifyNoOtherInvocations(mockCAN);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_digital_out_read);
    RUN_TEST(test_digital_out_write);
    RUN_TEST(test_mbed_tester_digital_out_write);
    RUN_TEST(test_mbed_tester_digital_out_write_private_test_pin);
    RUN_TEST(test_can_read);
    RUN_TEST(test_can_write);
    UNITY_END();

#ifndef NATIVE
    while(1){}
#endif
}