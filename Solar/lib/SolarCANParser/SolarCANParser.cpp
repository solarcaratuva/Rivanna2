#include "SolarCANParser.h"
#include "Printing.h"

void SolarCANParser::parse(const CANMessage& msg)
{
    uint8_t messagePriority = CAN_PRIORITY(msg.id);
    uint8_t messageNodeID = CAN_NODE_ID(msg.id);

    solar_example_struct = *(SolarExampleStruct*)msg.data;

    PRINT("[ID: %d] Data received: a=%u, b=%u, c=%u, d=%d\r\n", msg.id, solar_example_struct.a, solar_example_struct.b, solar_example_struct.c, solar_example_struct.d);
}

queue<CANMessage> SolarCANParser::getMessages()
{
    static int id = 0;
    
    queue<CANMessage> fifo;
    fifo.push(CANMessage(id, (char*)&solar_example_struct, sizeof(solar_example_struct)));

    PRINT("[ID: %d] Data sent: a=%u, b=%u, c=%u, d=%d\r\n", id, solar_example_struct.a, solar_example_struct.b, solar_example_struct.c, solar_example_struct.d);
    
    id++;
    if(id == 10)
        id = 0;
    
    return fifo;
}