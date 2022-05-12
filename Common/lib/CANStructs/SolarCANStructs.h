#ifndef SOLAR_CAN_STRUCTS_H
#define SOLAR_CAN_STRUCTS_H

#include "CANStruct.h"
#include "Printing.h"
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

    void print() { PRINT("SolarCurret\n total_currentL %u\n", total_current); }

    std::string to_string() {
        char buffer[1024];
        int bytes = JsonBitprotoSolarCurrent(this, buffer);
        buffer[bytes] = '\0';
        return std::string(buffer);
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

    void print() {
        PRINT("SolarVoltage\n panel1_voltage: %u\n panel2_voltage: %u\n "
              "panel3_voltage: %u\n panel4_voltage: %u\n",
              panel1_voltage, panel2_voltage, panel3_voltage, panel4_voltage);
    }

    std::string to_string() {
        char buffer[1024];
        int bytes = JsonBitprotoSolarVoltage(this, buffer);
        buffer[bytes] = '\0';
        return std::string(buffer);
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

    void print() {
        PRINT("SolarTemp\n panel1_temp: %u\n panel2_temp: %u\n panel3_temp: "
              "%u\n panel4_temp: %u\n",
              panel1_temp, panel2_temp, panel3_temp, panel4_temp);
    }

    std::string to_string() {
        char buffer[1024];
        int bytes = JsonBitprotoSolarTemp(this, buffer);
        buffer[bytes] = '\0';
        return std::string(buffer);
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
    void print() {
        PRINT("SolarPhoto\n panel1_photo: %u\n panel2_photo: %u\n "
              "panel3_photo: %u\n panel4_photo: %u\n",
              panel1_photo, panel2_photo, panel3_photo, panel4_photo);
    }

    std::string to_string() {
        char buffer[1024];
        int bytes = JsonBitprotoSolarPhoto(this, buffer);
        buffer[bytes] = '\0';
        return std::string(buffer);
    }
} SolarPhoto;

#endif