#ifndef MAIN_CAN_INTERFACE_H
#define MAIN_CAN_INTERFACE_H

#include "CANInterface.h"

class MainCANInterface : public CANInterface
{
public:
    MainCANInterface(PinName rd, PinName td, PinName standby_pin) : CANInterface(rd, td, standby_pin) {}

    void send(CANStruct *can_struct);

    virtual void handle(ECUMotorCommands *can_struct) {}
    virtual void handle(ECUPowerAuxCommands *can_struct) {}
    virtual void handle(PowerAuxExampleStruct *can_struct) {}
    virtual void handle(SolarCurrent *can_struct) {}
    virtual void handle(SolarVoltage *can_struct) {}
    virtual void handle(SolarTemp *can_struct) {}
    virtual void handle(SolarPhoto *can_struct) {}

private:
    void rx_handler() override;
};

#endif
