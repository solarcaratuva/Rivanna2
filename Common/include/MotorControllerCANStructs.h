#ifndef MOTOR_CONTROLLER_CAN_STRUCTS_H
#define MOTOR_CONTROLLER_CAN_STRUCTS_H

#include "CANStruct.h"
#include "dbc/structs/motor_controller.h"
#include "log.h"

/**
 * Struct for requesting information from the motor controller.
 * Any combination of frames can be requested in one FrameRequest.
 * Defined on page 5 of the Motor CAN bus documentation.
 */
typedef struct MotorControllerFrameRequest
    : CANStruct,
      motor_controller_motor_controller_frame_request_t {
    void serialize(CANMessage *message) {
        motor_controller_motor_controller_frame_request_pack(
            message->data, this,
            MOTOR_CONTROLLER_MOTOR_CONTROLLER_FRAME_REQUEST_LENGTH);
        message->len = MOTOR_CONTROLLER_MOTOR_CONTROLLER_FRAME_REQUEST_LENGTH;
    }

    void deserialize(CANMessage *message) {
        motor_controller_motor_controller_frame_request_unpack(
            this, message->data,
            MOTOR_CONTROLLER_MOTOR_CONTROLLER_FRAME_REQUEST_LENGTH);
    }

    uint32_t get_message_ID() {
        // Since we're sending this on the motor controller CAN bus, we need to
        // use the 29-bit ID
        return MotorControllerFrameRequest_AUX_BUS_MESSAGE_ID;
    }

    void log(int level) {
        log_at_level(level,
                     "MotorControllerFrameRequest: power_status_frame %u, "
                     "drive_status_frame %u, error_frame %u",
                     power_status_frame, drive_status_frame, error_frame);
    }
} MotorControllerFrameRequest;

/**
 * Diagnostic information from the motor controller.
 * Defined on page 5 of the Motor CAN bus documentation.
 */
typedef struct MotorControllerPowerStatus
    : CANStruct,
      motor_controller_motor_controller_power_status_t {
    void serialize(CANMessage *message) {
        motor_controller_motor_controller_power_status_pack(
            message->data, this,
            MOTOR_CONTROLLER_MOTOR_CONTROLLER_POWER_STATUS_LENGTH);
        message->len = MOTOR_CONTROLLER_MOTOR_CONTROLLER_POWER_STATUS_LENGTH;
    }

    void deserialize(CANMessage *message) {
        motor_controller_motor_controller_power_status_unpack(
            this, message->data,
            MOTOR_CONTROLLER_MOTOR_CONTROLLER_POWER_STATUS_LENGTH);
    }

    uint32_t get_message_ID() {
        // We only call get_message_ID for sending on the main CAN bus, so we
        // use the ID intended for the main bus
        return MotorControllerPowerStatus_MESSAGE_ID;
    }

    void log(int level) {
        log_at_level(
            level,
            "MotorControllerPowerStatus: battery_voltage %u, battery_current "
            "%u, battery_current_direction %u, motor_current %u, "
            "fet_temp %u, motor_rpm %u, pwm_duty %u, lead_angle %u",
            battery_voltage, battery_current, battery_current_direction,
            motor_current, fet_temp, motor_rpm, pwm_duty, lead_angle);
    }
} MotorControllerPowerStatus;

/**
 * Input information from the motor controller.
 * Defined on page 5 of the Motor CAN bus documentation.
 */
typedef struct MotorControllerDriveStatus
    : CANStruct,
      motor_controller_motor_controller_drive_status_t {
    void serialize(CANMessage *message) {
        motor_controller_motor_controller_drive_status_pack(
            message->data, this,
            MOTOR_CONTROLLER_MOTOR_CONTROLLER_DRIVE_STATUS_LENGTH);
        message->len = MOTOR_CONTROLLER_MOTOR_CONTROLLER_DRIVE_STATUS_LENGTH;
    }

    void deserialize(CANMessage *message) {
        motor_controller_motor_controller_drive_status_unpack(
            this, message->data,
            MOTOR_CONTROLLER_MOTOR_CONTROLLER_DRIVE_STATUS_LENGTH);
    }

    uint32_t get_message_ID() {
        // We only call get_message_ID for sending on the main CAN bus, so we
        // use the ID intended for the main bus
        return MotorControllerDriveStatus_MESSAGE_ID;
    }

    void log(int level) {
        log_at_level(level,
                     "MotorControllerDriveStatus: power_mode %u, control_mode "
                     "%u, accelerator_vr_position %u, regen_vr_position %u, "
                     "digital_sw_position %u, output_target_value %u, "
                     "motor_status %u, regen_status %u",
                     power_mode, control_mode, accelerator_vr_position,
                     regen_vr_position, digital_sw_position,
                     output_target_value, motor_status, regen_status);
    }
} MotorControllerDriveStatus;

/**
 * Errors from the motor controller.
 * Padding is required to match the specification defined on page 5 of the Motor
 * CAN bus documentation. NOTE: This frame has not been tested, there may be
 * transcription or padding errors.
 */
typedef struct MotorControllerError
    : CANStruct,
      motor_controller_motor_controller_error_t {
    void serialize(CANMessage *message) {
        motor_controller_motor_controller_error_pack(
            message->data, this,
            MOTOR_CONTROLLER_MOTOR_CONTROLLER_ERROR_LENGTH);
        message->len = MOTOR_CONTROLLER_MOTOR_CONTROLLER_ERROR_LENGTH;
    }

    void deserialize(CANMessage *message) {
        motor_controller_motor_controller_error_unpack(
            this, message->data,
            MOTOR_CONTROLLER_MOTOR_CONTROLLER_ERROR_LENGTH);
    }

    uint32_t get_message_ID() {
        // We only call get_message_ID for sending on the main CAN bus, so we
        // use the ID intended for the main bus
        return MotorControllerError_MESSAGE_ID;
    }

    void log(int level) {
        log_at_level(
            level,
            "MotorControllerError: analog_sensor_err %u, "
            "motor_current_sensor_u_err %u, motor_current_sensor_w_err %u, "
            "fet_thermistor_err %u, battery_voltage_sensor_err %u, "
            "battery_current_sensor_err %u, battery_current_sensor_adj_err %u, "
            "motor_current_sensor_adj_err %u, accelerator_position_err %u, "
            "controller_voltage_sensor_err %u, power_system_err %u, "
            "overcurrent_err %u, overvoltage_err %u, overcurrent_limit %u, "
            "motor_system_err %u, motor_lock %u, hall_sensor_short %u, "
            "hall_sensor_open %u, overheat_level %u",
            analog_sensor_err, motor_current_sensor_u_err,
            motor_current_sensor_w_err, fet_thermistor_err,
            battery_voltage_sensor_err, battery_current_sensor_err,
            battery_current_sensor_adj_err, motor_current_sensor_adj_err,
            accelerator_position_err, controller_voltage_sensor_err,
            power_system_err, overcurrent_err, overvoltage_err,
            overcurrent_limit, motor_system_err, motor_lock, hall_sensor_short,
            hall_sensor_open, overheat_level);
    }
} MotorControllerError;

#endif
