#ifndef SOLAR_CAN_PARSER_H
#define SOLAR_CAN_PARSER_H
#include <mbed.h>

#include "CANParser.h"
#include "SolarCANStructs.h"

class SolarCANParser : public CANParser {
    public:
    void parse(const CANMessage &msg) override;
    queue<CANMessage> *get_messages() override;
    
    void push_solar_example_struct(SolarExampleStruct *example_struct);
private:
    queue<CANMessage> messages;
};


#endif