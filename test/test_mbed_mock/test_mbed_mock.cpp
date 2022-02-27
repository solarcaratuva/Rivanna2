#include "MbedTester.h"
#include <fakeit.hpp>
#include <mbed.h>
#include <unity.h>

using namespace fakeit;

Mock<DigitalIn> mockDigitalIn;
Mock<DigitalOut> mockDigitalOut;
Mock<CAN> mockCAN;

DigitalIn *testDigitalIn;
DigitalOut *testDigitalOut;
CAN *testCAN;
CANMessage *testCANMessage;

MbedTester *mbedTester;

// Called before every test
void setUp() {
    testDigitalIn = &mockDigitalIn.get();
    testDigitalOut = &mockDigitalOut.get();
    testCAN = &mockCAN.get();
    testCANMessage = new CANMessage();
    mbedTester = new MbedTester(*testDigitalIn, *testDigitalOut, *testCAN);
}

// Called after every test
void tearDown() {
    // final verifications
    VerifyNoOtherInvocations(mockDigitalIn);
    VerifyNoOtherInvocations(mockDigitalOut);
    VerifyNoOtherInvocations(mockCAN);

    // clean up
    delete testCANMessage;
    delete mbedTester;
    mockDigitalIn.Reset();
    mockDigitalOut.Reset();
    mockCAN.Reset();
}

// Write all tests here

/****************************** DigitalIn tests ******************************/

// Equivalence Test
void test_digital_in_read() {
    // initialization
    Fake(Method(mockDigitalIn, read));

    // the test
    int result = testDigitalIn->read();

    // verification
    Verify(Method(mockDigitalIn, read)).Exactly(Once);
}

// Equivalence Test
void test_mbed_tester_digital_in_read() {
    // initialization
    Fake(Method(mockDigitalIn, read));

    // the test
    int result = mbedTester->testDigitalInRead(*testDigitalIn);

    // verification
    Verify(Method(mockDigitalIn, read)).Exactly(Once);
}

// Equivalence Test
void test_mbed_tester_digital_in_read_private() {
    // initialization
    Fake(Method(mockDigitalIn, read));

    // the test
    int result = mbedTester->testDigitalInRead();

    // verification
    Verify(Method(mockDigitalIn, read)).Exactly(Once);
}

/****************************** DigitalOut tests ******************************/

// Equivalence Test
void test_digital_out_read() {
    // initialization
    Fake(Method(mockDigitalOut, read));

    // the test
    int result = testDigitalOut->read();

    // verification
    Verify(Method(mockDigitalOut, read)).Exactly(Once);
}

// Equivalence Test
void test_digital_out_write() {
    // initialization
    Fake(Method(mockDigitalOut, write));
    int testValue = 1;

    // the test
    testDigitalOut->write(testValue);

    // verification
    Verify(Method(mockDigitalOut, write).Using(testValue)).Exactly(Once);
}

// Equivalence Test
void test_mbed_tester_digital_out_write() {
    // initialization
    Fake(Method(mockDigitalOut, write));
    int testValue = 1;

    // the test
    mbedTester->testDigitalOutWrite(*testDigitalOut, testValue);

    // verification
    Verify(Method(mockDigitalOut, write).Using(testValue)).Exactly(Once);
}

// Equivalence Test
void test_mbed_tester_digital_out_write_private() {
    // initialization
    Fake(Method(mockDigitalOut, write));
    int testValue = 1;

    // the test
    mbedTester->testDigitalOutWrite(testValue);

    // verification
    Verify(Method(mockDigitalOut, write).Using(testValue)).Exactly(Once);
}

/****************************** CAN tests ******************************/

// Equivalence Test
void test_can_read() {
    // initialization
    Fake(Method(mockCAN, read));

    // the test
    testCAN->read(*testCANMessage);

    // verification
    Verify(Method(mockCAN, read).Using(_, 0))
        .Exactly(
            Once); // FakeIt has a known limitation for spying the usage of
                   // reference arguments, so we use _ to indicate any value
}

// Equivalence Test
void test_can_write() {
    // initialization
    Fake(Method(mockCAN, write));

    // the test
    testCAN->write(*testCANMessage);

    // verification
    Verify(Method(mockCAN, write).Using(*testCANMessage)).Exactly(Once);
}

// Equivalence Test
void test_mbed_tester_can_message() {
    // initialization

    // the test
    CANMessage result = mbedTester->testCANMessage();

    // verification
    TEST_ASSERT_EQUAL_MEMORY(testCANMessage, &result, sizeof(CANMessage));
}

// Equivalence Test
void test_mbed_tester_can_read() {
    // initialization
    Fake(Method(mockCAN, read));

    // the test
    mbedTester->testCANRead(*testCAN, *testCANMessage);

    // verification
    Verify(Method(mockCAN, read).Using(_, 0))
        .Exactly(
            Once); // FakeIt has a known limitation for spying the usage of
                   // reference arguments, so we use _ to indicate any value
}

// Equivalence Test
void test_mbed_tester_can_write() {
    // initialization
    Fake(Method(mockCAN, write));

    // the test
    mbedTester->testCANWrite(*testCAN, *testCANMessage);

    // verification
    Verify(Method(mockCAN, write).Using(*testCANMessage)).Exactly(Once);
}

// Equivalence Test
void test_mbed_tester_can_read_private() {
    // initialization
    Fake(Method(mockCAN, read));

    // the test
    mbedTester->testCANRead(*testCANMessage);

    // verification
    Verify(Method(mockCAN, read).Using(_, 0))
        .Exactly(
            Once); // FakeIt has a known limitation for spying the usage of
                   // reference arguments, so we use _ to indicate any value
}

// Equivalence Test
void test_mbed_tester_can_write_private() {
    // initialization
    Fake(Method(mockCAN, write));

    // the test
    mbedTester->testCANWrite(*testCANMessage);

    // verification
    Verify(Method(mockCAN, write).Using(*testCANMessage)).Exactly(Once);
}

int main() {
    UNITY_BEGIN();

    /****************************** DigitalIn tests
     * ******************************/
    RUN_TEST(test_digital_in_read);
    RUN_TEST(test_mbed_tester_digital_in_read);
    RUN_TEST(test_mbed_tester_digital_in_read_private);

    /****************************** DigitalOut tests
     * ******************************/
    RUN_TEST(test_digital_out_read);
    RUN_TEST(test_digital_out_write);
    RUN_TEST(test_mbed_tester_digital_out_write);
    RUN_TEST(test_mbed_tester_digital_out_write_private);

    /****************************** CAN tests ******************************/
    RUN_TEST(test_can_read);
    RUN_TEST(test_can_write);
    RUN_TEST(test_mbed_tester_can_message);
    RUN_TEST(test_mbed_tester_can_read);
    RUN_TEST(test_mbed_tester_can_write);
    RUN_TEST(test_mbed_tester_can_read_private);
    RUN_TEST(test_mbed_tester_can_write_private);

    UNITY_END();

#ifndef NATIVE
    while (1) {
    }
#endif
}