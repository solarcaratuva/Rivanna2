#include "MotorInterface.h"

/**
 * Motor driver that controls the throttle and regen values
 * @param throttle Mbed I2C object for throttle communication
 * @param regen Mbed I2C object for regen communication 
 */
MotorInterface::MotorInterface(I2C &throttle, I2C& regen) : throttleBus(throttle), regenBus(regen) {}

/**
 * Sends a throttle value to motor
 * @param throttle Throttle value (between 0x0000 and 0x0100)
 */
int MotorInterface::sendThrottle(uint16_t throttle) 
{
    char cmd[2];
    cmd[0] = (throttle & 0x100) >> 8;
    cmd[1] = throttle & 0xFF; 
    int result = throttleBus.write(0x5C, cmd, 2);
    return result;
}

/**
 * Sends a regen value to motor
 * @param regen Regen value (between 0x0000 and 0x0100)
 */
int MotorInterface::sendRegen(uint16_t regen) 
{
    char cmd[2];
    cmd[0] = (regen & 0x100) >> 8;
    cmd[1] = regen & 0xFF; 
    int result = regenBus.write(0x5C, cmd, 2);
    return result;
}