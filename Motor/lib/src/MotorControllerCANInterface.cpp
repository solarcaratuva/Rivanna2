#include "MotorControllerCANInterface.h"
#include "Logging.h"

#define MOTOR_CONTROLLER_CAN_BUS_FREQ 125000

MotorControllerCANInterface::MotorControllerCANInterface(PinName rd, PinName td,
                                                         PinName standby_pin)
    : CANInterface("MotorControllerCANInterface", rd, td, standby_pin) {
    can.frequency(MOTOR_CONTROLLER_CAN_BUS_FREQ);
}

int MotorControllerCANInterface::request_frames(bool power_status_frame,
                                                bool drive_status_frame,
                                                bool error_frame) {
    CANMessage message;
    MotorControllerFrameRequest request;
    request.power_status_frame = power_status_frame;
    request.drive_status_frame = drive_status_frame;
    request.error_frame = error_frame;
    request.serialize(&message);
    message.id = request.get_message_ID();
    message.format = CANFormat::CANExtended;
    int result = can.write(message);

    char message_data[17];
    CANInterface::write_CAN_message_data_to_buffer(message_data, &message);
    if (result == 1) {
        log_debug(
            "%s sent MotorControllerFrameRequest CAN message with Data 0x%s",
            name, message_data);
    } else {
        log_error(
            "%s failed to send MotorControllerFrameRequest CAN message with "
            "Data 0x%s",
            name, message_data);
    }

    return result;
}

void MotorControllerCANInterface::message_handler() {
    while (true) {
        ThisThread::flags_wait_all(0x1);
        CANMessage message;
        while (can.read(message)) {
            char message_data[17];
            CANInterface::write_CAN_message_data_to_buffer(message_data,
                                                           &message);
            log_debug(
                "%s Received CAN message with ID 0x%08X Length %d Data 0x%s "
                "from MotorController",
                name, message.id, message.len, message_data);

            if (message.id == MotorControllerPowerStatus_AUX_BUS_MESSAGE_ID) {
                MotorControllerPowerStatus can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id ==
                       MotorControllerDriveStatus_AUX_BUS_MESSAGE_ID) {
                MotorControllerDriveStatus can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id == MotorControllerError_AUX_BUS_MESSAGE_ID) {
                MotorControllerError can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            }
        }
    }
}
