#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H

#include <mbed.h>
#include "CANParser.h"
#include "NoMutexCAN.h"

class CANInterface
{
public:
    CANInterface(PinName rd, PinName td, CANParser &cp, Thread &rx_thread, Thread &tx_thread, DigitalOut *stby=nullptr, std::chrono::milliseconds can_period = 1s, int rx_queue_size = 64);
    void start_CAN_transmission(void);

private:
    void rx_isr(void);
    void rx_handler(CANMessage message);
    void tx_handler(void);

    NoMutexCAN can;
    CANParser &can_parser;
    DigitalOut *standby;

    Thread &rx_thread;
    Thread &tx_thread;

    std::chrono::milliseconds tx_period;

    EventQueue rx_queue;
};

#endif