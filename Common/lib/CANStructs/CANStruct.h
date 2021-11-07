#ifndef CAN_STRUCT_H
#define CAN_STRUCT_H

#include <mbed.h>

class CANStruct
{
    // TODO: Change serialize method to set node id and priority using the new methods
    void serialize(CANMessage *message);
    void deserialize(const CANMessage *message);
    static uint8_t get_node_id();
    static uint8_t get_priority();
};

#endif