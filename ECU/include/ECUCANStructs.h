#ifndef ECU_CAN_STRUCTS_H
#define ECU_CAN_STRUCTS_H

#include <stdio.h>

typedef struct MotorMessage
{
    uint16_t throttle : 16;
    uint16_t regen : 16;
    uint8_t reverse_en : 1;
    uint8_t forward_en : 1;
    uint8_t cruise_control_en : 1;
    uint8_t cruise_speed_up : 1;
    uint8_t cruise_speed_down : 1;
    uint8_t motor_on : 1;
} MotorMessage;

typedef struct PowerAuxMessage
{
    uint8_t hazards : 1;
    uint8_t brake_pedal : 1;
    uint8_t running_lights : 1;
    uint8_t horn : 1;
    uint8_t left_turn_signal : 1;
    uint8_t right_turn_signal : 1;
    uint8_t ignition : 1;
    uint8_t battery_contact : 1;
} PowerAuxMessage;

#endif