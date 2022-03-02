#ifndef POWER_AUX_CAN_STRUCTS_H
#define POWER_AUX_CAN_STRUCTS_H

#include "CANSerializer.h"
#include "CANStruct.h"
#include "Printing.h"

typedef struct PowerAuxErrorStruct : CANStruct {
    bool fan_error;
    bool brake_light_error;
    bool headlight_error;
    bool bms_strobe_error;
    bool left_turn_error;
    bool right_turn_error;

    PowerAuxErrorStruct() {}
    PowerAuxErrorStruct(bool fan_error, bool brake_light_error,
                        bool headlight_error, bool bms_strobe_error,
                        bool left_turn_error, bool right_turn_error)
        : fan_error(fan_error), brake_light_error(brake_light_error),
          headlight_error(headlight_error), bms_strobe_error(bms_strobe_error),
          left_turn_error(left_turn_error), right_turn_error(right_turn_error) {
    }

    SERIALIZATION_METHODS((fan_error, 1), (brake_light_error, 1),
                          (headlight_error, 1), (bms_strobe_error, 1),
                          (left_turn_error, 1), (right_turn_error, 1)

    );

    bool has_error() {
        return fan_error || brake_light_error || headlight_error ||
               bms_strobe_error || left_turn_error || right_turn_error;
    }

    void print() {
        PRINT("PowerAuxErrorStruct\n Fan Error: %d\n Brake Light Error: %d\n "
              "Headlight Error: %d\n BMS Strobe Error: %d\n, Left Turn Error: "
              "%d\n Right Turn Error: %d\n",
              fan_error, brake_light_error, headlight_error, bms_strobe_error,
              left_turn_error, right_turn_error);
    }

    uint32_t get_message_ID() { return PowerAuxErrorStruct_MESSAGE_ID; }
} PowerAuxErrorStruct;

#endif
