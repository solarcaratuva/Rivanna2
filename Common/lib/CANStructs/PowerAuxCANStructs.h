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

    uint16_t get_message_ID() { return PowerAuxErrorStruct_MESSAGE_ID; }

    void print() {
        PRINT("PowerAuxErrorStruct\n Fan Error: %d\n Brake Light Error: %d\n "
              "Headlight Error: %d\n BMS Strobe Error: %d\n, Left Turn Error: "
              "%d\n Right Turn Error: %d\n",
              fan_error, brake_light_error, headlight_error, bms_strobe_error,
              left_turn_error, right_turn_error);
    }
} PowerAuxErrorStruct;

#endif
