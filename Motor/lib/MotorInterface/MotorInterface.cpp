#include "MotorInterface.h"

MotorInterface::MotorInterface(I2C &bus) : messageBus(bus) {}

void MotorInterface::startTransmission() {
    this->messageBus.start();
}

void MotorInterface::sendThrottle(int throttle) {
    
}