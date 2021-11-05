#include <mbed.h>
#include <limits.h>
#include "pindef.h"
#include "Printing.h"
#include "MotorInterface.h"

#define TESTING     // only defined if using test functions
// #define DEBUGGING   // only define if debugging

#define MAIN_LOOP_PERIOD_MS 20  // units of 1 ms

Mutex main_printing_mutex;
BufferedSerial device(USBTX, USBRX);

CAN can(CAN_RX, CAN_TX);
DigitalOut canStby(CAN_STBY);
Ticker canTxTicker;

I2C throttle(SDA_ACCEL, SCL_ACCEL);
I2C regen(SDA_REGEN, SCL_REGEN);

MotorInterface motorInterface(throttle, regen);

int main() {
    // device.set_baud(38400);
    init_printing(&main_printing_mutex);
#ifdef TESTING
    PRINT("start main() \r\n");
#endif //TESTING
    // motorInterface.sendThrottle(1500);
    while(1){
        #ifdef TESTING
            PRINT("main thread loop \r\n");
        #endif //TESTING
        motorInterface.sendThrottle(256);
        thread_sleep_for(MAIN_LOOP_PERIOD_MS);
        motorInterface.sendThrottle(200);
        thread_sleep_for(MAIN_LOOP_PERIOD_MS);
        motorInterface.sendThrottle(150);
        thread_sleep_for(MAIN_LOOP_PERIOD_MS);
        motorInterface.sendThrottle(100);
        thread_sleep_for(MAIN_LOOP_PERIOD_MS);
        motorInterface.sendThrottle(50);
        thread_sleep_for(MAIN_LOOP_PERIOD_MS);
        motorInterface.sendThrottle(0);
        thread_sleep_for(MAIN_LOOP_PERIOD_MS);

    }
}
