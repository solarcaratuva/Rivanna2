#ifndef POWER_AUX_CAN_STRUCTS_H
#define POWER_AUX_CAN_STRUCTS_H

#include "CANStruct.h"
#include "CANSerializer.h"

typedef struct PowerAuxErrorStruct : CANStruct
{
    bool fan_error;
    bool brake_light_error;
    bool headlight_error;
    bool bms_strobe_error;
    bool left_turn_error;
    bool right_turn_error; 

    PowerAuxErrorStruct() {}
    // PowerAuxErrorStruct(uint32_t a, uint16_t b, uint8_t c, int8_t d)
    //     : a(a), b(b), c(c), d(d) {}

    SERIALIZATION_METHODS(
        (fan_error, 1), 
        (brake_light_error, 1), 
        (headlight_error, 1), 
        (bms_strobe_error, 1),
        (left_turn_error, 1),
        (right_turn_error, 1)
    
    );

    uint32_t get_message_ID()
    {
        return PowerAuxErrorStruct_MESSAGE_ID;
    }
} PowerAuxErrorStruct;

#endif
