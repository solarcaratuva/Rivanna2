#ifndef BPS_CAN_INTERFACE_H
#define BPS_CAN_INTERFACE_H

#include "BPSCANStructs.h"
#include "CANInterface.h"

class BPSCANInterface : public CANInterface {
  public:
    BPSCANInterface(PinName rd, PinName td, PinName standby_pin);
    void handle(BPSPackInformation *can_struct);
    void handle(BPSError *can_struct);
    void handle(BPSCellVoltage *can_struct);
    void handle(BPSCellTemperature *can_struct);

  private:
    void message_handler() override;
};

#endif
