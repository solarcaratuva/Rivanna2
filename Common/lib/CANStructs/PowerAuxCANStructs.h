#ifndef POWER_AUX_CAN_STRUCTS_H
#define POWER_AUX_CAN_STRUCTS_H

#include "CANStruct.h"
#include "CANSerializer.h"

class PowerAuxExampleStruct : CANStruct
{
public:
    uint32_t a;
    uint16_t b;
    uint8_t c;
    int8_t d;

    PowerAuxExampleStruct() {}
    PowerAuxExampleStruct(uint32_t a, uint16_t b, uint8_t c, int8_t d)
        : a(a), b(b), c(c), d(d) {}

    SERIALIZATION_METHODS((a, 32), (b, 16), (c, 8), (d, 8))

    static uint8_t get_node_id()
    {
        return 3;
    }

    static uint8_t get_priority()
    {
        return 3;
    }
};

#endif
