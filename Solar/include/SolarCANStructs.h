#ifndef SOLAR_CAN_STRUCTS_H
#define SOLAR_CAN_STRUCTS_H

#include <stdio.h>

typedef struct SolarCurrent {
    int16_t total_current;
} SolarCurrent;

typedef struct SolarVoltage
{
    int16_t panel1_voltage;
    int16_t panel2_voltage;
    int16_t panel3_voltage;
    int16_t panel4_voltage;
} SolarVoltage;

typedef struct SolarTemp
{
    int16_t panel1_temp;
    int16_t panel2_temp;
    int16_t panel3_temp;
    int16_t panel4_temp;
} SolarTemp;

typedef struct SolarPhoto
{
    int16_t panel1_photo;
    int16_t panel2_photo;
    int16_t panel3_photo;
    int16_t panel4_photo;
} SolarPhoto;

#endif