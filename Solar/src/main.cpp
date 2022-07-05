#include "Printing.h"
#include "SolarCANInterface.h"
#include "SolarInputReader.h"
#include "log.h"
#include "mcp3008.h"
#include "pindef.h"
#include <mbed.h>
#include <rtos.h>

#define LOG_LEVEL        LOG_DEBUG
#define MAIN_LOOP_PERIOD 1s

SolarCANInterface vehicle_can_interface(CAN_RX, CAN_TX, CAN_STBY);

SPI adc1(ADC1_MOSI, ADC1_MISO, ADC1_CLK);
MCP3008 adc1_interface(&adc1, ADC1_CS);

SPI adc2(ADC2_MOSI, ADC2_MISO, ADC2_CLK);
MCP3008 adc2_interface(&adc2, ADC2_CS);

SolarInputReader input_reader(adc1_interface, adc2_interface);

int main() {
    log_set_level(LOG_LEVEL);
    log_debug("Start main()");

    while (true) {
        log_debug("Main thread loop");

        SolarCurrent current;
        current.total_current = input_reader.readTotalCurrent();
        vehicle_can_interface.send(&current);

        SolarVoltage voltage;
        voltage.panel1_voltage = input_reader.readPanel1Voltage();
        voltage.panel2_voltage = input_reader.readPanel2Voltage();
        voltage.panel3_voltage = input_reader.readPanel3Voltage();
        voltage.panel4_voltage = input_reader.readPanel4Voltage();
        vehicle_can_interface.send(&voltage);

        SolarTemp temp;
        temp.panel1_temp = input_reader.readPanel1Temp();
        temp.panel2_temp = input_reader.readPanel2Temp();
        temp.panel3_temp = input_reader.readPanel3Temp();
        temp.panel4_temp = input_reader.readPanel4Temp();
        vehicle_can_interface.send(&temp);

        SolarPhoto photo;
        photo.panel1_photo = input_reader.readPanel1Photo();
        photo.panel2_photo = input_reader.readPanel2Photo();
        photo.panel3_photo = input_reader.readPanel3Photo();
        photo.panel4_photo = input_reader.readPanel4Photo();
        vehicle_can_interface.send(&photo);

        ThisThread::sleep_for(MAIN_LOOP_PERIOD);
    }
}
