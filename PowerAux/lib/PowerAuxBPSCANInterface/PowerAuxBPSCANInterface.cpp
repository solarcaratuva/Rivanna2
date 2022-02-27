#include "PowerAuxBPSCANInterface.h"

PowerAuxBPSCANInterface::PowerAuxBPSCANInterface(PinName rd, PinName td,
                                                 PinName standby_pin)
    : CANInterface(rd, td, standby_pin) {
    can.frequency(250000);
}

void PowerAuxBPSCANInterface::rx_handler() {
    while (true) {
        CANMessage message;
        while (can.read(message)) {
            if (message.id == POWER_AUX_BPS_CAN_PackInformation) {
                PackInformation can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id == POWER_AUX_BPS_CAN_CellVoltage) {
                CellVoltage can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            }
            if (message.id == POWER_AUX_BPS_CAN_CellTemperature) {
                CellTemperature can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            }
        }
    }
}
