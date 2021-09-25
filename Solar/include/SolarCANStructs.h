#ifndef SOLAR_CAN_STRUCTS_H
#define SOLAR_CAN_STRUCTS_H

#include <stdio.h>
#include "CANSerializer.h"

typedef struct SolarExampleStruct {
    uint32_t a;
    uint16_t b;
    uint8_t c;
    int8_t d;
    SERIALIZATION_METHODS((a, 32), (b, 16), (c, 8), (d, 8))
} SolarExampleStruct;

#endif