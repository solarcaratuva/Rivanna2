#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H

#include <mbed.h>
#include "CANStructs.h"

class CANInterface
{
public:
    CANInterface(PinName rd, PinName td, PinName standby_pin = NC);

protected:
    CAN can;
    DigitalOut standby;
    Thread rx_thread;
    virtual void rx_handler() = 0;
};

#endif