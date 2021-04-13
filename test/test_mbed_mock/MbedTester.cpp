#include "MbedTester.h"

MbedTester::MbedTester(DigitalOut& testPin, CAN& testCAN) : privateTestPin(testPin), privateTestCAN(testCAN)
{

}

void MbedTester::testDigitalOutWrite(DigitalOut& testPin, int testValue)
{
    testPin.write(testValue);
}

void MbedTester::testDigitalOutWrite(int testValue)
{
    privateTestPin.write(testValue);
}

CANMessage MbedTester::testCANMessage()
{
    CANMessage testCANMessage;
    return testCANMessage;
}

void MbedTester::testCANRead(CAN& testCAN, CANMessage& testCANMessage)
{
    testCAN.read(testCANMessage);
}

void MbedTester::testCANWrite(CAN& testCAN, const CANMessage& testCANMessage)
{
    testCAN.write(testCANMessage);
}

void MbedTester::testCANRead(CANMessage& testCANMessage)
{
    privateTestCAN.read(testCANMessage);
}

void MbedTester::testCANWrite(const CANMessage& testCANMessage)
{
    privateTestCAN.write(testCANMessage);
}
