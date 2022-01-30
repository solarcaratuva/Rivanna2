#include <mbed.h>
#include <rtos.h>
#include "pindef.h"
#include "Printing.h"
#include "SolarCANInterface.h"
#include "mcp3008.h"

#define TESTING     // only defined if using test functions
// #define DEBUGGING   // only define if debugging

#define MAIN_LOOP_PERIOD 1s
#define CAN_PERIOD 1s

SolarCANInterface vehicle_can_interface(CAN_RX, CAN_TX, CAN_STBY);

SPI adc1(ADC1_MOSI, ADC1_MISO, ADC1_CLK);
MCP3008 adc1_inteface(&adc1, ADC1_CS);

SPI adc2(ADC2_MOSI, ADC2_MOSI,ADC2_CLK);
MCP3008 adc2_inteface(&adc2, ADC2_CS);

int main() {
#ifdef TESTING
    PRINT("start main() \r\n");
#endif //TESTING
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
