#ifndef SOLAR_CAN_STRUCTS_H
#define SOLAR_CAN_STRUCTS_H

#include "CANStruct.h"
#include "CANSerializer.h"

typedef struct SolarCurrent : CANStruct
{
    int16_t total_current;

    SolarCurrent() {}
    SolarCurrent(int16_t total_current) : total_current(total_current) {}

    SERIALIZATION_METHODS((total_current, 16))

    uint32_t get_message_ID()
    {
        return SolarCurrent_MESSAGE_ID;
    }
} SolarCurrent;

typedef struct SolarVoltage : CANStruct
{
    int16_t panel1_voltage;
    int16_t panel2_voltage;
    int16_t panel3_voltage;
    int16_t panel4_voltage;

    SolarVoltage() {}
    SolarVoltage(int16_t panel1_voltage, int16_t panel2_voltage, int16_t panel3_voltage, int16_t panel4_voltage)
        : panel1_voltage(panel1_voltage), panel2_voltage(panel2_voltage), panel3_voltage(panel3_voltage), panel4_voltage(panel4_voltage) {}

    SERIALIZATION_METHODS(
        (panel1_voltage, 16),
        (panel2_voltage, 16),
        (panel3_voltage, 16),
        (panel4_voltage, 16)
    )

    uint32_t get_message_ID()
    {
        return SolarVoltage_MESSAGE_ID;
    }
} SolarVoltage;

typedef struct SolarTemp : CANStruct
{
    int16_t panel1_temp;
    int16_t panel2_temp;
    int16_t panel3_temp;
    int16_t panel4_temp;

    SolarTemp() {}
    SolarTemp(int16_t panel1_temp, int16_t panel2_temp, int16_t panel3_temp, int16_t panel4_temp)
        : panel1_temp(panel1_temp), panel2_temp(panel2_temp), panel3_temp(panel3_temp), panel4_temp(panel4_temp) {}

    SERIALIZATION_METHODS(
        (panel1_temp, 16),
        (panel2_temp, 16),
        (panel3_temp, 16),
        (panel4_temp, 16)
    )

    uint32_t get_message_ID()
    {
        return SolarTemp_MESSAGE_ID;
    }
} SolarTemp;

typedef struct SolarPhoto : CANStruct
{
    int16_t panel1_photo;
    int16_t panel2_photo;
    int16_t panel3_photo;
    int16_t panel4_photo;

    SolarPhoto() {}
    SolarPhoto(int16_t panel1_photo, int16_t panel2_photo, int16_t panel3_photo, int16_t panel4_photo)
        : panel1_photo(panel1_photo), panel2_photo(panel2_photo), panel3_photo(panel3_photo), panel4_photo(panel4_photo) {}

    SERIALIZATION_METHODS(
        (panel1_photo, 16),
        (panel2_photo, 16),
        (panel3_photo, 16),
        (panel4_photo, 16)
    )

    uint32_t get_message_ID()
    {
        return SolarPhoto_MESSAGE_ID;
    }
} SolarPhoto;

#endif