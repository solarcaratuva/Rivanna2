#include <unity.h>
#include <mbed.h>
#include <fakeit.hpp>
#include "CANInterface.h"

using namespace fakeit;

Mock<CAN> mockCAN;
Mock<CANParser> mockCANParser;
Mock<Thread> mockThread;
Mock<DigitalOut> mockDigitalOut;

CAN *testCAN;
CANParser *testCANParser;
Thread *testTxThread;
Thread *testRxThread;
DigitalOut *testDigitalOut;

CANMessage *testCANMessage;

CANInterface *testCANInterface;

// Called before every test
void setUp()
{
    testCAN = &mockCAN.get();
    testCANParser = &mockCANParser.get();
    testTxThread = &mockThread.get();
    testRxThread = &mockThread.get();
    testDigitalOut = &mockDigitalOut.get();
    
    testCANMessage = new CANMessage();

    Fake(Method(mockDigitalOut, write));

    testCANInterface = new CANInterface(*testCAN, *testCANParser, *testTxThread, *testRxThread, testDigitalOut);

    Verify(Method(mockDigitalOut, write)).Exactly(Once);
}

// Called after every test
void tearDown()
{
    // final verifications
    VerifyNoOtherInvocations(mockCAN);
    VerifyNoOtherInvocations(mockCANParser);
    VerifyNoOtherInvocations(mockThread);
    VerifyNoOtherInvocations(mockDigitalOut);
    
    // clean up
    delete testCANMessage;
    delete testCANInterface;
    mockCAN.Reset();
    mockCANParser.Reset();
    mockThread.Reset();
    mockDigitalOut.Reset();
}

// Write all tests here

// Equivalence Test
void test_compiles()
{
    // initialization
    // Fake(Method(mockDigitalOut, read));

    // the test
    // int result = testDigitalOut->read();
    
    // verification
    // Verify(Method(mockDigitalOut, read)).Exactly(Once);
}

// Equivalence Test
void test_start_transmission()
{
    // initialization
    Fake(OverloadedMethod(mockThread, start, osStatus(Callback<void()>)));

    // the test
    testCANInterface->startCANTransmission();
    
    // verification
    Verify(OverloadedMethod(mockThread, start, osStatus(Callback<void()>))).Exactly(2_Times);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_compiles);
    RUN_TEST(test_start_transmission);
    
    UNITY_END();

#ifndef NATIVE
    while(1){}
#endif
}