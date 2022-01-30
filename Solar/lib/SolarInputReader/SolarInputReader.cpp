#include "SolarInputReader.h"

#define ADC_REF_VOLTAGE 3.3

float get_voltage_from_adc_channel(MCP3008 adc_interface, int channel) {
    uint16_t raw_value = adc_interface.read_input_u16(channel);
    return ((float) raw_value) / 1024.0 * ADC_REF_VOLTAGE;
}

SolarInputReader::SolarInputReader(MCP3008 adc1_interface, MCP3008 adc2_interface) : adc1_interface(adc1_interface), adc2_interface(adc2_interface) {}

uint16_t SolarInputReader::readTotalCurrent() {
    float voltage = get_voltage_from_adc_channel(adc1_interface, 0);
    float transformed_value = voltage * 600.0;
    return (uint16_t)transformed_value;
}
