#include "MotorStateTracker.h"

void MotorStateTracker::setMotorControllerPowerStatus(
    MotorControllerPowerStatus new_frame) {
    frame0 = new_frame;
}

void MotorStateTracker::setMotorControllerDriveStatus(
    MotorControllerDriveStatus new_frame) {
    frame1 = new_frame;
}

void MotorStateTracker::setMotorControllerError(
    MotorControllerError new_frame) {
    frame2 = new_frame;
}

MotorControllerPowerStatus
MotorStateTracker::getMotorControllerPowerStatus(void) {
    return frame0;
}

MotorControllerDriveStatus
MotorStateTracker::getMotorControllerDriveStatus(void) {
    return frame1;
}

MotorControllerError MotorStateTracker::getMotorControllerError(void) {
    return frame2;
}