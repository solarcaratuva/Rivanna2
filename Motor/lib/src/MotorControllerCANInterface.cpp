#include "MotorControllerCANInterface.h"
#include "ThisThread.h"
#include "log.h"

MotorControllerCANInterface::MotorControllerCANInterface(PinName rd, PinName td,
                                                         PinName standby_pin)
    : CANInterface(rd, td, standby_pin) {
    can.frequency(125000);
    bus_status_thread.start(
        callback(this, &MotorControllerCANInterface::check_bus_status));
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
        log_debug("Sent MotorControllerFrameRequest CAN message with Data 0x%s",
                  message_data);
    } else {
        log_error("Failed to send MotorControllerFrameRequest CAN message with "
                  "Data 0x%s",
                  message_data);
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
            log_debug("Received CAN message with ID 0x%08X Length %d Data 0x%s "
                      "from MotorController",
                      message.id, message.len, message_data);

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

void MotorControllerCANInterface::check_bus_status() {
    while (true) {
        int rderror = can.rderror();
        int tderror = can.tderror();

        if (rderror >= 128 || tderror >= 128) {
            can.reset();
            log_warn("MotorControllerCANInterface reset due to RX error %d TX "
                     "error %d",
                     rderror, tderror);
        } else {
            log_debug("MotorControllerCANInterface RX error %d TX error %d",
                      rderror, tderror);
        }

        ThisThread::sleep_for(1s);
    }
}
