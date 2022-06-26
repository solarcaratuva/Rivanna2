#ifndef BPS_RELAY_CONTROLLER_H
#define BPS_RELAY_CONTROLLER_H

#include "BPSCANStructs.h"
#include <mbed.h>

class BPSRelayController {
  public:
    BPSRelayController(PinName discharge_en, PinName charge_en,
                       PinName pack_contactor_closed);
    void update_state(BPSPackInformation *can_struct);

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
};

#endif
