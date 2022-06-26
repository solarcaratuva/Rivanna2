#ifndef BPS_RELAY_CONTROLLER_H
#define BPS_RELAY_CONTROLLER_H

#include "BPSCANStructs.h"
#include <mbed.h>

class BPSRelayController {
  public:
    BPSRelayController(PinName discharge_en, PinName charge_en,
                       PinName pack_contactor_closed,
                       PinName bps_fault_indicator);
    void update_state(BPSPackInformation *can_struct);
    void update_state(BPSError *can_struct);
    bool bps_fault_indicator_on();

  protected:
    DigitalOut discharge_en;
    DigitalOut charge_en;
    InterruptIn pack_contactor_closed;
    Thread relay_controller_thread;
    EventFlags event_flags;
    void rise_handler();
    void fall_handler();
    void relay_controller();
    void enable_discharge_charge();
    bool bps_discharge_state = false;
    bool bps_charge_state = false;

    DigitalOut bps_fault_indicator;
    Thread bps_fault_indicator_thread;
    void update_bps_fault_indicator();
    bool bps_fault = false;
};

#endif
