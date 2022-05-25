#ifndef SOLAR_CAN_STRUCTS_H
#define SOLAR_CAN_STRUCTS_H

#include "CANStruct.h"
#include "bitproto/structs/solar_bp.h"

typedef struct SolarCurrent : CANStruct, BitprotoSolarCurrent {
    void serialize(CANMessage *message) {
        EncodeBitprotoSolarCurrent(this, message->data);
        message->len = BYTES_LENGTH_BITPROTO_SOLAR_CURRENT;
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoSolarCurrent(this, message->data);
    }

    uint32_t get_message_ID() { return SolarCurrent_MESSAGE_ID; }

    void log(int level) {
        log_at_level(level, "SolarCurret\n total_currentL %u\n", total_current);
    }
} SolarCurrent;

typedef struct SolarVoltage : CANStruct, BitprotoSolarVoltage {
    void serialize(CANMessage *message) {
        EncodeBitprotoSolarVoltage(this, message->data);
        message->len = BYTES_LENGTH_BITPROTO_SOLAR_VOLTAGE;
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoSolarVoltage(this, message->data);
    }

    uint32_t get_message_ID() { return SolarVoltage_MESSAGE_ID; }

    void log(int level) {
        log_at_level(level,
                     "SolarVoltage\n panel1_voltage: %u\n panel2_voltage: %u\n "
                     "panel3_voltage: %u\n panel4_voltage: %u\n",
                     panel1_voltage, panel2_voltage, panel3_voltage,
                     panel4_voltage);
    }
} SolarVoltage;

typedef struct SolarTemp : CANStruct, BitprotoSolarTemp {
    void serialize(CANMessage *message) {
        EncodeBitprotoSolarTemp(this, message->data);
        message->len = BYTES_LENGTH_BITPROTO_SOLAR_TEMP;
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoSolarTemp(this, message->data);
    }

    uint32_t get_message_ID() { return SolarTemp_MESSAGE_ID; }

    void log(int level) {
        log_at_level(
            level,
            "SolarTemp\n panel1_temp: %u\n panel2_temp: %u\n panel3_temp: "
            "%u\n panel4_temp: %u\n",
            panel1_temp, panel2_temp, panel3_temp, panel4_temp);
    }
} SolarTemp;

typedef struct SolarPhoto : CANStruct, BitprotoSolarPhoto {
    void serialize(CANMessage *message) {
        EncodeBitprotoSolarPhoto(this, message->data);
        message->len = BYTES_LENGTH_BITPROTO_SOLAR_PHOTO;
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoSolarPhoto(this, message->data);
    }

    uint32_t get_message_ID() { return SolarPhoto_MESSAGE_ID; }

    void log(int level) {
        log_at_level(level,
                     "SolarPhoto\n panel1_photo: %u\n panel2_photo: %u\n "
                     "panel3_photo: %u\n panel4_photo: %u\n",
                     panel1_photo, panel2_photo, panel3_photo, panel4_photo);
    }
} SolarPhoto;

#endif