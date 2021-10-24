#include <mbed.h>
#include <rtos.h>
#include "pindef.h"
#include "Printing.h"
#include "SolarCANParser.h"
#include "CANInterface.h"
#include "mcp3008.h"

#define TESTING     // only defined if using test functions
// #define DEBUGGING   // only define if debugging

#define MAIN_LOOP_PERIOD 1s
#define CAN_PERIOD 1s

SolarCANParser vehicle_can_parser;
CANInterface vehicle_can_interface(CAN_RX, CAN_TX, vehicle_can_parser, PB_10, CAN_PERIOD);

SPI spi1(ADC1_MOSI, ADC1_MISO, ADC1_CLK);
MCP3008 spi1_inteface(&spi1, ADC1_CS);

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

        for (int channel = 0; channel < 8; channel += 1) {
            uint16_t result = spi1_inteface.read_input_u16(channel);
            if (result > 0) {
                printf("Channel %d = %d\n", channel, result);
            }
        }

        ThisThread::sleep_for(MAIN_LOOP_PERIOD);
    }
}
