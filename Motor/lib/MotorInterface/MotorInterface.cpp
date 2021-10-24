#include "MotorInterface.h"

MotorInterface::MotorInterface(I2C &throttle, I2C& regen, DigitalOut &throttleEnable, DigitalOut &regenEnable) : throttleBus(throttle), regenBus(regen), throttleEn(throttleEnable), regenEn(regenEnable) {
    this->throttleEn.write(1);
    this->regenEn.write(1);
}

int MotorInterface::sendThrottle(char* throttle) {
    // this->throttleBus.start();
    int result = throttleBus.write(0x2E, throttle, 1);
    // this->throttleBus.stop();
    return result;
}

uint8_t MotorInterface::getThrottle() {
    return throttleBus.read(0);
}

void MotorInterface::sendRegen(uint8_t regen_val) {
    regenBus.start();
    regenBus.write(regen_val);
    regenBus.stop();
}

uint8_t MotorInterface::getRegen() {
    return regenBus.read(0);
}