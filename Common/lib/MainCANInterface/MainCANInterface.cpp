#include "MainCANInterface.h"

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
            } else if (message.id == PowerAuxErrorStruct_MESSAGE_ID) {
                PowerAuxErrorStruct can_struct;
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
            } else if (message.id == Frame0_MESSAGE_ID) {
                Frame0 can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id == Frame1_MESSAGE_ID) {
                Frame1 can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id == Frame2_MESSAGE_ID) {
                Frame2 can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id == PackInformation_Message_ID) {
                PackInformation can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id == CellVoltage_Message_ID) {
                CellVoltage can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id == CellTemperature_Message_ID) {
                CellTemperature can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            }
        }
    }
}
