#ifndef ECU_CAN_STRUCTS_H
#define ECU_CAN_STRUCTS_H

#include <stdio.h>
#include "CANStruct.h"
#include "CANSerializer.h"

typedef struct ECUMotorCommands : CANStruct
{
    uint16_t throttle;
    uint16_t regen;
    bool forward_en;
    bool reverse_en;
    bool cruise_control_en;
    uint8_t cruise_control_speed;
    bool motor_on;

    ECUMotorCommands() {}
    ECUMotorCommands(uint8_t throttle, uint8_t regen, bool forward_en, bool reverse_en, bool cruise_control_en, uint8_t cruise_control_speed, bool motor_on)
        : throttle(throttle), regen(regen), forward_en(forward_en), reverse_en(reverse_en), cruise_control_en(cruise_control_en), cruise_control_speed(cruise_control_speed), motor_on(motor_on) {}

    SERIALIZATION_METHODS(
        (throttle, 8),
        (regen, 8),
        (forward_en, 1),
        (reverse_en, 1),
        (cruise_control_en, 1),
        (cruise_control_speed, 8),
        (motor_on, 1)
    )

    uint32_t get_message_ID()
    {
        return ECUMotorCommands_MESSAGE_ID;
    }
} ECUMotorCommands;

typedef struct ECUPowerAuxCommands : CANStruct
{
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

    uint32_t get_message_ID()
    {
        return ECUPowerAuxCommands_MESSAGE_ID;
    }
} ECUPowerAuxCommands;

#endif