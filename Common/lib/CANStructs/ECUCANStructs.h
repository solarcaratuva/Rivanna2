#ifndef ECU_CAN_STRUCTS_H
#define ECU_CAN_STRUCTS_H

#include "CANStruct.h"
#include "bitproto/structs/ecu_bp.h"

typedef struct ECUMotorCommands : CANStruct, BitprotoECUMotorCommands {
    void serialize(CANMessage *message) {
        EncodeBitprotoECUMotorCommands(this, message->data);
        message->len = BYTES_LENGTH_BITPROTO_ECU_MOTOR_COMMANDS;
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoECUMotorCommands(this, message->data);
    }

    uint32_t get_message_ID() { return ECUMotorCommands_MESSAGE_ID; }

    void log(int level) {
        log_at_level(level, "ECUMotorCommands\n Throttle: %u\n Regen: %u\n Forward_Enable: "
              "%d\n Reverse_Enable: %d\n, Cruise_Control_Enable: %d\n "
              "Cruise_Control_Speed %u\n Motor_On %d\n",
              throttle, regen, forward_en, reverse_en, cruise_control_en,
              cruise_control_speed, motor_on);
    }
} ECUMotorCommands;

typedef struct ECUPowerAuxCommands : CANStruct, BitprotoECUPowerAuxCommands {
    void serialize(CANMessage *message) {
        EncodeBitprotoECUPowerAuxCommands(this, message->data);
        message->len = BYTES_LENGTH_BITPROTO_ECU_POWER_AUX_COMMANDS;
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoECUPowerAuxCommands(this, message->data);
    }

    uint32_t get_message_ID() { return ECUPowerAuxCommands_MESSAGE_ID; }

    void log(int level) {
        log_at_level(level, "ECUPOWERAUXCOMMANDS\n Hazards: %d\n Brake_Lights: %d\n "
              "Headlights: %d\n Left_Turn_Signal: %d\n Right_Turn_Signal: %d\n",
              hazards, brake_lights, headlights, left_turn_signal,
              right_turn_signal);
    }
} ECUPowerAuxCommands;

#endif