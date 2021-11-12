#ifndef SOLAR_CAN_INTERFACE_H
#define SOLAR_CAN_INTERFACE_H

#include "CANInterface.h"

class SolarCANInterface : public CANInterface
{
public:
    SolarCANInterface(PinName rd, PinName td, PinName standby_pin) : CANInterface(rd, td, standby_pin) {}

    void handle(PowerAuxExampleStruct *can_struct) override;
};

#endif