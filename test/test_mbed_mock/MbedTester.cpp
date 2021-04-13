#include "MbedTester.h"

MbedTester::MbedTester(DigitalIn& testDigitalIn, DigitalOut& testDigitalOut, CAN& testCAN) : privateTestDigitalIn(testDigitalIn), privateTestDigitalOut(testDigitalOut), privateTestCAN(testCAN)
{

}

/****************************** DigitalIn tests ******************************/

int MbedTester::testDigitalInRead(DigitalIn& testDigitalIn)
{
    return testDigitalIn.read();
}

int MbedTester::testDigitalInRead()
{
    return privateTestDigitalIn.read();
}

/****************************** DigitalOut tests ******************************/

void MbedTester::testDigitalOutWrite(DigitalOut& testDigitalOut, int testValue)
{
    testDigitalOut.write(testValue);
}

void MbedTester::testDigitalOutWrite(int testValue)
{
    privateTestDigitalOut.write(testValue);
}

/****************************** CAN tests ******************************/

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
