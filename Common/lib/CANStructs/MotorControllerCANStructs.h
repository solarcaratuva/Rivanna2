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
                     "MotorControllerFrameRequest\n power_status_frame: %d\n "
                     "drive_status_frame: "
                     "%d\n error_frame: %d\n",
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
        log_at_level(level,
                     "MotorControllerPowerStatus\n battery_voltage: %u\n "
                     "battery_current: %u\n "
                     "battery_current_direction: %d\n motor_current: %u\n "
                     "fet_temperature: %u\n motor_speed: %u\n pwm_duty: %u\n "
                     "lead_angle: %u\n",
                     battery_voltage, battery_current,
                     battery_current_direction, motor_current, fet_temperature,
                     motor_speed, pwm_duty, lead_angle);
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
        log_at_level(
            level,
            "MotorControllerDriveStatus\n power_mode: %d\n control_mode: %d\n "
            "accelerator_vr_position: %u\n regen_vr_position: %u\n "
            "digital_sw_position: %u\n output_target_value: %u\n "
            "drive_action_status: %u\n"
            "regen_status: %d\n",
            power_mode, control_mode, accelerator_vr_position,
            regen_vr_position, digital_sw_position, output_target_value,
            drive_action_status, regen_status);
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
            "MotorControllerError\n analog_sensor_error: %d\n "
            "motor_current_sensor_u_error: "
            "%d\n motor_current_sensor_w_error: %d\n fet_thermistor_error: "
            "%d\n battery_voltage_sensor_error: %d\n "
            "battery_current_sensor_error: %d\n "
            "battery_current_sensor_err: %d\n "
            "battery_current_sensor_adj_err: %d\n "
            "accelerator_position_error: %d\n accelerator_position_error: %d\n "
            "controller_voltage_sensor_error: "
            "%u\n power_system_error: %d\n overcurrent_error: "
            "%d\n overcurrent_limit: %d\n overvoltage_error: "
            "%d\n motor_sysem_error: d%\n motor_lock: d%\n "
            "hall_sensor_short: d%\n hall_sensor_open: d%\n"
            "overheat_level: u%\n",
            analog_sensor_err, motor_current_sensor_u_err,
            motor_current_sensor_w_err, fet_thermistor_err,
            battery_voltage_sensor_err, battery_current_sensor_err,
            battery_current_sensor_err, battery_current_sensor_adj_err,
            accelerator_position_err, controller_voltage_sensor_err,
            power_system_err, overcurrent_err, overvoltage_err,
            overcurrent_limit, motor_system_err, motor_lock, hall_sensor_short,
            hall_sensor_open, overheat_level);
    }
} MotorControllerError;

#endif
