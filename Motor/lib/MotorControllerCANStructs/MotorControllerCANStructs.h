#ifndef MOTOR_CONTROLLER_CAN_STRUCTS_H
#define MOTOR_CONTROLLER_CAN_STRUCTS_H

#include "CANSerializer.h"
#include "CANStruct.h"
#include "Printing.h"

/**
 * Struct for requesting information from the motor controller.
 * Any combination of frames can be requested in one FrameRequest.
 * Defined on page 5 of the Motor CAN bus documentation.
 */
typedef struct FrameRequest : public CANStruct {
    bool frame0;
    bool frame1;
    bool frame2;

    FrameRequest() {}
    FrameRequest(bool frame0, bool frame1, bool frame2)
        : frame0(frame0), frame1(frame1), frame2(frame2) {}

    SERIALIZATION_METHODS((frame0, 1), (frame1, 1), (frame2, 1));

    uint32_t get_message_ID() {
        return MOTOR_CONTROLLER_FrameRequest_MESSAGE_ID;
    }

    void printStruct() {
        PRINT("TODO");
    }

} FrameRequest;

/**
 * Diagnostic information from the motor controller.
 * Defined on page 5 of the Motor CAN bus documentation.
 */
typedef struct Frame0 : public CANStruct {
    /**
     * 0.5V/LSB
     */
    uint16_t battery_voltage;
    /**
     * 1A/LSB
     */
    uint16_t battery_current;
    /**
     * 0: plus current
     * 1: minus current
     */
    bool battery_current_direction;
    /**
     * 1A/LSB
     */
    uint16_t motor_current;
    /**
     * 5 degrees C/LSB
     */
    uint8_t fet_temperature;
    /**
     * 1rpm/LSB
     */
    uint16_t motor_rotating_speed;
    /**
     * 0.5%/LSB
     */
    uint16_t pwm_duty;
    /**
     * 0.5 degrees/LSB
     */
    uint8_t advanced_lead_angle;

    Frame0() {}

    SERIALIZATION_METHODS((battery_voltage, 10), (battery_current, 9),
                          (battery_current_direction, 1), (motor_current, 10),
                          (fet_temperature, 5), (motor_rotating_speed, 12),
                          (pwm_duty, 10), (advanced_lead_angle, 7));

    uint32_t get_message_ID() { return MOTOR_CONTROLLER_Frame0_MESSAGE_ID; }

    void printStruct() {
        PRINT("TODO");
    }

} Frame0;

/**
 * Input information from the motor controller.
 * Defined on page 5 of the Motor CAN bus documentation.
 */
typedef struct Frame1 : public CANStruct {
    /**
     * 0: eco mode
     * 1: power mode
     */
    bool power_eco;
    /**
     * 0: current mode
     * 1: PWM mode
     */
    bool control_mode;
    /**
     * Acceleration input position (0-100%)
     * 0.5%/LSB
     */
    uint16_t acceleration_vr_position;
    /**
     * Regeneration input position (0-100%)
     * 0.5%/LSB
     */
    uint16_t regeneration_vr_position;
    uint8_t digi_sw_number;
    /**
     * 0.5A/LSB (in current mode)
     * 0.5%/LSB (in PWM mode)
     */
    uint16_t target_value;
    /**
     * 0: stop
     * 1: unused
     * 2: forward
     * 3: reverse
     */
    uint8_t motor_status;
    /**
     * 0: drive
     * 1: regen
     */
    bool drive_regen;

    Frame1() {}

    SERIALIZATION_METHODS((power_eco, 1), (control_mode, 1),
                          (acceleration_vr_position, 10),
                          (regeneration_vr_position, 10), (digi_sw_number, 4),
                          (target_value, 10), (motor_status, 2),
                          (drive_regen, 1));

    uint32_t get_message_ID() { return MOTOR_CONTROLLER_Frame1_MESSAGE_ID; }

    void printStruct() {
        PRINT("TODO");
    }

} Frame1;

/**
 * Errors from the motor controller.
 * Padding is required to match the specification defined on page 5 of the Motor
 * CAN bus documentation. NOTE: This frame has not been tested, there may be
 * transcription or padding errors.
 */
typedef struct Frame2 : public CANStruct {
  public:
    bool analog_sensor_error;
    bool motor_current_sensor_u_error;
    bool motor_current_sensor_w_error;
    bool fet_thermistor_error;
    bool padding0;
    bool battery_voltage_sensor_error;
    bool battery_current_sensor_error;
    bool battery_current_sensor_adjust_error;
    bool motor_current_sensor_adjust_error;
    bool accelerator_position_error;
    bool padding1;
    bool controller_voltage_sensor_error;
    uint8_t padding2;
    bool power_system_error;
    bool overcurrent_error;
    bool padding3;
    bool overvoltage_error;
    bool padding4;
    bool overcurrent_limit;
    uint8_t padding5;
    bool motor_system_error;
    bool motor_lock;
    bool hall_sensor_short;
    bool hall_sensor_open;
    uint8_t padding6;
    uint8_t overheat_level;

    Frame2() {}

    SERIALIZATION_METHODS(
        (analog_sensor_error, 1), (motor_current_sensor_u_error, 1),
        (motor_current_sensor_w_error, 1), (fet_thermistor_error, 1),
        (padding0, 1), (battery_voltage_sensor_error, 1),
        (battery_current_sensor_error, 1),
        (battery_current_sensor_adjust_error, 1),
        (motor_current_sensor_adjust_error, 1), (accelerator_position_error, 1),
        (padding1, 1), (controller_voltage_sensor_error, 1), (padding2, 4),
        (power_system_error, 1), (overcurrent_error, 1), (padding3, 1),
        (overvoltage_error, 1), (padding4, 1), (overcurrent_limit, 1),
        (padding5, 2), (motor_system_error, 1), (motor_lock, 1),
        (hall_sensor_short, 1), (hall_sensor_open, 1), (padding6, 4),
        (overheat_level, 2));

    uint32_t get_message_ID() { return MOTOR_CONTROLLER_Frame2_MESSAGE_ID; }

    void printStruct() {
        PRINT("TODO");
    }
    
} Frame2;

#endif
