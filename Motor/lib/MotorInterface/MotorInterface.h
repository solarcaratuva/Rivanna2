#ifndef MOTOR_INTERFACE_H
#define MOTOR_INTERFACE_H

#include <mbed.h>

class MotorInterface {

    public:
        MotorInterface(I2C &throttle, I2C &regen, DigitalOut &throttleEnable, DigitalOut &regenEnable);
        int sendThrottle(char* throttle);
        uint8_t getThrottle();
        void sendRegen(uint8_t regen_value);
        uint8_t getRegen();

    private:
        I2C &throttleBus;
        I2C &regenBus;
        DigitalOut &throttleEn;
        DigitalOut &regenEn;
};

#endif