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
    bool bps_has_fault();
    bool bps_fault_indicator_on();

  protected:
    DigitalOut discharge_en;
    DigitalOut charge_en;
    InterruptIn pack_contactor_closed;
    DigitalOut bps_fault_indicator;
    Thread error_handler_thread;
    Thread relay_controller_thread;
    Thread bps_fault_indicator_thread;
    EventFlags event_flags;
    void rise_handler();
    void fall_handler();
    void error_handler();
    void relay_controller();
    void update_bps_fault_indicator();
    bool bps_discharge_state = false;
    bool bps_charge_state = false;
    bool bps_fault = false;
};

#endif
