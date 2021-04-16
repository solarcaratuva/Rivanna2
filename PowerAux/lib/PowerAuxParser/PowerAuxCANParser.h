#ifndef POWER_AUX_CAN_PARSER_H
#define POWER_AUX_CAN_PARSER_H

#include <mbed.h>

#include "CANParser.h"

class PowerAuxCANParser : public CANParser
{
public:
    void parse(const CANMessage& msg) override;
};

#endif