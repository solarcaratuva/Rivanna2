// Code generated by bitproto. DO NOT EDIT.

#ifndef __BITPROTO__MOTOR_CONTROLLER_H__
#define __BITPROTO__MOTOR_CONTROLLER_H__ 1

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#ifndef __cplusplus
#include <stdbool.h>
#endif

#include "bitproto.h"

#if defined(__cplusplus)
extern "C" {
#endif

// Number of bytes to encode struct BitprotoMotorControllerFrameRequest
#define BYTES_LENGTH_BITPROTO_MOTOR_CONTROLLER_FRAME_REQUEST 1

struct BitprotoMotorControllerFrameRequest {
    bool power_status_frame; // 1bit
    bool drive_status_frame; // 1bit
    bool errors_frame; // 1bit
};

// Number of bytes to encode struct BitprotoMotorControllerPowerStatus
#define BYTES_LENGTH_BITPROTO_MOTOR_CONTROLLER_POWER_STATUS 8

struct BitprotoMotorControllerPowerStatus {
    uint16_t battery_voltage; // 10bit
    uint16_t battery_current; // 9bit
    bool battery_current_direction; // 1bit
    uint16_t motor_current; // 10bit
    uint8_t fet_temperature; // 5bit
    uint16_t motor_rotating_speed; // 12bit
    uint16_t pwm_duty; // 10bit
    uint8_t advanced_lead_angle; // 7bit
};

// Number of bytes to encode struct BitprotoMotorControllerDriveStatus
#define BYTES_LENGTH_BITPROTO_MOTOR_CONTROLLER_DRIVE_STATUS 5

struct BitprotoMotorControllerDriveStatus {
    bool power_eco; // 1bit
    bool control_mode; // 1bit
    uint16_t acceleration_vr_position; // 10bit
    uint16_t regeneration_vr_position; // 10bit
    uint8_t digi_sw_number; // 4bit
    uint16_t target_value; // 10bit
    uint8_t motor_status; // 2bit
    bool drive_regen; // 1bit
};

// Number of bytes to encode struct BitprotoMotorControllerError
#define BYTES_LENGTH_BITPROTO_MOTOR_CONTROLLER_ERROR 4

struct BitprotoMotorControllerError {
    bool analog_sensor_error; // 1bit
    bool motor_current_sensor_u_error; // 1bit
    bool motor_current_sensor_w_error; // 1bit
    bool fet_thermistor_error; // 1bit
    uint8_t padding0; // 1bit
    bool battery_voltage_sensor_error; // 1bit
    bool battery_current_sensor_error; // 1bit
    bool battery_current_sensor_adjust_error; // 1bit
    bool motor_current_sensor_adjust_error; // 1bit
    bool accelerator_position_error; // 1bit
    uint8_t padding1; // 1bit
    bool controller_voltage_sensor_error; // 1bit
    uint8_t padding2; // 2bit
    bool power_system_error; // 1bit
    bool overcurrent_error; // 1bit
    uint8_t padding3; // 1bit
    bool overvoltage_error; // 1bit
    uint8_t padding4; // 1bit
    bool overcurrent_limit; // 1bit
    uint8_t padding5; // 2bit
    bool motor_system_error; // 1bit
    bool motor_lock; // 1bit
    bool hall_sensor_short; // 1bit
    bool hall_sensor_open; // 1bit
    uint8_t padding6; // 4bit
    uint8_t overheat_level; // 2bit
};

// Encode struct BitprotoMotorControllerFrameRequest to given buffer s.
int EncodeBitprotoMotorControllerFrameRequest(struct BitprotoMotorControllerFrameRequest *m, unsigned char *s);
// Decode struct BitprotoMotorControllerFrameRequest from given buffer s.
int DecodeBitprotoMotorControllerFrameRequest(struct BitprotoMotorControllerFrameRequest *m, unsigned char *s);
// Format struct BitprotoMotorControllerFrameRequest to a json format string.
int JsonBitprotoMotorControllerFrameRequest(struct BitprotoMotorControllerFrameRequest *m, char *s);

// Encode struct BitprotoMotorControllerPowerStatus to given buffer s.
int EncodeBitprotoMotorControllerPowerStatus(struct BitprotoMotorControllerPowerStatus *m, unsigned char *s);
// Decode struct BitprotoMotorControllerPowerStatus from given buffer s.
int DecodeBitprotoMotorControllerPowerStatus(struct BitprotoMotorControllerPowerStatus *m, unsigned char *s);
// Format struct BitprotoMotorControllerPowerStatus to a json format string.
int JsonBitprotoMotorControllerPowerStatus(struct BitprotoMotorControllerPowerStatus *m, char *s);

// Encode struct BitprotoMotorControllerDriveStatus to given buffer s.
int EncodeBitprotoMotorControllerDriveStatus(struct BitprotoMotorControllerDriveStatus *m, unsigned char *s);
// Decode struct BitprotoMotorControllerDriveStatus from given buffer s.
int DecodeBitprotoMotorControllerDriveStatus(struct BitprotoMotorControllerDriveStatus *m, unsigned char *s);
// Format struct BitprotoMotorControllerDriveStatus to a json format string.
int JsonBitprotoMotorControllerDriveStatus(struct BitprotoMotorControllerDriveStatus *m, char *s);

// Encode struct BitprotoMotorControllerError to given buffer s.
int EncodeBitprotoMotorControllerError(struct BitprotoMotorControllerError *m, unsigned char *s);
// Decode struct BitprotoMotorControllerError from given buffer s.
int DecodeBitprotoMotorControllerError(struct BitprotoMotorControllerError *m, unsigned char *s);
// Format struct BitprotoMotorControllerError to a json format string.
int JsonBitprotoMotorControllerError(struct BitprotoMotorControllerError *m, char *s);

void BpXXXProcessBitprotoMotorControllerFrameRequest(void *data, struct BpProcessorContext *ctx);
void BpXXXJsonFormatBitprotoMotorControllerFrameRequest(void *data, struct BpJsonFormatContext *ctx);

void BpXXXProcessBitprotoMotorControllerPowerStatus(void *data, struct BpProcessorContext *ctx);
void BpXXXJsonFormatBitprotoMotorControllerPowerStatus(void *data, struct BpJsonFormatContext *ctx);

void BpXXXProcessBitprotoMotorControllerDriveStatus(void *data, struct BpProcessorContext *ctx);
void BpXXXJsonFormatBitprotoMotorControllerDriveStatus(void *data, struct BpJsonFormatContext *ctx);

void BpXXXProcessBitprotoMotorControllerError(void *data, struct BpProcessorContext *ctx);
void BpXXXJsonFormatBitprotoMotorControllerError(void *data, struct BpJsonFormatContext *ctx);

#if defined(__cplusplus)
}
#endif

#endif