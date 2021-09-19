#include "CANInterface.h"
#include "Printing.h"

CANInterface::CANInterface(PinName rd, PinName td, CANParser &cp, PinName standby_pin, std::chrono::milliseconds tx_prd) : can(rd, td), can_parser(cp), standby(standby_pin), tx_period(tx_prd)
{
    standby = 0;
}

void CANInterface::start_CAN_transmission(void)
{
    rx_thread.start(callback(this, &CANInterface::rx_handler));
    tx_thread.start(callback(this, &CANInterface::tx_handler));
}

void CANInterface::rx_handler(void)
{
    while(1)
    {
        CANMessage receivedCANMessage;
        while (can.read(receivedCANMessage))
        {
            can_parser.parse(receivedCANMessage);
        }
    }
}

void CANInterface::tx_handler(void)
{
    while(1)
    {
        queue<CANMessage> *fifo = can_parser.get_messages();
        while(!fifo->empty())
        {
            can.write(fifo->front());
            fifo->pop();
        }
        ThisThread::sleep_for(tx_period);
    }
}
