#ifndef POWER_AUX_CAN_STRUCTS_H
#define POWER_AUX_CAN_STRUCTS_H

#include "CANSerializer.h"

typedef struct PowerAuxExampleStruct
{
    uint32_t a;
    uint16_t b;
    uint8_t c;
    int8_t d;
    SERIALIZATION_METHODS((a, 32), (b, 16), (c, 8), (d, 8))
} PowerAuxExampleStruct;

#endif
