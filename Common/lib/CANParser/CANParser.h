#ifndef CAN_PARSER_H
#define CAN_PARSER_H

#include <mbed.h>

// TODO: determine & change the message ID format (# of bits for node ID vs priority) 
// CAN message ID (11 bits): Node ID stored in bottom 7 bits (bits 0-6),
//                           Priority stored in next 4 bits (bits 7-10)
#define CAN_MESSAGE_ID(NODE_ID, PRIORITY)   ((NODE_ID&0x7F)|((PRIORITY&0x0F)<<7))
#define CAN_NODE_ID(CAN_MESSAGE_ID)         (CAN_MESSAGE_ID&0x7F)
#define CAN_PRIORITY(CAN_MESSAGE_ID)        ((CAN_MESSAGE_ID>>7)&0x0F)

#define MAX_CAN_DATA_SIZE_BITS  64
#define MAX_CAN_DATA_SIZE_BYTES 8

class CANParser
{
public:
    virtual ~CANParser() {}

    virtual void parse(const CANMessage &msg) = 0;
};

#endif