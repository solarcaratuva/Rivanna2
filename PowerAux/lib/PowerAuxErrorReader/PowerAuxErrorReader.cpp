#include "PowerAuxErrorReader.h"

PowerAuxErrorReader::PowerAuxErrorReader(DigitalIn& fan, DigitalIn& brake_light, DigitalIn& headlight, DigitalIn& bms_strobe, DigitalIn& left_turn, DigitalIn& right_turn) :
    fan_error(fan),
    brake_light_error(brake_light),
    headlight_error(headlight),
    bms_strobe_error(bms_strobe),
    left_turn_error(left_turn),
    right_turn_error(right_turn)
{}

bool PowerAuxErrorReader::get_fan_error(void)
{
    return fan_error.read();
}

bool PowerAuxErrorReader::get_brake_light_error(void)
{
    return brake_light_error.read();
}

bool PowerAuxErrorReader::get_headlight_error(void)
{
    return headlight_error.read();
}

bool PowerAuxErrorReader::get_bms_strobe_error(void)
{
    return bms_strobe_error.read();
}

bool PowerAuxErrorReader::get_left_turn_error(void)
{
    return left_turn_error.read();
}

bool PowerAuxErrorReader::get_right_turn_error(void)
{
    return right_turn_error.read();
}