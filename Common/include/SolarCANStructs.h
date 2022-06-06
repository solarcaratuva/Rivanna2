#ifndef SOLAR_CAN_STRUCTS_H
#define SOLAR_CAN_STRUCTS_H

#include "CANStruct.h"
#include "dbc/structs/rivanna2.h"
#include "log.h"

typedef struct SolarCurrent : CANStruct, rivanna2_solar_current_t {
    void serialize(CANMessage *message) {
        rivanna2_solar_current_pack(message->data, this,
                                    RIVANNA2_SOLAR_CURRENT_LENGTH);
        message->len = RIVANNA2_SOLAR_CURRENT_LENGTH;
    }

    void deserialize(CANMessage *message) {
        rivanna2_solar_current_unpack(this, message->data,
                                      RIVANNA2_SOLAR_CURRENT_LENGTH);
    }

    uint32_t get_message_ID() { return SolarCurrent_MESSAGE_ID; }

    void log(int level) {
        log_at_level(level, "SolarCurrent: total_current %u", total_current);
    }
} SolarCurrent;

typedef struct SolarVoltage : CANStruct, rivanna2_solar_voltage_t {
    void serialize(CANMessage *message) {
        rivanna2_solar_voltage_pack(message->data, this,
                                    RIVANNA2_SOLAR_VOLTAGE_LENGTH);
        message->len = RIVANNA2_SOLAR_VOLTAGE_LENGTH;
    }

    void deserialize(CANMessage *message) {
        rivanna2_solar_voltage_unpack(this, message->data,
                                      RIVANNA2_SOLAR_VOLTAGE_LENGTH);
    }

    uint32_t get_message_ID() { return SolarVoltage_MESSAGE_ID; }

    void log(int level) {
        log_at_level(level,
                     "SolarVoltage: panel1_voltage %u, panel2_voltage %u, "
                     "panel3_voltage %u, panel4_voltage %u",
                     panel1_voltage, panel2_voltage, panel3_voltage,
                     panel4_voltage);
    }
} SolarVoltage;

typedef struct SolarTemp : CANStruct, rivanna2_solar_temp_t {
    void serialize(CANMessage *message) {
        rivanna2_solar_temp_pack(message->data, this,
                                 RIVANNA2_SOLAR_TEMP_LENGTH);
        message->len = RIVANNA2_SOLAR_TEMP_LENGTH;
    }

    void deserialize(CANMessage *message) {
        rivanna2_solar_temp_unpack(this, message->data,
                                   RIVANNA2_SOLAR_TEMP_LENGTH);
    }

    uint32_t get_message_ID() { return SolarTemp_MESSAGE_ID; }

    void log(int level) {
        log_at_level(level,
                     "SolarTemp: panel1_temp %u, panel2_temp %u, panel3_temp "
                     "%u, panel4_temp %u",
                     panel1_temp, panel2_temp, panel3_temp, panel4_temp);
    }
} SolarTemp;

typedef struct SolarPhoto : CANStruct, rivanna2_solar_photo_t {
    void serialize(CANMessage *message) {
        rivanna2_solar_photo_pack(message->data, this,
                                  RIVANNA2_SOLAR_PHOTO_LENGTH);
        message->len = RIVANNA2_SOLAR_PHOTO_LENGTH;
    }

    void deserialize(CANMessage *message) {
        rivanna2_solar_photo_unpack(this, message->data,
                                    RIVANNA2_SOLAR_PHOTO_LENGTH);
    }

    uint32_t get_message_ID() { return SolarPhoto_MESSAGE_ID; }

    void log(int level) {
        log_at_level(level,
                     "SolarPhoto: panel1_photo %u, panel2_photo %u, "
                     "panel3_photo %u, panel4_photo %u",
                     panel1_photo, panel2_photo, panel3_photo, panel4_photo);
    }
} SolarPhoto;

#endif