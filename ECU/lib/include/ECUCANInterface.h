#ifndef ECU_CAN_INTERFACE_H
#define ECU_CAN_INTERFACE_H

#include "MainCANInterface.h"

class ECUCANInterface : public MainCANInterface {
  public:
    ECUCANInterface(PinName rd, PinName td, PinName standby_pin)
        : MainCANInterface(rd, td, standby_pin) {}
};

#endif
