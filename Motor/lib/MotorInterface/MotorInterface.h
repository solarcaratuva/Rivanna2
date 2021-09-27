#ifndef MOTOR_INTERFACE_H
#define MOTOR_INTERFACE_H

#include <mbed.h>

class MotorInterface {

    public:
        MotorInterface(I2C &throttle, I2C &regen, DigitalOut &en);
        void startTransmission(void);
        void stopTransmission(void);
        void sendThrottle(int throttle);
        int getThrottle();
        void sendRegen(int regen_value);
        int getRegen();

    private:
        I2C &throttleBus;
        I2C &regenBus;
        DigitalOut &enable;
};

#endif