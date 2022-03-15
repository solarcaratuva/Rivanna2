#ifndef MOTOR_CONTROLLER_CAN_STRUCTS_H
#define MOTOR_CONTROLLER_CAN_STRUCTS_H

#include "CANStruct.h"
#include "Printing.h"
#include "bitproto/structs/motor_controller_bp.h"

/**
 * Struct for requesting information from the motor controller.
 * Any combination of frames can be requested in one FrameRequest.
 * Defined on page 5 of the Motor CAN bus documentation.
 */
typedef struct MotorControllerFrameRequest : CANStruct, BitprotoMotorControllerFrameRequest {
    void serialize(CANMessage *message) {
        EncodeBitprotoMotorControllerFrameRequest(this, message->data);
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoMotorControllerFrameRequest(this, message->data);
    }

    uint32_t get_message_ID() { return MOTOR_CONTROLLER_FrameRequest_MESSAGE_ID; }

    void print() {
        PRINT("FrameRequest\n frame0: %d\n frame1: %d\n frame2: %d\n", frame0,
              frame1, frame2);
    }
} MotorControllerFrameRequest;

/**
 * Diagnostic information from the motor controller.
 * Defined on page 5 of the Motor CAN bus documentation.
 */
typedef struct MotorControllerFrame0 : CANStruct, BitprotoMotorControllerFrame0 {
    void serialize(CANMessage *message) {
        EncodeBitprotoMotorControllerFrame0(this, message->data);
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoMotorControllerFrame0(this, message->data);
    }

    uint32_t get_message_ID() { return Frame0_MESSAGE_ID; }
    
    void print() {
        PRINT("Frame0\n battery_voltage: %u\n battery_current: %u\n "
              "battery_current_direction: %d\n motor_current: %u\n "
              "fet_temperature: %u\n motor_rotating_speed: %u\n pwm_duty: %u\n "
              "advanced_lead_angle: %u\n",
              battery_voltage, battery_current, battery_current_direction,
              motor_current, fet_temperature, motor_rotating_speed, pwm_duty,
              advanced_lead_angle);
    }
} Frame0;

/**
 * Input information from the motor controller.
 * Defined on page 5 of the Motor CAN bus documentation.
 */
typedef struct Frame1 : CANStruct, BitprotoMotorControllerFrame1 {
    void serialize(CANMessage *message) {
        EncodeBitprotoMotorControllerFrame1(this, message->data);
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoMotorControllerFrame1(this, message->data);
    }

    uint32_t get_message_ID() { return Frame1_MESSAGE_ID; }

    void print() {
        PRINT("Frame1\n power_eco: %d\n control_mode: %d\n "
              "acceleration_vr_position: %u\n regeneration_vr_position: %u\n "
              "digi_sw_number: %u\n target_value: %u\n motor_status: %u\n",
              power_eco, control_mode, acceleration_vr_position,
              regeneration_vr_position, digi_sw_number, target_value,
              motor_status, drive_regen);
    }
} Frame1;

/**
 * Errors from the motor controller.
 * Padding is required to match the specification defined on page 5 of the Motor
 * CAN bus documentation. NOTE: This frame has not been tested, there may be
 * transcription or padding errors.
 */
typedef struct Frame2 : CANStruct, BitprotoMotorControllerFrame2 {
    void serialize(CANMessage *message) {
        EncodeBitprotoMotorControllerFrame2(this, message->data);
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoMotorControllerFrame2(this, message->data);
    }

    uint32_t get_message_ID() { return Frame2_MESSAGE_ID; }

    void print() {
        PRINT(
            "Frame2\n analog_sensor_error: %d\n motor_current_sensor_u_error: "
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
} Frame2;

#endif
