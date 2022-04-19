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
            if (message.id == POWER_AUX_BPS_CAN_BPSPackInformation) {
                BPSPackInformation can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            } else if (message.id == POWER_AUX_BPS_CAN_BPSCellVoltage) {
                BPSCellVoltage can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            }
            if (message.id == POWER_AUX_BPS_CAN_BPSCellTemperature) {
                BPSCellTemperature can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            }
        }
    }
}
