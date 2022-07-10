#ifndef MOTOR_CONTROLLER_CAN_INTERFACE_H
#define MOTOR_CONTROLLER_CAN_INTERFACE_H

#include "CANInterface.h"
#include "MotorControllerCANStructs.h"
#include <mbed.h>

class MotorControllerCANInterface : public CANInterface {
  public:
    MotorControllerCANInterface(PinName rd, PinName td, PinName standby_pin);
    int request_frames(bool power_status_frame, bool drive_status_frame,
                       bool error_frame);
    void handle(MotorControllerPowerStatus *can_struct);
    void handle(MotorControllerDriveStatus *can_struct);
    void handle(MotorControllerError *can_struct);

  private:
    void message_handler() override;
    Thread bus_status_thread;
    void check_bus_status();
};

#endif
