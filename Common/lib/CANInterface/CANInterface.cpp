#include "CANInterface.h"
#include "Printing.h"

#define CAN_PERIOD  1000ms
#define RX_QUEUE_EVENT_SIZE (EVENTS_EVENT_SIZE + sizeof(CANMessage))

CANInterface::CANInterface(PinName rd, PinName td, CANParser &cp, Thread &rx_thrd, Thread &tx_thrd, DigitalOut *stby, std::chrono::milliseconds tx_prd, int rx_queue_size) : can(rd, td), can_parser(cp), rx_thread(rx_thrd), tx_thread(tx_thrd), tx_period(tx_prd), rx_queue(rx_queue_size * RX_QUEUE_EVENT_SIZE)
{
    if(stby)    // should these be checked in the rx/tx threads? once we initialize this we 
    {           // won't have control over it anymore 
        standby = stby;
        *standby = 0;   // active low
    }
}

void CANInterface::start_CAN_transmission(void)
{
    rx_thread.start(callback(&rx_queue, &EventQueue::dispatch_forever));
    tx_thread.start(callback(this, &CANInterface::tx_handler));

    can.attach(callback(this, &CANInterface::rx_isr), CAN::RxIrq);
}

// WARNING: This method will be called in an ISR context
void CANInterface::rx_isr(void)
{
    CANMessage received_message;
    while (can.read(received_message))
    {
        rx_queue.call(callback(this, &CANInterface::rx_handler), received_message);
    }
}

void CANInterface::rx_handler(CANMessage received_message)
{
    can_parser.parse(received_message);
}

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
