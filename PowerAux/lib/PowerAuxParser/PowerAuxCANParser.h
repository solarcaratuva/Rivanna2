#ifndef POWER_AUX_CAN_PARSER_H
#define POWER_AUX_CAN_PARSER_H

#include <mbed.h>

#include "CANParser.h"
#include "PowerAuxCANStructs.h"

class PowerAuxCANParser : public CANParser
{
public:
    void parse(const CANMessage &msg) override;
    queue<CANMessage> *get_messages() override;

    void push_power_aux_example_struct(PowerAuxExampleStruct *example_struct);

private:
    queue<CANMessage> messages;
};

#endif