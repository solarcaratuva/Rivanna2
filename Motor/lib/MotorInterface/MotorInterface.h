#ifndef MOTOR_INTERFACE_H
#define MOTOR_INTERFACE_H

#include <mbed.h>

class MotorInterface {

    public:
        MotorInterface(I2C &throttle, I2C &regen);
        int sendThrottle(float throttle);
        int sendRegen(float regen);
        int sendForwardEn();
        int sendReverseEn();

    private:
        I2C &throttleBus;
        I2C &regenBus;
        uint8_t gear;  // -1: reverse, 0: neutral, 1: forward

};

#endif