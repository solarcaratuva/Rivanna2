#include "mcp3008.h"

#define START_BIT   0x01
#define MODE_SINGLE 0x80 // Single-ended mode
#define MODE_DIFF   0x00 // Differential mode

MCP3008::MCP3008(SPI *p_bus, PinName cs) : m_cs(cs), m_p_bus(p_bus) {
    deselect();
}

MCP3008::~MCP3008() {}

void MCP3008::select() { m_cs = 0; }
void MCP3008::deselect() {
    m_cs = 1;
    wait_us(1);
}

float MCP3008::read_input(int channel) {
    int conv_result = read_input_u16(channel);
    return ((float)conv_result) / 1024;
}

uint16_t MCP3008::read_input_u16(int channel) {
    /*
    int command_high = START_BIT | MODE_SINGLE | ((channel & 0x04) >> 2);
    int command_low = (channel & 0x03) << 6;
    */
    int command_high = START_BIT;
    int command_low = MODE_SINGLE | ((channel & 0x07) << 4);

    select();

    // Odd writing requirements, see the datasheet for details
    m_p_bus->write(command_high);
    int high_byte = m_p_bus->write(command_low) & 0x03;
    int low_byte = m_p_bus->write(0);

    deselect();

    int conv_result = (high_byte << 8) | low_byte;

    return conv_result;
}

#if 0 // not tested.
float MCP3008::read_diff_input(int channel, Polarity polarity)
{
    /*
    int command_high = START_BIT | MODE_DIFF | ((channel & 0x02) >> 1);
    int command_low = ((channel & 0x01) << 7) | (polarity << 6);
    */
    int command_high = START_BIT;
    int command_low = MODE_DIFF | ((channel & 0x03) << 5) | (polarity << 4);
    
    select();
    
    // Odd writing and reading requirements, see the datasheet for details.
    m_p_bus->write(command_high);
    int high_byte = m_p_bus->write(command_low) & 0x03;
    int low_byte = m_p_bus->write(0);
    
    deselect();
    
    int conv_result = (high_byte << 8) | low_byte;
    
    return float(conv_result) / 1024;
}
#endif
