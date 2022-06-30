#ifndef MOTOR_STATE_TRACKER_H
#define MOTOR_STATE_TRACKER_H

#include "MotorControllerCANStructs.h"
#include <mbed.h>

class MotorStateTracker {
  public:
    void setMotorControllerPowerStatus(MotorControllerPowerStatus new_frame);
    void setMotorControllerDriveStatus(MotorControllerDriveStatus new_frame);
    void setMotorControllerError(MotorControllerError new_frame);

    MotorControllerPowerStatus getMotorControllerPowerStatus(void);
    MotorControllerDriveStatus getMotorControllerDriveStatus(void);
    MotorControllerError getMotorControllerError(void);

  private:
    MotorControllerPowerStatus frame0;
    MotorControllerDriveStatus frame1;
    MotorControllerError frame2;
};

#endif