#ifndef ECU_CAN_STRUCTS_H
#define ECU_CAN_STRUCTS_H

#include "CANStruct.h"
#include "dbc/structs/rivanna2.h"
#include "log.h"

typedef struct ECUMotorCommands : CANStruct, rivanna2_ecu_motor_commands_t {
    void serialize(CANMessage *message) {
        rivanna2_ecu_motor_commands_pack(message->data, this,
                                         RIVANNA2_ECU_MOTOR_COMMANDS_LENGTH);
        message->len = RIVANNA2_ECU_MOTOR_COMMANDS_LENGTH;
    }

    void deserialize(CANMessage *message) {
        rivanna2_ecu_motor_commands_unpack(this, message->data,
                                           RIVANNA2_ECU_MOTOR_COMMANDS_LENGTH);
    }

    uint32_t get_message_ID() { return ECUMotorCommands_MESSAGE_ID; }

    void log(int level) {
        log_at_level(
            level,
            "ECUMotorCommands: throttle %u, regen %u, cruise_control_speed %u, "
            "cruise_control_en %u, forward_en %u, reverse_en %u, motor_on %u",
            throttle, regen, cruise_control_speed, cruise_control_en,
            forward_en, reverse_en, motor_on);
    }
} ECUMotorCommands;

typedef struct ECUPowerAuxCommands : CANStruct,
                                     rivanna2_ecu_power_aux_commands_t {
    void serialize(CANMessage *message) {
        rivanna2_ecu_power_aux_commands_pack(
            message->data, this, RIVANNA2_ECU_MOTOR_COMMANDS_LENGTH);
        message->len = RIVANNA2_ECU_MOTOR_COMMANDS_LENGTH;
    }

    void deserialize(CANMessage *message) {
        rivanna2_ecu_power_aux_commands_unpack(
            this, message->data, RIVANNA2_ECU_MOTOR_COMMANDS_LENGTH);
    }

    uint32_t get_message_ID() { return ECUPowerAuxCommands_MESSAGE_ID; }

    void log(int level) {
        log_at_level(level,
                     "ECUPowerAuxCommands: hazards %u, brake_lights %u, "
                     "headlights %u, left_turn_signal %u, right_turn_signal %u",
                     hazards, brake_lights, headlights, left_turn_signal,
                     right_turn_signal);
    }
} ECUPowerAuxCommands;

#endif