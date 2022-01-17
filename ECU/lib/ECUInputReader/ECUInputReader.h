#ifndef ECU_INPUT_READER_H
#define ECU_INPUT_READER_H

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
        bool readForwardEn();
        bool readReverseEn();
        bool readBatteryContact();
        bool readIgnition();
        float readThrottle();
        float readRegen();

};

#endif