#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H

#include <mbed.h>

#include "CANParser.h"

class CANInterface
{
public:
    CANInterface(CAN &c, CANParser &cp, Ticker &tx, DigitalOut *stby=nullptr, std::chrono::microseconds txPeriod=0s);

private:
    void rxHandler();
    void txHandler();

    CAN &can;
    CANParser &canParser;
    Ticker &txTicker;
    DigitalOut *standby;
};

#endif