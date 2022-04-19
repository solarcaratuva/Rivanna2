#ifndef POWER_AUX_BPS_CAN_INTERFACE_H
#define POWER_AUX_BPS_CAN_INTERFACE_H

#include "CANInterface.h"
#include "PowerAuxBPSCANStructs.h"

class PowerAuxBPSCANInterface : public CANInterface {
  public:
    PowerAuxBPSCANInterface(PinName rd, PinName td, PinName standby_pin);
    void handle(BPSPackInformation *can_struct);
    void handle(BPSCellVoltage *can_struct);
    void handle(BPSCellTemperature *can_struct);

  private:
    void rx_handler() override;
};

#endif
