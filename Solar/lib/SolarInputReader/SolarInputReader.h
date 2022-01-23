#ifndef SOLAR_INPUT_READER_H
#define SOLAR_INPUT_READER_H
#include "mcp3008.h"


#include <mbed.h>

class SolarInputReader {
    public:
        SolarInputReader(MCP3008 spi1_interface, MCP3008 spi2_interface);

        uint16_t readTotalCurrent();


        uint16_t readPanel1Voltage();
        uint16_t readPanel2Voltage();
        uint16_t readPanel3Voltage();
        uint16_t readPanel4Voltage();

        uint16_t readPanel1Temp();
        uint16_t readPanel2Temp();
        uint16_t readPanel3Temp();
        uint16_t readPanel4Temp();

        uint16_t readPanel1Photo();
        uint16_t readPanel2Photo();
        uint16_t readPanel3Photo();
        uint16_t readPanel4Photo();

        

};

#endif