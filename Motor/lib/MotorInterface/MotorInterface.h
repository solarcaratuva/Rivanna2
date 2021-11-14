#ifndef MOTOR_INTERFACE_H
#define MOTOR_INTERFACE_H

#include <mbed.h>

class MotorInterface {

    public:
        MotorInterface(I2C &throttle, I2C &regen);
        int sendThrottle(float throttle);
        int sendRegen(float regen);

    private:
        I2C &throttleBus;
        I2C &regenBus;

};

#endif