#ifndef POWER_AUX_CAN_STRUCTS_H
#define POWER_AUX_CAN_STRUCTS_H

#include <stdio.h>
#include "cereal/archives/binary.hpp"

typedef struct PowerAuxExampleStruct
{
    uint32_t a;
    uint16_t b;
    uint8_t c;
    int8_t d;

    template<class Archive>
    void serialize(Archive &archive) {
        archive(a, b, c, d);
    }
} PowerAuxExampleStruct;

#endif