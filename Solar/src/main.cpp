#include <mbed.h>
#include <rtos.h>
#include "pindef.h"
#include "Printing.h"
#include "SolarCANInterface.h"

#define TESTING     // only defined if using test functions
// #define DEBUGGING   // only define if debugging

#define MAIN_LOOP_PERIOD 1s
#define CAN_PERIOD 1s

SolarCANInterface vehicle_can_interface(CAN_RX, CAN_TX, PB_10);

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

        ThisThread::sleep_for(MAIN_LOOP_PERIOD);
    }
}

void SolarCANInterface::handle(PowerAuxExampleStruct *can_struct)
{
    PRINT("Received PowerAuxExampleStruct: a=%u, b=%u, c=%u, d=%d\r\n", can_struct->a, can_struct->b, can_struct->c, can_struct->d);
}
