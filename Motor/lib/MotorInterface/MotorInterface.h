#ifndef MOTOR_INTERFACE_H
#define MOTOR_INTERFACE_H

#include <mbed.h>

class MotorInterface {

    public:
        MotorInterface(I2C &bus);
        void startTransmission(void);
        void sendThrottle(int throttle);

    private:
        I2C &messageBus;
};

#endif