#include <mbed.h>
#include "pindef.h"
#include "Printing.h"
#include "CANStructs.h"

#define TESTING     // only defined if using test functions
// #define DEBUGGING   // only define if debugging

#define MAIN_LOOP_PERIOD_MS 1000  // units of 1 ms

BufferedSerial device(USBTX, USBRX);

CAN can(CAN_RX, CAN_TX);

DigitalOut canStby(CAN_STBY);

Ticker canTxTicker;

void parseCANMessage(const CANMessage& msg)
{
    uint8_t messagePriority = GET_PRIORITY(msg.id);
    uint8_t messageNodeID = GET_NODE_ID(msg.id);

    PRINT("%s\r\n", msg.data);
}

// WARNING: This method will be called in an ISR context
void canTxIrqHandler()
{
    string toSend = "Hello!";
    if (can.write(CANMessage(GET_CAN_MESSAGE_ID(0,0), toSend.c_str(), toSend.length())))
    {
#ifdef TESTING
        PRINT("Message sent!\r\n");
#endif //TESTING
    }
}

// WARNING: This method will be called in an ISR context
void canRxIrqHandler()
{
    CANMessage receivedCANMessage;
    while (can.read(receivedCANMessage))
    {
#ifdef TESTING
        PRINT("Message received!\r\n");
#endif //TESTING
        parseCANMessage(receivedCANMessage);
    }
}

void canInit()
{
    canTxTicker.attach(&canTxIrqHandler, CAN_PERIOD);
    can.attach(&canRxIrqHandler, CAN::RxIrq);
    canStby = 0;
}

int main() {
    // device.set_baud(38400);
    
#ifdef TESTING
    PRINT("start main() \r\n");
#endif //TESTING

    canInit();
    
    while(1){
        #ifdef TESTING
            PRINT("main thread loop \r\n");
        #endif //TESTING

        thread_sleep_for(MAIN_LOOP_PERIOD_MS);
    }
}
