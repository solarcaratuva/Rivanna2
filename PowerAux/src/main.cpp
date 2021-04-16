#include <mbed.h>
#include "pindef.h"
#include "Printing.h"
// #include "CANStructs.h"
#include "PowerAuxCANParser.h"
#include "CANInterface.h"

#define TESTING     // only defined if using test functions
// #define DEBUGGING   // only define if debugging

#define MAIN_LOOP_PERIOD_MS 1000  // units of 1 ms

BufferedSerial device(USBTX, USBRX);

CAN can(CAN_RX, CAN_TX);
DigitalOut canStby(CAN_STBY);
Ticker canTxTicker;

CAN can2(CAN2_RX, CAN2_TX);
DigitalOut can2Stby(CAN2_STBY);
Ticker can2TxTicker;

PowerAuxCANParser canParser;
CANInterface canInterface(can, canParser, canTxTicker, &canStby, 1s);
CANInterface can2Interface(can2, canParser, can2TxTicker, &can2Stby, 1s);

int main() {
    // device.set_baud(38400);
    
#ifdef TESTING
    PRINT("start main() \r\n");
#endif //TESTING
    
    while(1){
        #ifdef TESTING
            PRINT("main thread loop \r\n");
        #endif //TESTING

        thread_sleep_for(MAIN_LOOP_PERIOD_MS);
    }
}
