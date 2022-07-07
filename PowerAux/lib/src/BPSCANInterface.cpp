#include "BPSCANInterface.h"
#include "Logging.h"

#define BPS_CAN_BUS_FREQ 250000

BPSCANInterface::BPSCANInterface(PinName rd, PinName td, PinName standby_pin)
    : CANInterface("BPSCANInterface", rd, td, standby_pin) {
    can.frequency(BPS_CAN_BUS_FREQ);
}

void BPSCANInterface::message_handler() {
    while (true) {
        ThisThread::flags_wait_all(0x1);
        CANMessage message;
        while (can.read(message)) {
            char message_data[17];
            CANInterface::write_CAN_message_data_to_buffer(message_data,
                                                           &message);
            log_debug(
                "%s received CAN message with ID 0x%03X Length %d Data 0x%s",
                name, message.id, message.len, message_data);

            if (message.id == BPSPackInformation_MESSAGE_ID) {
                BPSPackInformation can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id == BPSError_MESSAGE_ID) {
                BPSError can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id == BPSCellVoltage_MESSAGE_ID) {
                BPSCellVoltage can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id == BPSCellTemperature_MESSAGE_ID) {
                BPSCellTemperature can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            }
        }
    }
}
