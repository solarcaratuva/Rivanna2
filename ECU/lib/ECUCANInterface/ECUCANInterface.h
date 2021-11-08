#ifndef ECU_CAN_INTERFACE_H
#define ECU_CAN_INTERFACE_H

#include "CANInterface.h"

class ECUCANInterface : public CANInterface
{
public:
    ECUCANInterface(PinName rd, PinName td, PinName standby_pin) : CANInterface(rd, td, standby_pin) {}

    void handle(PowerAuxExampleStruct *can_struct) override;
};

#endif