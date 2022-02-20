#ifndef POWER_AUX_ERROR_READER_H
#define POWER_AUX_ERROR_READER_H

#include <mbed.h>

class PowerAuxErrorReader 
{
    public:
        PowerAuxErrorReader(DigitalIn& fan, DigitalIn& brake_light, DigitalIn& headlight, DigitalIn& bms_strobe, DigitalIn& left_turn, DigitalIn& right_turn);
        bool get_fan_error(void);
        bool get_brake_light_error(void);
        bool get_headlight_error(void);
        bool get_bms_strobe_error(void);
        bool get_left_turn_error(void);
        bool get_right_turn_error(void);


    private:
        DigitalIn fan_error;
        DigitalIn brake_light_error;
        DigitalIn headlight_error;
        DigitalIn bms_strobe_error;
        DigitalIn left_turn_error;
        DigitalIn right_turn_error;
};


#endif