#include "CANInterface.h"

CANInterface::CANInterface(PinName rd, PinName td, PinName standby_pin) : can(rd, td), standby(standby_pin)
{
    if (standby_pin != NC)
    {
        standby = 0;
    }
    rx_thread.start(callback(this, &CANInterface::rx_handler));
}

