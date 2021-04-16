#include "PowerAuxCANParser.h"
#include "Printing.h"

void PowerAuxCANParser::parse(const CANMessage& msg)
{
    uint8_t messagePriority = CAN_PRIORITY(msg.id);
    uint8_t messageNodeID = CAN_NODE_ID(msg.id);

    PRINT("[ID: %d] Data received: %s\r\n", msg.id, msg.data);
}