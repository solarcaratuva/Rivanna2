#ifndef MBED_TESTER_H
#define MBED_TESTER_H

#include <mbed.h>

class MbedTester
{
public:
    MbedTester(DigitalOut& testPin, CAN& testCAN);

    void testDigitalOutWrite(DigitalOut& testPin, int testValue);
    void testDigitalOutWrite(int testValue);
    CANMessage testCANMessage();
    void testCANRead(CAN& testCAN, CANMessage& testCANMessage);
    void testCANWrite(CAN& testCAN, const CANMessage& testCANMessage);
    void testCANRead(CANMessage& testCANMessage);
    void testCANWrite(const CANMessage& testCANMessage);
private:
    DigitalOut& privateTestPin;
    CAN& privateTestCAN;
};

#endif