#include <unity.h>
#include <mbed.h>
#include <fakeit.hpp>
#include "MbedTester.h"

using namespace fakeit;

Mock<DigitalOut> mockDigitalOut;
Mock<CAN> mockCAN;

DigitalOut *testPin;
CAN *testCAN;
CANMessage *testCANMessage;

MbedTester *mbedTester;

// Called before every test
void setUp()
{
    testPin = &mockDigitalOut.get();
    testCAN = &mockCAN.get();
    testCANMessage = new CANMessage();
    mbedTester = new MbedTester(*testPin);
}

// Called after every test
void tearDown()
{
    // final verifications
    VerifyNoOtherInvocations(mockDigitalOut);
    VerifyNoOtherInvocations(mockCAN);
    
    // clean up
    delete testCANMessage;
    delete mbedTester;
    mockDigitalOut.Reset();
}

// Write all tests here

// Equivalence Test
void test_digital_out_read()
{
    // initialization
    Fake(Method(mockDigitalOut, read));

    // the test
    int testValue = testPin->read();
    
    // verification
    Verify(Method(mockDigitalOut, read)).Exactly(Once);
}

// Equivalence Test
void test_digital_out_write()
{
    // initialization
    Fake(Method(mockDigitalOut, write));
    int testValue = 1;

    //the test
    testPin->write(testValue);
    
    // verification
    Verify(Method(mockDigitalOut, write).Using(testValue)).Exactly(Once);
}

// Equivalence Test
void test_mbed_tester_digital_out_write()
{
    // initialization
    Fake(Method(mockDigitalOut, write));
    int testValue = 1;

    // the test
    mbedTester->testDigitalOutWrite(*testPin, testValue);
    
    // verification
    Verify(Method(mockDigitalOut, write).Using(testValue)).Exactly(Once);
}

// Equivalence Test
void test_mbed_tester_digital_out_write_private_test_pin()
{
    // initialization
    Fake(Method(mockDigitalOut, write));
    int testValue = 1;

    // the test
    mbedTester->testDigitalOutWrite(testValue);
    
    // verification
    Verify(Method(mockDigitalOut, write).Using(testValue)).Exactly(Once);
}

// Equivalence Test
void test_can_read()
{
    // initialization
    Fake(Method(mockCAN, read));
    
    // the test
    testCAN->read(*testCANMessage);
    
    // verification
    Verify(Method(mockCAN, read).Using(_, 0)).Exactly(Once);    // FakeIt has a known limitation for spying the usage of reference arguments, so we use _ to indicate any value
}

// Equivalence Test
void test_can_write()
{
    // initialization
    Fake(Method(mockCAN, write));
    
    // the test
    testCAN->write(*testCANMessage);

    // verification
    Verify(Method(mockCAN, write).Using(*testCANMessage)).Exactly(Once);
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