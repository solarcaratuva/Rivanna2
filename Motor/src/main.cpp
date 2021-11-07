// CAN vehicle_can(PB_12, PB_13);
// DigitalOut vehicle_can_stby(PA_10);

#include <mbed.h>
#include "MotorInterface.h"
#include <rtos.h>
#include "pindef.h"
#include "Printing.h"
#include "MotorCANParser.h"
#include "CANInterface.h"

#define TESTING     // only defined if using test functions
// #define DEBUGGING   // only define if debugging

#define MAIN_LOOP_PERIOD 1s
#define CAN_PERIOD 1s

Mutex main_printing_mutex;
BufferedSerial device(USBTX, USBRX);

MotorCANParser vehicle_can_parser;
CANInterface vehicle_can_interface(PB_12, PB_13, vehicle_can_parser, PA_10, CAN_PERIOD);

I2C throttle(SDA_ACCEL, SCL_ACCEL);
I2C regen(SDA_REGEN, SCL_REGEN);

MotorInterface motorInterface(throttle, regen);

int main() {
#ifdef TESTING
    PRINT("start main() \r\n");
#endif //TESTING
    
    vehicle_can_interface.start_CAN_transmission();

    while(1){
        #ifdef TESTING
            PRINT("main thread loop \r\n");
        #endif //TESTING
        motorInterface.sendThrottle(256);
        ThisThread::sleep_for(MAIN_LOOP_PERIOD);
        motorInterface.sendThrottle(200);
        ThisThread::sleep_for(MAIN_LOOP_PERIOD);
        motorInterface.sendThrottle(150);
        ThisThread::sleep_for(MAIN_LOOP_PERIOD);
        motorInterface.sendThrottle(100);
        ThisThread::sleep_for(MAIN_LOOP_PERIOD);
        motorInterface.sendThrottle(50);
        ThisThread::sleep_for(MAIN_LOOP_PERIOD);
        motorInterface.sendThrottle(0);
        ThisThread::sleep_for(MAIN_LOOP_PERIOD); 
    }
}

