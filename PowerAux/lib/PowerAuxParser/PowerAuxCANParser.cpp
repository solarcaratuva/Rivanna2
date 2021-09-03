#include "PowerAuxCANParser.h"
#include "Printing.h"

void PowerAuxCANParser::parse(const CANMessage& msg)
{
    uint8_t messagePriority = CAN_PRIORITY(msg.id);
    uint8_t messageNodeID = CAN_NODE_ID(msg.id);

    powerAuxExampleStruct = *(PowerAuxExampleStruct*)msg.data;

    PRINT("[ID: %d] Data received: a=%u, b=%u, c=%u, d=%d\r\n", msg.id, powerAuxExampleStruct.a, powerAuxExampleStruct.b, powerAuxExampleStruct.c, powerAuxExampleStruct.d);
}

queue<CANMessage> PowerAuxCANParser::get_messages()
{
    static int id = 0;
    
    queue<CANMessage> fifo;
    fifo.push(CANMessage(id, (char*)&powerAuxExampleStruct, sizeof(powerAuxExampleStruct)));

    PRINT("[ID: %d] Data sent: a=%u, b=%u, c=%u, d=%d\r\n", id, powerAuxExampleStruct.a, powerAuxExampleStruct.b, powerAuxExampleStruct.c, powerAuxExampleStruct.d);
    
    id++;
    if(id == 10)
        id = 0;
    
    return fifo;
}