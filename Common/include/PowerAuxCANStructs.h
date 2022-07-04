#ifndef POWER_AUX_CAN_STRUCTS_H
#define POWER_AUX_CAN_STRUCTS_H

#include "CANStruct.h"
#include "dbc/structs/rivanna2.h"
#include "log.h"

typedef struct PowerAuxError : CANStruct, rivanna2_power_aux_error_t {
    void serialize(CANMessage *message) {
        rivanna2_power_aux_error_pack(message->data, this,
                                      RIVANNA2_POWER_AUX_ERROR_LENGTH);
        message->len = RIVANNA2_POWER_AUX_ERROR_LENGTH;
    }

    void deserialize(CANMessage *message) {
        rivanna2_power_aux_error_unpack(this, message->data,
                                        RIVANNA2_POWER_AUX_ERROR_LENGTH);
    }

    uint32_t get_message_ID() { return PowerAuxError_MESSAGE_ID; }

    bool has_error() {
        return fan_error || brake_light_error || headlight_error ||
               bps_strobe_error || left_turn_error || right_turn_error;
    }

    void log(int level) {
        log_at_level(level,
                     "PowerAuxError: fan_error %u, brake_light_error %u, "
                     "headlight_error %u, bps_strobe_error %u, left_turn_error "
                     "%u, right_turn_error %u",
                     fan_error, brake_light_error, headlight_error,
                     bps_strobe_error, left_turn_error, right_turn_error);
    }
} PowerAuxError;

#endif
