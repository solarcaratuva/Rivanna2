#include <mbed.h>
#include "pindef.h"
#include "Printing.h"
#include "MotorInterface.h"

#define TESTING     // only defined if using test functions
// #define DEBUGGING   // only define if debugging

#define MAIN_LOOP_PERIOD_MS 1000  // units of 1 ms

BufferedSerial device(USBTX, USBRX);

CAN can(CAN_RX, CAN_TX);
DigitalOut canStby(CAN_STBY);
Ticker canTxTicker;

I2C throttle(PB_8, PB_9);//(SDA_ACCEL, SCL_ACCEL);
I2C regen(PF_15, PF_14);//(SDA_REGEN, SCL_REGEN);
I2C testMessage(PB_11, PB_10);
DigitalIn testEn(PF_13);
DigitalOut enable(PE_9);//(DIR_ACCEL);
MotorInterface motorInterface(throttle, regen, enable);

int main() {
    // device.set_baud(38400);
    
#ifdef TESTING
    PRINT("start main() \r\n");
#endif //TESTING
    // motorInterface.startTransmission();
    while(1){
        #ifdef TESTING
            PRINT("main thread loop \r\n");
        #endif //TESTING
        // printf("%d", testEn.read());
        // motorInterface.sendThrottle(15);
        // printf("%d", testMessage.read(1));
        // thread_sleep_for(MAIN_LOOP_PERIOD_MS);
    }
}
