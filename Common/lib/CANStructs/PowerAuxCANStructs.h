#ifndef POWER_AUX_CAN_STRUCTS_H
#define POWER_AUX_CAN_STRUCTS_H

#include "CANStruct.h"
#include "CANSerializer.h"

class PowerAuxExampleStruct : public CANStruct
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

    uint32_t get_message_ID()
    {
        return PowerAuxExampleStruct_MESSAGE_ID;
    }
};

#endif
