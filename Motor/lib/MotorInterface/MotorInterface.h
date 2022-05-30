#ifndef MOTOR_INTERFACE_H
#define MOTOR_INTERFACE_H

#include <mbed.h>

class MotorInterface {

  public:
    MotorInterface(I2C &throttle, I2C &regen, DigitalOut &gear,
                   DigitalOut &ignition);
    int sendThrottle(uint16_t throttle);
    int sendRegen(uint16_t regen);
    void sendDirection(bool direction);
    void sendIgnition(bool ignition);

  private:
    I2C &throttleBus;
    I2C &regenBus;
    DigitalOut &gearBus; // false: reverse, true: forward
    DigitalOut &mainSwitch;
};

#endif