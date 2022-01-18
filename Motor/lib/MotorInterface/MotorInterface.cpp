#include "MotorInterface.h"

/**
 * Motor driver that controls the throttle and regen values
 * @param throttle Mbed I2C object for throttle communication
 * @param regen Mbed I2C object for regen communication 
 */
MotorInterface::MotorInterface(I2C &throttle, I2C& regen) : throttleBus(throttle), regenBus(regen) {}

/**
 * Converts a throttle percentage into a throttle value for the motor and sends it
 * @param throttle Throttle value (decimal percentage between 0 and 100)
 */
int MotorInterface::sendThrottle(uint8_t throttle) 
{
    uint16_t updated_throttle = 0x0100-(0x0100*throttle/100);
    char cmd[2];
    cmd[0] = (updated_throttle & 0x100) >> 8;
    cmd[1] = updated_throttle & 0xFF; 
    int result = throttleBus.write(0x5C, cmd, 2);
    return result;
}

/**
 * Converts a regen percentage into a regen value for the motor and sends it
 * @param regen Regen value (decimal percentage between 0 and 100)
 */
int MotorInterface::sendRegen(uint8_t regen) 
{
    uint16_t updated_regen = 0x0100-(0x0100*regen/100);
    char cmd[2];
    cmd[0] = (updated_regen & 0x100) >> 8;
    cmd[1] = updated_regen & 0xFF; 
    int result = regenBus.write(0x5C, cmd, 2);
    return result;
}