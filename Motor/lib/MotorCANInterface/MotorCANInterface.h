#ifndef MOTOR_CAN_INTERFACE_H
#define MOTOR_CAN_INTERFACE_H

#include "CANInterface.h"

class MotorCANInterface : public CANInterface
{
public:
    MotorCANInterface(PinName rd, PinName td) : CANInterface(rd, td, NC) {}

    void handle(PowerAuxExampleStruct *can_struct) override;
};

#endif