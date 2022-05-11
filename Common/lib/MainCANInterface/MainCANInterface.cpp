#include "MainCANInterface.h"

MainCANInterface::MainCANInterface(PinName rd, PinName td, PinName standby_pin)
    : CANInterface(rd, td, standby_pin) {
    can.frequency(250000);
}

int MainCANInterface::send(CANStruct *can_struct) {
    CANMessage message;
    can_struct->serialize(&message);
    message.id = can_struct->get_message_ID();
    return can.write(message);
}

void MainCANInterface::rx_handler() {
    while (true) {
        CANMessage message;
        while (can.read(message)) {
            if (message.id == ECUMotorCommands_MESSAGE_ID) {
                ECUMotorCommands can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id == ECUPowerAuxCommands_MESSAGE_ID) {
                ECUPowerAuxCommands can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id == PowerAuxError_MESSAGE_ID) {
                PowerAuxError can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id == SolarCurrent_MESSAGE_ID) {
                SolarCurrent can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id == SolarTemp_MESSAGE_ID) {
                SolarTemp can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id == SolarVoltage_MESSAGE_ID) {
                SolarVoltage can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id == SolarPhoto_MESSAGE_ID) {
                SolarPhoto can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id == MotorControllerPowerStatus_MESSAGE_ID) {
                MotorControllerPowerStatus can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id == MotorControllerDriveStatus_MESSAGE_ID) {
                MotorControllerDriveStatus can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id == MotorControllerError_MESSAGE_ID) {
                MotorControllerError can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id == BPSPackInformation_MESSAGE_ID) {
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
