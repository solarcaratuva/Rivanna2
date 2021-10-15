#include <mbed.h>
#include <rtos.h>
#include "pindef.h"
#include "Printing.h"
#include "PowerAuxCANParser.h"
#include "CANInterface.h"

#define TESTING     // only defined if using test functions
// #define DEBUGGING   // only define if debugging

#define MAIN_LOOP_PERIOD 1s
#define CAN_PERIOD 1s

BufferedSerial device(USBTX, USBRX);

Mutex main_printing_mutex;

PowerAuxCANParser bms_can_parser;
PowerAuxCANParser vehicle_can_parser;
CANInterface bms_can_interface(BMS_CAN1_RX, BMS_CAN1_TX, bms_can_parser, BMS_CAN1_STBY, CAN_PERIOD);
CANInterface vehicle_can_interface(MAIN_CAN_RX, MAIN_CAN_TX, vehicle_can_parser, MAIN_CAN_STBY, CAN_PERIOD);

int main() {
    // device.set_baud(38400);

#ifdef TESTING
    PRINT("start main() \r\n");
#endif //TESTING
    
    bms_can_interface.start_CAN_transmission();
    vehicle_can_interface.start_CAN_transmission();

    while(1){
        #ifdef TESTING
            PRINT("main thread loop \r\n");
        #endif //TESTING

        PowerAuxExampleStruct a = { 1, 2, 3, 4 };
        bms_can_parser.push_power_aux_example_struct(&a);

        ThisThread::sleep_for(MAIN_LOOP_PERIOD);
    }
}
