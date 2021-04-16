#include "CANInterface.h"
#include "Printing.h"

#define CAN_PERIOD  10ms

CANInterface::CANInterface(CAN &c, CANParser &cp, Ticker &tx, DigitalOut *stby, std::chrono::microseconds txPeriod) : can(c), canParser(cp), txTicker(tx)
{
    txTicker.attach(callback(this, &CANInterface::txHandler), (txPeriod==0s ? CAN_PERIOD : txPeriod));
    can.attach(callback(this, &CANInterface::rxHandler), CAN::RxIrq);
    if(stby)
    {
        standby = stby;
        *standby = 0;   // active low
    }
}

// WARNING: This method will be called in an ISR context
void CANInterface::rxHandler()
{
    CANMessage receivedCANMessage;
    while (can.read(receivedCANMessage))
    {
// #ifdef TESTING
        PRINT("Message received!\r\n");
// #endif //TESTING
        canParser.parse(receivedCANMessage);
    }
}

// WARNING: This method will be called in an ISR context
void CANInterface::txHandler()
{
    static int id = 0;
    string toSend = "Hello!";
    if (can.write(CANMessage(id, toSend.c_str(), toSend.length())))
    {
// #ifdef TESTING
        PRINT("[ID: %d] Message sent!\r\n", id);
// #endif //TESTING
    }
    id++;
    if(id == 10)
        id = 0;
}
