#include <unity.h>
#include <mbed.h>
#include <fakeit.hpp>
// #include "CANInterface.h"

using namespace fakeit;

Mock<CAN> mockCAN;
// Mock<CANParser> mockCANParser;
Mock<Ticker> mockTicker;
Mock<DigitalOut> mockDigitalOut;

CAN *testCAN;
// CANParser *testCANParser;
Ticker *testTicker;
DigitalOut *testDigitalOut;

CANMessage *testCANMessage;

// CANInterface *testCANInterface;

// Called before every test
void setUp()
{
    testCAN = &mockCAN.get();
    // testCANParser = &mockCANParser.get();
    testTicker = &mockTicker.get();
    testDigitalOut = &mockDigitalOut.get();
    
    testCANMessage = new CANMessage();

    Fake(OverloadedMethod(mockTicker, attach, void(Callback<void()>, std::chrono::microseconds)));
    Fake(Method(mockCAN, attach));
    Fake(Method(mockDigitalOut, write));

    // testCANInterface = new CANInterface(*testCAN, *testCANParser, *testTicker, testDigitalOut);

    // Verify(Method(mockCAN, attach)).Exactly(Once);
    // Verify(OverloadedMethod(mockTicker, attach, void(Callback<void()>, std::chrono::microseconds))).Exactly(Once);
    // Verify(Method(mockDigitalOut, write)).Exactly(Once);
}

// Called after every test
void tearDown()
{
    // final verifications
    VerifyNoOtherInvocations(mockCAN);
    // VerifyNoOtherInvocations(mockCANParser);
    VerifyNoOtherInvocations(mockTicker);
    VerifyNoOtherInvocations(mockDigitalOut);
    
    // clean up
    delete testCANMessage;
    // delete testCANInterface;
    mockCAN.Reset();
    // mockCANParser.Reset();
    mockTicker.Reset();
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

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_compiles);
    
    UNITY_END();

#ifndef NATIVE
    while(1){}
#endif
}