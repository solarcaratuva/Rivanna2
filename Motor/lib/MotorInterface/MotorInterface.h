#ifndef MOTOR_INTERFACE_H
#define MOTOR_INTERFACE_H

#include <mbed.h>

class MotorInterface {

    public:
        MotorInterface(I2C &throttle, I2C &regen);
        int sendThrottle(uint8_t throttle);
        int sendRegen(uint8_t regen);
        void sendDirection(uint8_t direction);
        void sendIgnition(bool ignition);

    private:
        I2C &throttleBus;
        I2C &regenBus;
        uint8_t gear;  // 0: reverse, 1: neutral, 2: forward

};

#endif