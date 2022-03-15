#ifndef CAN_STRUCT_H
#define CAN_STRUCT_H

#include "CANStructMessageIDs.h"
#include <mbed.h>

/**
 * Serializable object to be sent over a CAN bus.
 */
struct CANStruct {
    virtual void serialize(CANMessage *message);
    virtual void deserialize(CANMessage *message);
    virtual uint16_t get_message_ID();
    virtual void print();
};

#endif