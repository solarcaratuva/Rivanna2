#include <mbed.h>
#include "pindef.h"
#include "Printing.h"

#define TESTING     // only defined if using test functions
// #define DEBUGGING   // only define if debugging

#define MAIN_LOOP_PERIOD_MS 1000  // units of 1 ms

BufferedSerial device(USBTX, USBRX);

CAN can(CAN_RX, CAN_TX);
DigitalOut canStby(CAN_STBY);
Ticker canTxTicker;

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
