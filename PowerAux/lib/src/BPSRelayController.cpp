#include "BPSRelayController.h"
#include "Callback.h"
#include "ConditionVariable.h"
#include "EventFlags.h"
#include "ThisThread.h"
#include "log.h"

#define PACK_CONTACTOR_CLOSED  (1 << 0)
#define PACK_CONTACTOR_OPENED  (1 << 1)
#define BPS_DISCHARGE_ENABLED  (1 << 2)
#define BPS_CHARGE_ENABLED     (1 << 3)
#define BPS_DISCHARGE_DISABLED (1 << 4)
#define BPS_CHARGE_DISABLED    (1 << 5)

BPSRelayController::BPSRelayController(PinName discharge_en, PinName charge_en,
                                       PinName pack_contactor_status)
    : discharge_en(discharge_en), charge_en(charge_en),
      pack_contactor_status(pack_contactor_status) {
    relay_controller_thread.start(
        callback(this, &BPSRelayController::relay_controller));
}

void BPSRelayController::update_state(BPSPackInformation *can_struct) {
    uint32_t flags_to_set = 0;

    if (bps_discharge_state && !can_struct->discharge_relay_status) {
        flags_to_set |= BPS_DISCHARGE_DISABLED;
        log_debug("Set BPS_DISCHARGE_DISABLED flag");
    }
    if (bps_charge_state && !can_struct->charge_relay_status) {
        flags_to_set |= BPS_CHARGE_DISABLED;
        log_debug("Set BPS_CHARGE_DISABLED flag");
    }
    if (!bps_discharge_state && can_struct->discharge_relay_status) {
        flags_to_set |= BPS_DISCHARGE_ENABLED;
        log_debug("Set BPS_DISCHARGE_ENABLED flag");
    }
    if (!bps_charge_state && can_struct->charge_relay_status) {
        flags_to_set |= BPS_CHARGE_ENABLED;
        log_debug("Set BPS_CHARGE_ENABLED flag");
    }

    event_flags.set(flags_to_set);

    bps_discharge_state = can_struct->discharge_relay_status;
    bps_charge_state = can_struct->charge_relay_status;
}

void BPSRelayController::rise_handler() {
    event_flags.set(PACK_CONTACTOR_CLOSED);
}

void BPSRelayController::fall_handler() {
    event_flags.set(PACK_CONTACTOR_OPENED);
}

void BPSRelayController::relay_controller() {
    Thread enable_discharge_charge_thread;

    pack_contactor_status.rise(
        callback(this, &BPSRelayController::rise_handler));
    pack_contactor_status.fall(
        callback(this, &BPSRelayController::fall_handler));

    while (true) {
        log_debug("Waiting for event");
        event_flags.wait_any(BPS_DISCHARGE_ENABLED | BPS_CHARGE_ENABLED |
                                 PACK_CONTACTOR_OPENED |
                                 BPS_DISCHARGE_DISABLED | BPS_CHARGE_DISABLED,
                             osWaitForever, false);
        log_debug("Iteration of relay_controller with event flags 0x%X",
                  event_flags.get());

        // Disable discharge and charge if BPS disables either or pack contactor
        // opens
        if (event_flags.get() &
            (PACK_CONTACTOR_OPENED | BPS_DISCHARGE_DISABLED |
             BPS_CHARGE_DISABLED)) {
            enable_discharge_charge_thread.terminate();

            discharge_en = false;
            charge_en = false;

            if (event_flags.get() & PACK_CONTACTOR_OPENED) {
                log_error(
                    "Terminated relay_controller_thread and opened discharge "
                    "and charge relays because pack contactor opened");
            }
            if (event_flags.get() & BPS_DISCHARGE_DISABLED) {
                log_error(
                    "Terminated relay_controller_thread and opened discharge "
                    "and charge relays because BPS disabled discharge");
            }
            if (event_flags.get() & BPS_CHARGE_DISABLED) {
                log_error(
                    "Terminated relay_controller_thread and opened discharge "
                    "and charge relays because BPS disabled charge");
            }

            // Terminate thread
            break;
        }

        // Handle BPS discharge/charge enable
        if (event_flags.get() & (BPS_DISCHARGE_ENABLED | BPS_CHARGE_ENABLED)) {
            uint32_t flags = event_flags.get() &
                             (BPS_DISCHARGE_ENABLED | BPS_CHARGE_ENABLED);

            // Copy flags to secondary thread
            enable_discharge_charge_thread.flags_set(flags);

            // Create secondary thread to enable discharge and/or charge relays
            enable_discharge_charge_thread.start(
                callback(this, &BPSRelayController::enable_discharge_charge));
            log_debug("Started enable_discharge_charge_thread with flags 0x%X",
                      flags);

            event_flags.clear(flags);
        }
    }
}

void BPSRelayController::enable_discharge_charge() {
    bool discharge = ThisThread::flags_get() & BPS_DISCHARGE_ENABLED;
    bool charge = ThisThread::flags_get() & BPS_CHARGE_ENABLED;

    ThisThread::sleep_for(100ms);

    // If discharge is supposed to be enabled, enable discharge
    if (discharge) {
        discharge_en = true;
        log_debug("Enabled discharge relay");
    }

    if (charge) {
        // Wait for pack contactor to close
        log_debug("Waiting for pack contactor to close");
        if (pack_contactor_status) {
            event_flags.set(PACK_CONTACTOR_CLOSED);
        }
        event_flags.wait_all(PACK_CONTACTOR_CLOSED);
        log_debug("Pack contactor closed");

        // Wait for 5s or until the pack contactor opens
        event_flags.wait_all_for(PACK_CONTACTOR_OPENED, 5s, false);

        // If pack contactor has not opened, enable charge
        if (!(event_flags.get() & PACK_CONTACTOR_OPENED)) {
            charge_en = true;
            log_debug("Enabled charge relay");
        }
    }
}
