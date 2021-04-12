#include "MbedTester.h"

MbedTester::MbedTester(DigitalOut& testPin) : privateTestPin(testPin)
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
