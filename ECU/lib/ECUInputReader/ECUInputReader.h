#ifndef ECU_INPUT_READER_H
#define ECU_INPUT_READER_H

#include <stdio.h>

class ECUInputReader {
    public:
        ECUInputReader();
        bool readHazards();
        bool readLeftTurnSignal();
        bool readRightTurnSignal();
        bool readHorn();
        bool readCruiseSpeedDown();
        bool readCruiseSpeedUp();
        bool readCruiseThrottleEn();
        bool readRunningLights();
        bool readBrakePedal();
        bool readMotorOn();
        bool readReverseEn();
        bool readForwardEn();
        bool readBatteryContact();
        bool readIgnition();
        uint16_t readThrottle();
        uint16_t readRegen();

};

#endif