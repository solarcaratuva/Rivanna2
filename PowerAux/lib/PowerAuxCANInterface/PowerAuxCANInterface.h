#ifndef POWER_AUX_CAN_INTERFACE_H
#define POWER_AUX_CAN_INTERFACE_H

#include "CANInterface.h"

class PowerAuxCANInterface : public CANInterface
{
public:
    PowerAuxCANInterface(PinName rd, PinName td, PinName standby_pin) : CANInterface(rd, td, standby_pin) {}

    void handle(PowerAuxExampleStruct *can_struct) override;
};

#endif