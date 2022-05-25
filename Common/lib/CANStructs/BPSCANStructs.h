#ifndef BPS_CAN_STRUCTS_H
#define BPS_CAN_STRUCTS_H

#include "CANStruct.h"
#include "bitproto/structs/bps_bp.h"
#include "log.h"

/**
 * General BPS information.
 * NOTE: This struct has not been tested thoroughly, there may be transcription
 * or padding errors.
 */
typedef struct BPSPackInformation : CANStruct, BitprotoBPSPackInformation {
    void serialize(CANMessage *message) {
        EncodeBitprotoBPSPackInformation(this, message->data);
        message->len = BYTES_LENGTH_BITPROTO_BPS_PACK_INFORMATION;
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoBPSPackInformation(this, message->data);
    }

    uint32_t get_message_ID() { return BPSPackInformation_MESSAGE_ID; }

    void log(int level) {
        char buffer[2048] = {0};
        const char *start = "BPSPackInformation: ";
        strcat(buffer, start);
        JsonBitprotoBPSPackInformation(this, buffer + strlen(start));

        log_at_level(level, buffer);
    }
} BPSPackInformation;

/**
 * BPS errors.
 * NOTE: This struct has not been tested thoroughly, there may be transcription
 * or padding errors.
 */
typedef struct BPSError : CANStruct, BitprotoBPSError {
    void serialize(CANMessage *message) {
        EncodeBitprotoBPSError(this, message->data);
        message->len = BYTES_LENGTH_BITPROTO_BPS_ERROR;
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoBPSError(this, message->data);
    }

    uint32_t get_message_ID() { return BPSError_MESSAGE_ID; }

    bool has_error() {
        return internal_communications_fault || internal_conversion_fault ||
               weak_cell_fault || low_cell_voltage_fault || open_wiring_fault ||
               current_sensor_fault || pack_voltage_sensor_fault ||
               weak_pack_fault || voltage_redundancy_fault ||
               fan_monitor_fault || thermistor_fault ||
               CANBUS_communications_fault || always_on_supply_fault ||
               high_voltage_isolation_fault || power_supply_12v_fault ||
               charge_limit_enforcement_fault ||
               discharge_limit_enforcement_fault ||
               charger_safety_relay_fault || internal_memory_fault ||
               internal_thermistor_fault || internal_logic_fault;
    }

    void log(int level) {
        char buffer[2048] = {0};
        const char *start = "BPSError: ";
        strcat(buffer, start);
        JsonBitprotoBPSError(this, buffer + strlen(start));

        log_at_level(level, buffer);
    }
} BPSError;

/**
 * Extreme (low and high only) cell voltage data.
 * NOTE: This struct has not been tested thoroughly, there may be transcription
 * or padding errors.
 */
typedef struct BPSCellVoltage : CANStruct, BitprotoBPSCellVoltage {
    void serialize(CANMessage *message) {
        EncodeBitprotoBPSCellVoltage(this, message->data);
        message->len = BYTES_LENGTH_BITPROTO_BPS_CELL_VOLTAGE;
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoBPSCellVoltage(this, message->data);
    }

    uint32_t get_message_ID() { return BPSCellVoltage_MESSAGE_ID; }

    void log(int level) {
        char buffer[2048] = {0};
        const char *start = "BPSCellVoltage: ";
        strcat(buffer, start);
        JsonBitprotoBPSCellVoltage(this, buffer + strlen(start));

        log_at_level(level, buffer);
    }
} BPSCellVoltage;

/**
 * Extreme (low and high only) cell temperature data.
 * NOTE: This struct has not been tested thoroughly, there may be transcription
 * or padding errors.
 */
typedef struct BPSCellTemperature : CANStruct, BitprotoBPSCellTemperature {
    void serialize(CANMessage *message) {
        EncodeBitprotoBPSCellTemperature(this, message->data);
        message->len = BYTES_LENGTH_BITPROTO_BPS_CELL_TEMPERATURE;
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoBPSCellTemperature(this, message->data);
    }

    uint32_t get_message_ID() { return BPSCellTemperature_MESSAGE_ID; }

    void log(int level) {
        char buffer[2048] = {0};
        const char *start = "BPSCellTemperature: ";
        strcat(buffer, start);
        JsonBitprotoBPSCellTemperature(this, buffer + strlen(start));

        log_at_level(level, buffer);
    }
} BPSCellTemperature;

#endif