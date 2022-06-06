#ifndef SOLAR_CAN_INTERFACE_H
#define SOLAR_CAN_INTERFACE_H

#include "MainCANInterface.h"

class SolarCANInterface : public MainCANInterface {
  public:
    SolarCANInterface(PinName rd, PinName td, PinName standby_pin)
        : MainCANInterface(rd, td, standby_pin) {}
};

#endif
