#ifndef ECU_CAN_STRUCTS_H
#define ECU_CAN_STRUCTS_H

#include "CANSerializer.h"
#include "CANStruct.h"
#include "Printing.h"
#include <stdio.h>

typedef struct ECUMotorCommands : CANStruct {
    uint8_t throttle;
    uint8_t regen;
    bool forward_en;
    bool reverse_en;
    bool cruise_control_en;
    uint8_t cruise_control_speed;
    bool motor_on;

    ECUMotorCommands() {}
    ECUMotorCommands(uint8_t throttle, uint8_t regen, bool forward_en,
                     bool reverse_en, bool cruise_control_en,
                     uint8_t cruise_control_speed, bool motor_on)
        : throttle(throttle), regen(regen), forward_en(forward_en),
          reverse_en(reverse_en), cruise_control_en(cruise_control_en),
          cruise_control_speed(cruise_control_speed), motor_on(motor_on) {}

    SERIALIZATION_METHODS((throttle, 8), (regen, 8), (forward_en, 1),
                          (reverse_en, 1), (cruise_control_en, 1),
                          (cruise_control_speed, 8), (motor_on, 1))

    uint32_t get_message_ID() { return ECUMotorCommands_MESSAGE_ID; }

    void printStruct() {
        PRINT("ECUMotorCommands\n Throttle: %u\n Regen: %u\n Forward_Enable: "
              "%d\n Reverse_Enable: %d\n, Cruise_Control_Enable: %d\n "
              "Cruise_Control_Speed %u\n Motor_On %d\n",
              throttle, regen, forward_en, reverse_en, cruise_control_en,
              cruise_control_speed, motor_on);
    }

} ECUMotorCommands;

typedef struct ECUPowerAuxCommands : CANStruct {
    bool hazards;
    bool brake_lights;
    bool headlights;
    bool left_turn_signal;
    bool right_turn_signal;

    ECUPowerAuxCommands() {}
    ECUPowerAuxCommands(bool hazards, bool brake_lights, bool headlights,
                        bool left_turn_signal, bool right_turn_signal)
        : hazards(hazards), brake_lights(brake_lights), headlights(headlights),
          left_turn_signal(left_turn_signal),
          right_turn_signal(right_turn_signal) {}

    SERIALIZATION_METHODS((hazards, 1), (brake_lights, 1), (headlights, 1),
                          (left_turn_signal, 1), (right_turn_signal, 1))

    uint32_t get_message_ID() { return ECUPowerAuxCommands_MESSAGE_ID; }

    void printStruct() {
        PRINT("ECUPOWERAUXCOMMANDS\n Hazards: %d\n Brake_Lights: %d\n "
              "Headlights: %d\n Left_Turn_Signal: %d\n Right_Turn_Signal: %d\n",
              hazards, brake_lights, headlights, left_turn_signal,
              right_turn_signal);
    }

} ECUPowerAuxCommands;

#endif