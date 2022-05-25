#ifndef MOTOR_CONTROLLER_CAN_STRUCTS_H
#define MOTOR_CONTROLLER_CAN_STRUCTS_H

#include "CANStruct.h"
#include "bitproto/structs/motor_controller_bp.h"
#include "log.h"

/**
 * Struct for requesting information from the motor controller.
 * Any combination of frames can be requested in one FrameRequest.
 * Defined on page 5 of the Motor CAN bus documentation.
 */
typedef struct MotorControllerFrameRequest
    : CANStruct,
      BitprotoMotorControllerFrameRequest {
    void serialize(CANMessage *message) {
        EncodeBitprotoMotorControllerFrameRequest(this, message->data);
        message->len = BYTES_LENGTH_BITPROTO_MOTOR_CONTROLLER_FRAME_REQUEST;
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoMotorControllerFrameRequest(this, message->data);
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
                     "%d\n errors_frame: %d\n",
                     power_status_frame, drive_status_frame, errors_frame);
    }
} MotorControllerFrameRequest;

/**
 * Diagnostic information from the motor controller.
 * Defined on page 5 of the Motor CAN bus documentation.
 */
typedef struct MotorControllerPowerStatus : CANStruct,
                                            BitprotoMotorControllerPowerStatus {
    void serialize(CANMessage *message) {
        EncodeBitprotoMotorControllerPowerStatus(this, message->data);
        message->len = BYTES_LENGTH_BITPROTO_MOTOR_CONTROLLER_POWER_STATUS;
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoMotorControllerPowerStatus(this, message->data);
    }

    uint32_t get_message_ID() {
        // We only call get_message_ID for sending on the main CAN bus, so we
        // use the ID intended for the main bus
        return MotorControllerPowerStatus_MESSAGE_ID;
    }

    void log(int level) {
        log_at_level(
            level,
            "MotorControllerPowerStatus\n battery_voltage: %u\n "
            "battery_current: %u\n "
            "battery_current_direction: %d\n motor_current: %u\n "
            "fet_temperature: %u\n motor_rotating_speed: %u\n pwm_duty: %u\n "
            "advanced_lead_angle: %u\n",
            battery_voltage, battery_current, battery_current_direction,
            motor_current, fet_temperature, motor_rotating_speed, pwm_duty,
            advanced_lead_angle);
    }
} MotorControllerPowerStatus;

/**
 * Input information from the motor controller.
 * Defined on page 5 of the Motor CAN bus documentation.
 */
typedef struct MotorControllerDriveStatus : CANStruct,
                                            BitprotoMotorControllerDriveStatus {
    void serialize(CANMessage *message) {
        EncodeBitprotoMotorControllerDriveStatus(this, message->data);
        message->len = BYTES_LENGTH_BITPROTO_MOTOR_CONTROLLER_DRIVE_STATUS;
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoMotorControllerDriveStatus(this, message->data);
    }

    uint32_t get_message_ID() {
        // We only call get_message_ID for sending on the main CAN bus, so we
        // use the ID intended for the main bus
        return MotorControllerDriveStatus_MESSAGE_ID;
    }

    void log(int level) {
        log_at_level(
            level,
            "MotorControllerDriveStatus\n power_eco: %d\n control_mode: %d\n "
            "acceleration_vr_position: %u\n regeneration_vr_position: %u\n "
            "digi_sw_number: %u\n target_value: %u\n motor_status: %u\n",
            power_eco, control_mode, acceleration_vr_position,
            regeneration_vr_position, digi_sw_number, target_value,
            motor_status, drive_regen);
    }
} MotorControllerDriveStatus;

/**
 * Errors from the motor controller.
 * Padding is required to match the specification defined on page 5 of the Motor
 * CAN bus documentation. NOTE: This frame has not been tested, there may be
 * transcription or padding errors.
 */
typedef struct MotorControllerError : CANStruct, BitprotoMotorControllerError {
    void serialize(CANMessage *message) {
        EncodeBitprotoMotorControllerError(this, message->data);
        message->len = BYTES_LENGTH_BITPROTO_MOTOR_CONTROLLER_ERROR;
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoMotorControllerError(this, message->data);
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
            "%d\n padding0: %d\n battery_voltage_sensor_error: %d\n "
            "battery_current_sensor_error: %d\n "
            "battery_current_sensor_adjust_erro: %d\n "
            "motor_current_sensor_adjust_error: %d\n "
            "accelerator_position_error: %d\n accelerator_position_error: %d\n "
            "padding1: %d\n controller_voltage_sensor_error: %d\n padding2: "
            "%u\n power_system_error: %d\n overcurrent_error: %d\n padding3: "
            "%d\n padding4: %d\n overcurrent_limit: %d\n overvoltage_error: "
            "%d\n padding5: %u\n motor_sysem_error: d%\n motor_lock: d%\n "
            "hall_sensor_short: d%\n hall_sensor_open: d%\n padding6: u%\n "
            "overheat_level: u%\n",
            analog_sensor_error, motor_current_sensor_u_error,
            motor_current_sensor_w_error, fet_thermistor_error, padding0,
            battery_voltage_sensor_error, battery_current_sensor_error,
            battery_current_sensor_adjust_error,
            motor_current_sensor_adjust_error, accelerator_position_error,
            padding1, controller_voltage_sensor_error, padding2,
            power_system_error, overcurrent_error, padding3, overvoltage_error,
            padding4, overcurrent_limit, padding5, motor_system_error,
            motor_lock, hall_sensor_short, hall_sensor_open, padding6,
            overheat_level);
    }
} MotorControllerError;

#endif
