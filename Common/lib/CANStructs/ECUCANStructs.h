#ifndef ECU_CAN_STRUCTS_H
#define ECU_CAN_STRUCTS_H

#include "CANStruct.h"
#include "bitproto/structs/ecu_bp.h"

typedef struct ECUMotorCommands : CANStruct, BitprotoECUMotorCommands {
    void serialize(CANMessage *message) {
        EncodeBitprotoECUMotorCommands(this, message->data);
        message->len = BYTES_LENGTH_BITPROTO_ECU_MOTOR_COMMANDS;
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoECUMotorCommands(this, message->data);
    }

    uint32_t get_message_ID() { return ECUMotorCommands_MESSAGE_ID; }

    void log(int level) {
        char buffer[2048] = {0};
        const char *start = "ECUMotorCommands: ";
        strcat(buffer, start);
        JsonBitprotoECUMotorCommands(this, buffer + strlen(start));

        log_at_level(level, buffer);
    }
} ECUMotorCommands;

typedef struct ECUPowerAuxCommands : CANStruct, BitprotoECUPowerAuxCommands {
    void serialize(CANMessage *message) {
        EncodeBitprotoECUPowerAuxCommands(this, message->data);
        message->len = BYTES_LENGTH_BITPROTO_ECU_POWER_AUX_COMMANDS;
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoECUPowerAuxCommands(this, message->data);
    }

    uint32_t get_message_ID() { return ECUPowerAuxCommands_MESSAGE_ID; }

    void log(int level) {
        char buffer[2048] = {0};
        const char *start = "ECUPowerAuxCommands: ";
        strcat(buffer, start);
        JsonBitprotoECUPowerAuxCommands(this, buffer + strlen(start));

        log_at_level(level, buffer);
    }
} ECUPowerAuxCommands;

#endif