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
        char buffer[2048] = {0};
        const char *start = "SolarCurrent: ";
        strcat(buffer, start);
        JsonBitprotoSolarCurrent(this, buffer + strlen(start));

        log_at_level(level, buffer);
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
        char buffer[2048] = {0};
        const char *start = "SolarVoltage: ";
        strcat(buffer, start);
        JsonBitprotoSolarVoltage(this, buffer + strlen(start));

        log_at_level(level, buffer);
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
        char buffer[2048] = {0};
        const char *start = "SolarTemp: ";
        strcat(buffer, start);
        JsonBitprotoSolarTemp(this, buffer + strlen(start));

        log_at_level(level, buffer);
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
        char buffer[2048] = {0};
        const char *start = "SolarPhoto: ";
        strcat(buffer, start);
        JsonBitprotoSolarPhoto(this, buffer + strlen(start));

        log_at_level(level, buffer);
    }
} SolarPhoto;

#endif