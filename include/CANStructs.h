#ifndef CANSTRUCTS_H
#define CANSTRUCTS_H

#include <mbed.h>

// define any shared structs to be sent over CAN here

// TODO: determine & change the message ID format (# of bits for node ID vs priority) 
// CAN message ID (11 bits): Node ID stored in bottom 7 bits (bits 0-6),
//                           Priority stored in next 4 bits (bits 7-10)
#define GET_CAN_MESSAGE_ID(NODE_ID, PRIORITY)   ((NODE_ID&0x7F)|((PRIORITY&0x0F)<<7))
#define GET_NODE_ID(CAN_MESSAGE_ID)             (CAN_MESSAGE_ID&0x7F)
#define GET_PRIORITY(CAN_MESSAGE_ID)            ((CAN_MESSAGE_ID>>7)&0x0F)

#define MAX_CAN_DATA_SIZE   64
#define CAN_PERIOD          10ms

// TODO: define shared CAN structs for main CAN bus

#endif // CANSTRUCTS_H