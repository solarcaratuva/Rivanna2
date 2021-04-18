#ifndef CAN_PARSER_H
#define CAN_PARSER_H

#include <mbed.h>
#include <queue>

// CAN message ID (11 bits): Node ID stored in bottom 3 bits (bits 0-2),
//                           Priority stored in upper 8 bits (bits 3-10)
#define CAN_MESSAGE_ID(NODE_ID, PRIORITY)   ((NODE_ID&0x07)|((PRIORITY&0xFF)<<3))
#define CAN_NODE_ID(CAN_MESSAGE_ID)         (CAN_MESSAGE_ID&0x07)
#define CAN_PRIORITY(CAN_MESSAGE_ID)        ((CAN_MESSAGE_ID>>7)&0xFF)

#define MAX_CAN_DATA_SIZE_BITS  64
#define MAX_CAN_DATA_SIZE_BYTES 8

class CANParser
{
public:
    virtual ~CANParser() {}

    virtual void parse(const CANMessage &msg) = 0;

    virtual queue<CANMessage> getMessages() = 0;
};

#endif