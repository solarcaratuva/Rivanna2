#include "ECUParser.h"
#include "Printing.h"

void ECUParser::parse(const CANMessage& msg)
{
    uint8_t messagePriority = CAN_PRIORITY(msg.id);
    uint8_t messageNodeID = CAN_NODE_ID(msg.id);

    PowerAuxExampleStruct example_struct;
    example_struct.deserialize(msg.data, msg.len);

    PRINT("[ID: %d] Data received: a=%u, b=%u, c=%u, d=%d\r\n", msg.id, example_struct.a, example_struct.b, example_struct.c, example_struct.d);
}

queue<CANMessage> *ECUParser::get_messages()
{
    return &messages;
}

void ECUParser::push_power_aux_example_struct(PowerAuxExampleStruct *example_struct) {
    static int id = 1;

    CANMessage message;
    message.id = id;
    example_struct->serialize(message.data, &(message.len));

    PRINT("[ID: %d] Data queued: a=%u, b=%u, c=%u, d=%d\r\n", id, example_struct->a, example_struct->b, example_struct->c, example_struct->d);

    messages.push(message);
}
