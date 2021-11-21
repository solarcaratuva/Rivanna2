#ifndef MOTOR_CONTROLLER_CAN_INTERFACE_H
#define MOTOR_CONTROLLER_CAN_INTERFACE_H

#include "CANInterface.h"

class MotorControllerCANInterface : public CANInterface
{
public:
    MotorControllerCANInterface(PinName rd, PinName td, PinName standby_pin) : CANInterface(rd, td, standby_pin) {}

private:
    void rx_handler() override;
};

#endif
