#ifndef MOTOR_CONTROLLER_CAN_INTERFACE_H
#define MOTOR_CONTROLLER_CAN_INTERFACE_H

#include "CANInterface.h"
#include "MotorControllerCANStructs.h"

class MotorControllerCANInterface : public CANInterface
{
public:
    MotorControllerCANInterface(PinName rd, PinName td, PinName standby_pin);
    void request_frames(bool frame0, bool frame1, bool frame2);
    void handle(Frame0 *can_struct);
    void handle(Frame1 *can_struct);
    void handle(Frame2 *can_struct);
private:
    void rx_handler() override;
};

#endif
