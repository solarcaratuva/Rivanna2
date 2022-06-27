#include "BPSRelayController.h"
#include "ThisThread.h"
#include "log.h"

#define PACK_CONTACTOR_CLOSED  (1 << 0)
#define PACK_CONTACTOR_OPENED  (1 << 1)
#define BPS_DISCHARGE_ENABLED  (1 << 2)
#define BPS_CHARGE_ENABLED     (1 << 3)
#define BPS_DISCHARGE_DISABLED (1 << 4)
#define BPS_CHARGE_DISABLED    (1 << 5)

#define DISCHARGE_RELAY_DELAY  100ms
#define CHARGE_RELAY_DELAY     5s

BPSRelayController::BPSRelayController(PinName discharge_en, PinName charge_en,
                                       PinName pack_contactor_closed)
    : discharge_en(discharge_en), charge_en(charge_en),
      pack_contactor_closed(pack_contactor_closed) {
    this->pack_contactor_closed.rise(
        callback(this, &BPSRelayController::rise_handler));
    this->pack_contactor_closed.fall(
        callback(this, &BPSRelayController::fall_handler));
    
    error_handler_thread.start(
        callback(this, &BPSRelayController::error_handler));
    relay_controller_thread.start(
        callback(this, &BPSRelayController::relay_controller));
}

void BPSRelayController::update_state(BPSPackInformation *can_struct) {
    uint32_t flags = 0;

    if (bps_discharge_state && !can_struct->discharge_relay_status) {
        flags |= BPS_DISCHARGE_DISABLED;
        log_debug("Set BPS_DISCHARGE_DISABLED flag");
    }
    if (bps_charge_state && !can_struct->charge_relay_status) {
        flags |= BPS_CHARGE_DISABLED;
        log_debug("Set BPS_CHARGE_DISABLED flag");
    }
    if (!bps_discharge_state && can_struct->discharge_relay_status) {
        flags |= BPS_DISCHARGE_ENABLED;
        log_debug("Set BPS_DISCHARGE_ENABLED flag");
    }
    if (!bps_charge_state && can_struct->charge_relay_status) {
        flags |= BPS_CHARGE_ENABLED;
        log_debug("Set BPS_CHARGE_ENABLED flag");
    }

    event_flags.set(flags);

    bps_discharge_state = can_struct->discharge_relay_status;
    bps_charge_state = can_struct->charge_relay_status;
}

void BPSRelayController::rise_handler() {
    event_flags.set(PACK_CONTACTOR_CLOSED);
}

void BPSRelayController::fall_handler() {
    event_flags.set(PACK_CONTACTOR_OPENED);
}

void BPSRelayController::error_handler() {
    error_handler_thread.set_priority(osPriorityHigh);
    log_debug("Started error_handler_thread");

    while (true) {
        log_debug("error_handler_thread waiting for event");
        uint32_t flags = event_flags.wait_any(PACK_CONTACTOR_OPENED | BPS_DISCHARGE_DISABLED | BPS_CHARGE_DISABLED);
        log_debug("Iteration of error_handler with event flags 0x%X",
                  flags);

        relay_controller_thread.terminate();

        discharge_en = false;
        charge_en = false;

        if (flags & PACK_CONTACTOR_OPENED) {
            log_error(
                "Terminated error_handler_thread and opened discharge "
                "and charge relays because pack contactor opened");
        }
        if (flags & BPS_DISCHARGE_DISABLED) {
            log_error(
                "Terminated error_handler_thread and opened discharge "
                "and charge relays because BPS disabled discharge");
        }
        if (flags & BPS_CHARGE_DISABLED) {
            log_error(
                "Terminated error_handler_thread and opened discharge "
                "and charge relays because BPS disabled charge");
        }

        // Terminate thread
        return;
    }
}

void BPSRelayController::relay_controller() {
    error_handler_thread.set_priority(osPriorityHigh);
    log_debug("Started relay_controller_thread");

    while (true) {
        log_debug("relay_controller_thread waiting for event");
        uint32_t flags = event_flags.wait_any(BPS_DISCHARGE_ENABLED | BPS_CHARGE_ENABLED);
        log_debug("Iteration of relay_controller with flags 0x%X", flags);

        bool discharge = flags & BPS_DISCHARGE_ENABLED;
        bool charge = flags & BPS_CHARGE_ENABLED;

        // If discharge is supposed to be enabled, enable discharge
        if (discharge && !discharge_en) {
            ThisThread::sleep_for(DISCHARGE_RELAY_DELAY);

            discharge_en = true;
            log_debug("Enabled discharge relay");
        }

        if (charge && !charge_en) {
            // Wait for pack contactor to close
            log_debug("Waiting for pack contactor to close");
            if (pack_contactor_closed) {
                event_flags.set(PACK_CONTACTOR_CLOSED);
            }
            event_flags.wait_all(PACK_CONTACTOR_CLOSED);
            log_debug("Pack contactor closed");

            ThisThread::sleep_for(CHARGE_RELAY_DELAY);

            charge_en = true;
            log_debug("Enabled charge relay");
        }
    }
}
