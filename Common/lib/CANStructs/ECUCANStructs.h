#ifndef ECU_CAN_STRUCTS_H
#define ECU_CAN_STRUCTS_H

#include <stdio.h>
#include "CANStruct.h"
#include "CANSerializer.h"

class ECUMotorCommands : CANStruct
{
public:
    uint16_t throttle;
    uint16_t regen;
    bool reverse_en;
    bool forward_en;
    bool cruise_control_en;
    bool cruise_speed_up;
    bool cruise_speed_down;
    bool motor_on;

    ECUMotorCommands() {}
    ECUMotorCommands(uint16_t throttle, uint16_t regen, bool reverse_en, bool forward_en, bool cruise_control_en, bool cruise_speed_up, bool cruise_speed_down, bool motor_on)
        : throttle(throttle), regen(regen), reverse_en(reverse_en), forward_en(forward_en), cruise_control_en(cruise_control_en), cruise_speed_up(cruise_speed_up), cruise_speed_down(cruise_speed_down), motor_on(motor_on) {}

    SERIALIZATION_METHODS(
        (throttle, 16),
        (regen, 16),
        (reverse_en, 1),
        (forward_en, 1),
        (cruise_control_en, 1),
        (cruise_speed_up, 1),
        (cruise_speed_down, 1),
        (motor_on, 1)
    )

    static uint8_t get_node_id()
    {
        return 1;
    }

    static uint8_t get_priority()
    {
        return 1;
    }
};

class ECUPowerAuxCommands : CANStruct
{
public:
    bool hazards;
    bool brake_lights;
    bool headlights;
    bool horn;
    bool left_turn_signal;
    bool right_turn_signal;
    bool ignition;
    bool battery_contact;

    ECUPowerAuxCommands() {}
    ECUPowerAuxCommands(bool hazards, bool brake_lights, bool headlights, bool horn, bool left_turn_signal, bool right_turn_signal, bool ignition, bool battery_contact)
        : hazards(hazards), brake_lights(brake_lights), headlights(headlights), horn(horn), left_turn_signal(left_turn_signal), right_turn_signal(right_turn_signal), ignition(ignition), battery_contact(battery_contact) {}

    SERIALIZATION_METHODS(
        (hazards, 1),
        (brake_lights, 1),
        (headlights, 1),
        (horn, 1),
        (left_turn_signal, 1),
        (right_turn_signal, 1),
        (ignition, 1),
        (battery_contact, 1)
    )

    static uint8_t get_node_id()
    {
        return 1;
    }

    static uint8_t get_priority()
    {
        return 2;
    }
};

#endif