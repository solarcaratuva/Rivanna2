#include "SolarCANParser.h"
#include "Printing.h"

void SolarCANParser::parse(const CANMessage& msg)
{
    uint8_t messagePriority = CAN_PRIORITY(msg.id);
    uint8_t messageNodeID = CAN_NODE_ID(msg.id);

    PowerAuxExampleStruct example_struct;
    example_struct.deserialize(&msg);

    PRINT("[ID: %d] Data received: a=%u, b=%u, c=%u, d=%d\r\n", msg.id, example_struct.a, example_struct.b, example_struct.c, example_struct.d);
}

queue<CANMessage> *SolarCANParser::get_messages()
{
    return &messages;
}

void SolarCANParser::push_power_aux_example_struct(PowerAuxExampleStruct *example_struct) {
    static int id = 4;

    CANMessage message;
    message.id = id;
    example_struct->serialize(&message);

    PRINT("[ID: %d] Data queued: a=%u, b=%u, c=%u, d=%d\r\n", id, example_struct->a, example_struct->b, example_struct->c, example_struct->d);

    messages.push(message);
}
