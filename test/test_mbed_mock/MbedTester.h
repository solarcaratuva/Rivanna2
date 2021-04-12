#ifndef MBED_TESTER_H
#define MBED_TESTER_H

#include <mbed.h>

class MbedTester
{
public:
    MbedTester(DigitalOut& testPin);

    void testDigitalOutWrite(DigitalOut& testPin, int testValue);
    void testDigitalOutWrite(int testValue);
private:
    DigitalOut& privateTestPin;
};

#endif