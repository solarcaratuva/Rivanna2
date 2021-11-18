#ifndef MOTOR_CAN_INTERFACE_H
#define MOTOR_CAN_INTERFACE_H

#include "MainCANInterface.h"

class MotorCANInterface : public MainCANInterface
{
public:
    MotorCANInterface(PinName rd, PinName td) : MainCANInterface(rd, td, NC) {}

    void handle(PowerAuxExampleStruct *can_struct) override;
};

#endif
