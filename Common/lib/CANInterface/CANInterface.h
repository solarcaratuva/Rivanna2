#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H

#include <mbed.h>
#include "CANParser.h"

class CANInterface
{
public:
    CANInterface(CAN &c, CANParser &cp, Thread &tx_thread, Thread &rx_thread, DigitalOut *stby=nullptr, std::chrono::milliseconds can_period = 1s);
    void start_CAN_transmission(void);

private:
    void rx_handler(void);
    void tx_handler(void);

    CAN &can;
    CANParser &can_parser;
    DigitalOut *standby;

    Thread &tx_thread;
    Thread &rx_thread;

    std::chrono::milliseconds tx_period;

};

#endif