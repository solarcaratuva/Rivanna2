#include "MotorInterface.h"

MotorInterface::MotorInterface(I2C &throttle, I2C& regen, DigitalOut &en) : throttleBus(throttle), regenBus(regen), enable(en) {}


void MotorInterface::startTransmission() {
    this->throttleBus.start();
    this->regenBus.start();
    this->enable.write(1);
}

void MotorInterface::stopTransmission() {
    this->throttleBus.stop();
    this->regenBus.stop();
    this->enable.write(0);
}

void MotorInterface::sendThrottle(int throttle) {
    throttleBus.write(throttle);
}

int MotorInterface::getThrottle() {
    return throttleBus.read(0);
}

void MotorInterface::sendRegen(int regen_val) {
    regenBus.write(regen_val);
}

int MotorInterface::getRegen() {
    return regenBus.read(0);
}