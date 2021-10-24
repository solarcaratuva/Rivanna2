#include <mbed.h>
#include <limits.h>
#include "pindef.h"
#include "Printing.h"
#include "MotorInterface.h"

#define TESTING     // only defined if using test functions
// #define DEBUGGING   // only define if debugging

#define MAIN_LOOP_PERIOD_MS 1000  // units of 1 ms

Mutex main_printing_mutex;
BufferedSerial device(USBTX, USBRX);

CAN can(CAN_RX, CAN_TX);
DigitalOut canStby(CAN_STBY);
Ticker canTxTicker;

I2C throttle(SDA_ACCEL, SCL_ACCEL);
I2C regen(SDA_REGEN, SCL_REGEN);
DigitalOut ThrottleEn(DIR_ACCEL);
DigitalOut RegenEn(DIR_REGEN);

MotorInterface motorInterface(throttle, regen, ThrottleEn, RegenEn);

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
        char cmd[1];
        cmd[0] = 0xFF;
        // int result = motorInterface.sendThrottle(cmd);
        // printf("%d", result);
        int result1 = throttle.read(0x00, cmd, 1);
        printf("%d", result1);
        // printf("%d", cmd[0]);
        thread_sleep_for(MAIN_LOOP_PERIOD_MS);
    }
}
