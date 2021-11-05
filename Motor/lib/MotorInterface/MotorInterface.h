#ifndef MOTOR_INTERFACE_H
#define MOTOR_INTERFACE_H

#include <mbed.h>

class MotorInterface {

    public:
        MotorInterface(I2C &throttle, I2C &regen);
        int sendThrottle(uint16_t throttle);
        int sendRegen(uint16_t regen);

    private:
        I2C &throttleBus;
        I2C &regenBus;

};

#endif