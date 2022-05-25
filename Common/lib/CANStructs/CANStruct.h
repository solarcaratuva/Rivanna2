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
    /**
     * Gets the message ID for sending on the appropriate bus.
     */
    virtual uint32_t get_message_ID();
    virtual void log(int level);
};

#endif