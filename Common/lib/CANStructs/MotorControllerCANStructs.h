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
        char buffer[2048] = {0};
        const char *start = "MotorControllerFrameRequest: ";
        strcat(buffer, start);
        JsonBitprotoMotorControllerFrameRequest(this, buffer + strlen(start));

        log_at_level(level, buffer);
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
        char buffer[2048] = {0};
        const char *start = "MotorControllerPowerStatus: ";
        strcat(buffer, start);
        JsonBitprotoMotorControllerPowerStatus(this, buffer + strlen(start));

        log_at_level(level, buffer);
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
        char buffer[2048] = {0};
        const char *start = "MotorControllerDriveStatus: ";
        strcat(buffer, start);
        JsonBitprotoMotorControllerDriveStatus(this, buffer + strlen(start));

        log_at_level(level, buffer);
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
        char buffer[2048] = {0};
        const char *start = "MotorControllerError: ";
        strcat(buffer, start);
        JsonBitprotoMotorControllerError(this, buffer + strlen(start));

        log_at_level(level, buffer);
    }
} MotorControllerError;

#endif
