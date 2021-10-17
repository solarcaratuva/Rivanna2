#ifndef SOLAR_CAN_STRUCTS_H
#define SOLAR_CAN_STRUCTS_H

#include <stdio.h>
#include "CANSerializer.h"

typedef struct SolarCurrent
{
    int16_t total_current;
    SERIALIZATION_METHODS((total_current, 16))
} SolarCurrent;

typedef struct SolarVoltage
{
    int16_t panel1_voltage;
    int16_t panel2_voltage;
    int16_t panel3_voltage;
    int16_t panel4_voltage;
    SERIALIZATION_METHODS(
        (panel1_voltage, 16),
        (panel2_voltage, 16),
        (panel3_voltage, 16),
        (panel4_voltage, 16)
    )
} SolarVoltage;

typedef struct SolarTemp
{
    int16_t panel1_temp;
    int16_t panel2_temp;
    int16_t panel3_temp;
    int16_t panel4_temp;
    SERIALIZATION_METHODS(
        (panel1_temp, 16),
        (panel2_temp, 16),
        (panel3_temp, 16),
        (panel4_temp, 16)
    )
} SolarTemp;

typedef struct SolarPhoto
{
    int16_t panel1_photo;
    int16_t panel2_photo;
    int16_t panel3_photo;
    int16_t panel4_photo;
    SERIALIZATION_METHODS(
        (panel1_photo, 16),
        (panel2_photo, 16),
        (panel3_photo, 16),
        (panel4_photo, 16)
    )
} SolarPhoto;

#endif