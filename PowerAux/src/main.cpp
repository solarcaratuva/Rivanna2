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

CAN bms_can(BMS_CAN1_RX, BMS_CAN1_TX);
DigitalOut bms_can_stby(BMS_CAN1_STBY);
Thread bms_can_tx_thread;
Thread bms_can_rx_thread;

CAN vehicle_can(MAIN_CAN_RX, MAIN_CAN_TX);
DigitalOut vehicle_can_stby(MAIN_CAN_STBY);
Thread vehicle_can_tx_thread;
Thread vehicle_can_rx_thread;

PowerAuxCANParser bms_can_parser;
PowerAuxCANParser vehicle_can_parser;
CANInterface bms_can_interface(bms_can, bms_can_parser, bms_can_tx_thread, bms_can_rx_thread, &bms_can_stby, CAN_PERIOD);
CANInterface vehicle_can_interface(vehicle_can, vehicle_can_parser, vehicle_can_tx_thread, vehicle_can_rx_thread, &vehicle_can_stby, CAN_PERIOD);

int main() {
    // device.set_baud(38400);

#ifdef TESTING
    PRINT("start main() \r\n");
#endif //TESTING
    
    bms_can_interface.startCANTransmission();
    vehicle_can_interface.startCANTransmission();

    while(1){
        #ifdef TESTING
            PRINT("main thread loop \r\n");
        #endif //TESTING

        bms_can_parser.powerAuxExampleStruct.a++;
        bms_can_parser.powerAuxExampleStruct.b += 2;
        bms_can_parser.powerAuxExampleStruct.c += 3;
        bms_can_parser.powerAuxExampleStruct.d += 4;

        ThisThread::sleep_for(MAIN_LOOP_PERIOD);
    }
}
