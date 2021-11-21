#include <mbed.h>
#include "MotorInterface.h"
#include <rtos.h>
#include "pindef.h"
#include "Printing.h"
#include "MotorCANInterface.h"
#include "MotorControllerCANInterface.h"

#define TESTING     // only defined if using test functions
// #define DEBUGGING   // only define if debugging

#define MAIN_LOOP_PERIOD 1s
#define CAN_PERIOD 1s

BufferedSerial device(USBTX, USBRX);

MotorCANInterface vehicle_can_interface(MAIN_CAN_RX, MAIN_CAN_TX);
MotorControllerCANInterface motor_controller_can_interface(MTR_CTRL_CAN_RX, MTR_CTRL_CAN_TX, MTR_CTRL_CAN_STBY);

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

        PowerAuxExampleStruct a(1, 2, 3, 4);
        vehicle_can_interface.send(&a);

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

void MotorCANInterface::handle(PowerAuxExampleStruct *can_struct)
{
    PRINT("Received PowerAuxExampleStruct: a=%u, b=%u, c=%u, d=%d\r\n", can_struct->a, can_struct->b, can_struct->c, can_struct->d);
}
