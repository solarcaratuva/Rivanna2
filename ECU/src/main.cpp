#include <mbed.h>
#include <rtos.h>
#include "pindef.h"
#include "Printing.h"
#include "ECUParser.h"
#include "CANInterface.h"

#define TESTING     // only defined if using test functions
// #define DEBUGGING   // only define if debugging

#define MAIN_LOOP_PERIOD 1s
#define CAN_PERIOD 1s

ECUParser vehicle_can_parser;
CANInterface vehicle_can_interface(CAN_RX, CAN_TX, vehicle_can_parser, CAN_STBY, CAN_PERIOD);

int main() {
#ifdef TESTING
    PRINT("start main() \r\n");
#endif //TESTING
    
    vehicle_can_interface.start_CAN_transmission();

    while(1){
        #ifdef TESTING
            PRINT("main thread loop \r\n");
        #endif //TESTING

        PowerAuxExampleStruct a = { 1, 2, 3, 4 };
        vehicle_can_parser.push_power_aux_example_struct(&a);

        ThisThread::sleep_for(MAIN_LOOP_PERIOD);
    }
}
