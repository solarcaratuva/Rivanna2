#ifndef MBED_TESTER_H
#define MBED_TESTER_H

#include <mbed.h>

class MbedTester
{
public:
    MbedTester(DigitalIn& testDigitalIn, DigitalOut& testDigitalOut, CAN& testCAN);

    /****************************** DigitalIn tests ******************************/
    int testDigitalInRead(DigitalIn& testDigitalIn);
    int testDigitalInRead();

    /****************************** DigitalOut tests ******************************/
    void testDigitalOutWrite(DigitalOut& testDigitalOut, int testValue);
    void testDigitalOutWrite(int testValue);
    
    /****************************** CAN tests ******************************/
    CANMessage testCANMessage();
    void testCANRead(CAN& testCAN, CANMessage& testCANMessage);
    void testCANWrite(CAN& testCAN, const CANMessage& testCANMessage);
    void testCANRead(CANMessage& testCANMessage);
    void testCANWrite(const CANMessage& testCANMessage);
private:
    DigitalIn& privateTestDigitalIn;
    DigitalOut& privateTestDigitalOut;
    CAN& privateTestCAN;
};

#endif