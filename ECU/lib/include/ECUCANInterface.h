#ifndef ECU_CAN_INTERFACE_H
#define ECU_CAN_INTERFACE_H

#include "MainCANInterface.h"

class ECUCANInterface : public MainCANInterface {
  public:
    ECUCANInterface(PinName rd, PinName td, PinName standby_pin)
        : MainCANInterface(rd, td, standby_pin) {}

        void handle(ECUMotorCommands *can_struct) override;
        void handle(ECUPowerAuxCommands *can_struct) override;
        void handle(PowerAuxError *can_struct) override;
        void handle(SolarCurrent *can_struct) override;
        void handle(SolarVoltage *can_struct) override;
        void handle(SolarTemp *can_struct) override;
        void handle(SolarPhoto *can_struct) override;
        void handle(MotorControllerPowerStatus *can_struct) override;
        void handle(MotorControllerDriveStatus *can_struct) override;
        void handle(MotorControllerError *can_struct) override;
        void handle(BPSPackInformation *can_struct) override;
        void handle(BPSError *can_struct) override;
        void handle(BPSCellVoltage *can_struct) override;
        void handle(BPSCellTemperature *can_struct) override;






};

#endif
