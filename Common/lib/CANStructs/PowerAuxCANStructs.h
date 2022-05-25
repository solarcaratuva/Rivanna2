#ifndef POWER_AUX_CAN_STRUCTS_H
#define POWER_AUX_CAN_STRUCTS_H

#include "CANStruct.h"
#include "bitproto/structs/power_aux_bp.h"

typedef struct PowerAuxError : CANStruct, BitprotoPowerAuxError {
    void serialize(CANMessage *message) {
        EncodeBitprotoPowerAuxError(this, message->data);
        message->len = BYTES_LENGTH_BITPROTO_POWER_AUX_ERROR;
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoPowerAuxError(this, message->data);
    }

    uint32_t get_message_ID() { return PowerAuxError_MESSAGE_ID; }

    bool has_error() {
        return fan_error || brake_light_error || headlight_error ||
               bms_strobe_error || left_turn_error || right_turn_error;
    }

    void log(int level) {
        char buffer[2048] = {0};
        const char *start = "PowerAuxError: ";
        strcat(buffer, start);
        JsonBitprotoPowerAuxError(this, buffer + strlen(start));

        log_at_level(level, buffer);
    }
} PowerAuxError;

#endif
