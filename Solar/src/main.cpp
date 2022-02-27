#include "Printing.h"
#include "SolarCANInterface.h"
#include "SolarInputReader.h"
#include "mcp3008.h"
#include "pindef.h"
#include <mbed.h>
#include <rtos.h>

#define TESTING          // only defined if using test functions
// #define DEBUGGING   // only define if debugging

#define MAIN_LOOP_PERIOD 1s
#define CAN_PERIOD       1s

SolarCANInterface vehicle_can_interface(CAN_RX, CAN_TX, CAN_STBY);

SPI adc1(ADC1_MOSI, ADC1_MISO, ADC1_CLK);
MCP3008 adc1_interface(&adc1, ADC1_CS);

SPI adc2(ADC2_MOSI, ADC2_MISO, ADC2_CLK);
MCP3008 adc2_interface(&adc2, ADC2_CS);

SolarInputReader input_reader(adc1_interface, adc2_interface);

int main() {
#ifdef TESTING
    PRINT("start main() \r\n");
#endif // TESTING
    while (1) {
#ifdef TESTING
        PRINT("main thread loop \r\n");
#endif // TESTING

        PowerAuxExampleStruct a(1, 2, 3, 4);
        vehicle_can_interface.send(&a);

        SolarCurrent current(input_reader.readTotalCurrent());
        vehicle_can_interface.send(&current);

        SolarVoltage voltage(
            input_reader.readPanel1Voltage(), input_reader.readPanel2Voltage(),
            input_reader.readPanel3Voltage(), input_reader.readPanel4Voltage());
        vehicle_can_interface.send(&voltage);

        SolarTemp temp(
            input_reader.readPanel1Temp(), input_reader.readPanel2Temp(),
            input_reader.readPanel3Temp(), input_reader.readPanel4Temp());
        vehicle_can_interface.send(&temp);

        SolarPhoto photo(
            input_reader.readPanel1Photo(), input_reader.readPanel2Photo(),
            input_reader.readPanel3Photo(), input_reader.readPanel4Photo());
        vehicle_can_interface.send(&photo);

        ThisThread::sleep_for(MAIN_LOOP_PERIOD);
    }
}
