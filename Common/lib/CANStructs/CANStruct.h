#ifndef CAN_STRUCT_H
#define CAN_STRUCT_H

#include <mbed.h>
#include "CANStructMessageIDs.h"

class CANStruct
{
public:
    // TODO: Change serialize method to set node id and priority using the new methods
    virtual void serialize(CANMessage *message);
    virtual void deserialize(const CANMessage *message);
    virtual uint16_t get_message_ID();
};

#endif