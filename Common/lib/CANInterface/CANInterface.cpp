#include "CANInterface.h"
#include "Printing.h"

#define CAN_PERIOD  1000ms

CANInterface::CANInterface(CAN &c, CANParser &cp, Thread &tx_thrd, Thread &rx_thrd, DigitalOut *stby, std::chrono::milliseconds tx_prd) : can(c), can_parser(cp), tx_thread(rx_thrd), rx_thread(tx_thrd), tx_period(tx_prd)
{    
    if(stby)    // should these be checked in the rx/tx threads? once we initialize this we 
    {           // won't have control over it anymore 
        standby = stby;
        *standby = 0;   // active low
    }
}

void CANInterface::startCANTransmission(void)
{
    tx_thread.start(callback(this, &CANInterface::tx_handler));
    rx_thread.start(callback(this, &CANInterface::rx_handler));
}

// WARNING: This method will be called in an ISR context
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

// WARNING: This method will be called in an ISR context
void CANInterface::tx_handler(void)
{
    while(1)
    {
        queue<CANMessage> fifo = can_parser.getMessages();
        while(!fifo.empty())
        {
            can.write(fifo.front());
            fifo.pop();
        }
        ThisThread::sleep_for(tx_period);
    }
}
