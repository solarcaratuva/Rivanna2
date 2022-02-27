#ifndef SOLAR_INPUT_READER_H
#define SOLAR_INPUT_READER_H
#include "mcp3008.h"

#include <mbed.h>

class SolarInputReader {
  public:
    SolarInputReader(MCP3008 adc1_interface, MCP3008 adc2_interface);

    /*
    Return value: 1mA/LSB
    */
    uint16_t readTotalCurrent();

    /*
    Return value: 1mV/LSB
    */
    uint16_t readPanel1Voltage();
    uint16_t readPanel2Voltage();
    uint16_t readPanel3Voltage();
    uint16_t readPanel4Voltage();

    /*
    Return value: Degrees Celsius/LSB
    */
    uint16_t readPanel1Temp();
    uint16_t readPanel2Temp();
    uint16_t readPanel3Temp();
    uint16_t readPanel4Temp();

    /*
    Return value: ???/LSB
    */
    uint16_t readPanel1Photo();
    uint16_t readPanel2Photo();
    uint16_t readPanel3Photo();
    uint16_t readPanel4Photo();

  private:
    MCP3008 adc1_interface;
    MCP3008 adc2_interface;
};

#endif