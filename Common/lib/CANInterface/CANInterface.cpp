#include "CANInterface.h"

CANInterface::CANInterface(PinName rd, PinName td, PinName standby_pin) : can(rd, td), standby(standby_pin)
{
    standby = 0;
}

void CANInterface::start_CAN_transmission()
{
    rx_thread.start(callback(this, &CANInterface::rx_handler));
}
