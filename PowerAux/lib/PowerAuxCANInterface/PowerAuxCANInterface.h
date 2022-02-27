#ifndef POWER_AUX_CAN_INTERFACE_H
#define POWER_AUX_CAN_INTERFACE_H

#include "MainCANInterface.h"

class PowerAuxCANInterface : public MainCANInterface {
  public:
    PowerAuxCANInterface(PinName rd, PinName td, PinName standby_pin)
        : MainCANInterface(rd, td, standby_pin) {}

    void handle(ECUPowerAuxCommands *can_struct) override;
};

#endif
