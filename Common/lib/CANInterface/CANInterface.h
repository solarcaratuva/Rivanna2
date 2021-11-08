#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H

#include <mbed.h>
#include "CANStructs.h"

class CANInterface
{
public:
    CANInterface(PinName rd, PinName td, PinName standby_pin = NC);
    
    void start_CAN_transmission(void);

    void send(CANStruct *can_struct);

    virtual void handle(ECUMotorCommands *can_struct) {}
    virtual void handle(ECUPowerAuxCommands *can_struct) {}
    virtual void handle(PowerAuxExampleStruct *can_struct) {}
    virtual void handle(SolarCurrent *can_struct) {}
    virtual void handle(SolarVoltage *can_struct) {}
    virtual void handle(SolarTemp *can_struct) {}
    virtual void handle(SolarPhoto *can_struct) {}

private:
    CAN can;
    DigitalOut standby;
    Thread rx_thread;
    void rx_handler();
};

#endif