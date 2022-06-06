/**
 * @file mcp32008.h
 */

#include "mbed.h"

#ifndef MCP3008_H
#define MCP3008_H

/** Polarity setting for differential inputs.
 *
 * POL_EVEN_POSITIVE sets channel [0|2|4|6] as the positive side and channel
 * [1|3|5|7] as the negative side. POL_EVEN_NEGATIVE sets the opposite.
 */
enum Polarity { POL_EVEN_POSITIVE, POL_EVEN_NEGATIVE };

/** Class for interfacing to the MCP3008 SPI-based ADC.
 *
 */
class MCP3008 {
  public:
    /** Create an MCP3008 object.
     *
     * @param bus An SPI bus object.
     * @param cs The name of a pin to use as the chip select.
     */
    MCP3008(SPI *p_bus, PinName cs);
    ~MCP3008();

    /** Read from a single-ended input.
     *
     * @param channel The channel number to read from.
     *
     * @param returns The sampled value as a float between 0.0 and 1.0.
     */
    float read_input(int channel);

    /** Read from a single-ended input.
     *
     * @param channel The channel number to read from.
     *
     * @param returns The sampled value as a unsigned int16_t  between 0 and
     * 1024.
     */
    uint16_t read_input_u16(int channel);

    /** Read from a pair of differential inputs.
     *
     * In differential mode, the channels are referred to as 0 to 3, with
     * polarity set in a separate parameter. This avoids the user having to set
     * the polarity as part of the channel number or having channel numbers
     * increase by two (i.e. the channels being 0, 2, 4, and 6).
     *
     * @param channel The channel number to read from.
     * @param polarity The polarity of the differential signal.
     *
     * @param returns The sampled value as a float between 0.0 and 1.0.
     */
    // float read_diff_input(int channel, Polarity polarity);

  private:
    DigitalOut m_cs;
    SPI *m_p_bus;

    void select();
    void deselect();
};

#endif
