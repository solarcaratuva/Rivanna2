#ifndef POWER_AUX_CAN_STRUCTS_H
#define POWER_AUX_CAN_STRUCTS_H

#include "CANStruct.h"
#include "Printing.h"
#include "bitproto/structs/power_aux_bp.h"

typedef struct PowerAuxErrorStruct : CANStruct, BitprotoPowerAuxErrorStruct {
    void serialize(CANMessage *message) {
        EncodeBitprotoPowerAuxErrorStruct(this, message->data);
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoPowerAuxErrorStruct(this, message->data);
    }

    uint32_t get_message_ID() { return PowerAuxErrorStruct_MESSAGE_ID; }

    bool has_error() {
        return fan_current || brake_light_current || headlight_current ||
               bms_strobe_current || left_turn_current || right_turn_current;
    }

    void print() {
        PRINT("PowerAuxErrorStruct\n Fan Current: %d\n Brake Light Current: %d\n "
              "Headlight Current: %d\n BMS Strobe Current: %d\n Left Turn Current: "
              "%d\n Right Turn Current: %d\n",
              fan_current, brake_light_current, headlight_current, bms_strobe_current,
              left_turn_current, right_turn_current);
    }
} PowerAuxErrorStruct;

#endif
