#include "SolarCANParser.h"
#include "Printing.h"
#include "CANSerializer.h"

void SolarCANParser::parse(const CANMessage& msg)
{
    CANMessage message;
    uint8_t messagePriority = CAN_PRIORITY(msg.id);
    uint8_t messageNodeID = CAN_NODE_ID(msg.id);

    SolarExampleStruct powerAuxExampleStruct;
    deserialize_can_struct(&powerAuxExampleStruct, &msg);

    PRINT("[ID: %d] Data received: a=%u, b=%u, c=%u, d=%d\r\n", msg.id, powerAuxExampleStruct.a, powerAuxExampleStruct.b, powerAuxExampleStruct.c, powerAuxExampleStruct.d);
}

queue<CANMessage> *SolarCANParser::get_messages()
{
    return &messages;
}

void SolarCANParser::push_solar_example_struct(SolarExampleStruct *example_struct)
{
    static int id = 0;
    if (++id == 10) {
        id = 0;
    }

    CANMessage message;
    message.id = id;
    serialize_can_struct(&message, example_struct);

    PRINT("[ID: %d] Data queued: a=%u, b=%u, c=%u, d=%d\r\n", id, example_struct->a, example_struct->b, example_struct->c, example_struct->d);

    messages.push(message);
}
