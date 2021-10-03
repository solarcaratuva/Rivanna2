#ifndef ECU_CAN_STRUCTS_H
#define ECU_CAN_STRUCTS_H

#include <stdio.h>

typedef struct ECUMotorCommands
{
    uint16_t throttle;
    uint16_t regen;
    bool reverse_en;
    bool forward_en;
    bool cruise_control_en;
    bool cruise_speed_up;
    bool cruise_speed_down;
    bool motor_on;
} ECUMotorCommands;

typedef struct ECUPowerAuxCommands
{
    bool hazards;
    bool brake_lights;
    bool headlights;
    bool horn;
    bool left_turn_signal;
    bool right_turn_signal;
    bool ignition;
    bool battery_contact;
    
} ECUPowerAuxCommands;



#endif