#include "MotorInterface.h"

MotorInterface::MotorInterface(I2C &throttle, I2C& regen) : throttleBus(throttle), regenBus(regen) {}

int MotorInterface::sendThrottle(uint16_t throttle) 
{
    char cmd[2];
    cmd[0] = (throttle & 0x100) >> 8;
    cmd[1] = throttle & 0xFF; 
    int result = throttleBus.write(0x5C, cmd, 2);
    return result;
}

int MotorInterface::sendRegen(uint16_t regen) 
{
    char cmd[2];
    cmd[0] = (regen & 0x100) >> 8;
    cmd[1] = regen & 0xFF; 
    int result = regenBus.write(0x5C, cmd, 2);
    return result;
}