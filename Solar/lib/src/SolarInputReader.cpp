#include "SolarInputReader.h"

#define ADC_REF_VOLTAGE 3.3

float get_voltage_from_adc_channel(MCP3008 adc_interface, int channel) {
    uint16_t raw_value = adc_interface.read_input_u16(channel);
    return ((float)raw_value) / 1024.0 * ADC_REF_VOLTAGE;
}

SolarInputReader::SolarInputReader(MCP3008 adc1_interface,
                                   MCP3008 adc2_interface)
    : adc1_interface(adc1_interface), adc2_interface(adc2_interface) {}

uint16_t SolarInputReader::readTotalCurrent() {
    float voltage = get_voltage_from_adc_channel(adc2_interface, 0);
    float transformed_value = voltage * 600.0;
    return (uint16_t)transformed_value;
}

uint16_t SolarInputReader::readPanel1Voltage() {
    float voltage = get_voltage_from_adc_channel(adc1_interface, 0);
    float transformed_value = voltage * 200.0;
    return (uint16_t)transformed_value;
}

uint16_t SolarInputReader::readPanel2Voltage() {
    float voltage = get_voltage_from_adc_channel(adc1_interface, 2);
    float transformed_value = voltage * 200.0;
    return (uint16_t)transformed_value;
}

uint16_t SolarInputReader::readPanel3Voltage() {
    float voltage = get_voltage_from_adc_channel(adc1_interface, 4);
    float transformed_value = voltage * 200.0;
    return (uint16_t)transformed_value;
}

uint16_t SolarInputReader::readPanel4Voltage() {
    float voltage = get_voltage_from_adc_channel(adc1_interface, 7);
    float transformed_value = voltage * 200.0;
    return (uint16_t)transformed_value;
}

uint16_t SolarInputReader::readPanel1Temp() {
    float voltage = get_voltage_from_adc_channel(adc1_interface, 1);
    float transformed_value = (voltage - 1.25) / 0.005;
    return (uint16_t)transformed_value;
}

uint16_t SolarInputReader::readPanel2Temp() {
    float voltage = get_voltage_from_adc_channel(adc1_interface, 3);
    float transformed_value = (voltage - 1.25) / 0.005;
    return (uint16_t)transformed_value;
}

uint16_t SolarInputReader::readPanel3Temp() {
    float voltage = get_voltage_from_adc_channel(adc1_interface, 5);
    float transformed_value = (voltage - 1.25) / 0.005;
    return (uint16_t)transformed_value;
}

uint16_t SolarInputReader::readPanel4Temp() {
    float voltage = get_voltage_from_adc_channel(adc1_interface, 6);
    float transformed_value = (voltage - 1.25) / 0.005;
    return (uint16_t)transformed_value;
}

uint16_t SolarInputReader::readPanel1Photo() {
    float voltage = get_voltage_from_adc_channel(adc2_interface, 1);
    float transformed_value =
        voltage; // placeholder transfer function; needs to be changed
    return (uint16_t)transformed_value;
}

uint16_t SolarInputReader::readPanel2Photo() {
    float voltage = get_voltage_from_adc_channel(adc2_interface, 3);
    float transformed_value =
        voltage; // placeholder transfer function; needs to be changed
    return (uint16_t)transformed_value;
}

uint16_t SolarInputReader::readPanel3Photo() {
    float voltage = get_voltage_from_adc_channel(adc2_interface, 5);
    float transformed_value =
        voltage; // placeholder transfer function; needs to be changed
    return (uint16_t)transformed_value;
}

uint16_t SolarInputReader::readPanel4Photo() {
    float voltage = get_voltage_from_adc_channel(adc2_interface, 6);
    float transformed_value =
        voltage; // placeholder transfer function; needs to be changed
    return (uint16_t)transformed_value;
}
