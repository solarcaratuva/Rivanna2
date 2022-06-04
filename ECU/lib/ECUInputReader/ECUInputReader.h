#ifndef ECU_INPUT_READER_H
#define ECU_INPUT_READER_H

#include <mbed.h>

class ECUInputReader {
  public:
    ECUInputReader();
    bool readHazards();
    bool readLeftTurnSignal();
    bool readRightTurnSignal();
    bool readCruiseSpeedDown();
    bool readCruiseSpeedUp();
    bool readCruiseThrottleEn();
    bool readRunningLights();
    bool readBrakePedal();
    bool readMotorOn();
    bool readForwardEn();
    bool readReverseEn();
    bool readBatteryContact();
    bool readIgnition();
    bool readRegenEn();
    uint16_t readThrottle();
};

#endif