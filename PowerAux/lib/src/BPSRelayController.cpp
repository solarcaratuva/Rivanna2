#include "BPSRelayController.h"
#include "ThisThread.h"
#include "log.h"

#define PACK_CONTACTOR_CLOSED  (1 << 0)
#define PACK_CONTACTOR_OPENED  (1 << 1)
#define BPS_DISCHARGE_ENABLED  (1 << 2)
#define BPS_CHARGE_ENABLED     (1 << 3)
#define BPS_DISCHARGE_DISABLED (1 << 4)
#define BPS_CHARGE_DISABLED    (1 << 5)

#define FLASH_PERIOD           500ms

BPSRelayController::BPSRelayController(PinName discharge_en, PinName charge_en,
                                       PinName pack_contactor_closed,
                                       PinName bps_fault_indicator)
    : discharge_en(discharge_en), charge_en(charge_en),
      pack_contactor_closed(pack_contactor_closed),
      bps_fault_indicator(bps_fault_indicator) {
    this->pack_contactor_closed.rise(
        callback(this, &BPSRelayController::rise_handler));
    this->pack_contactor_closed.fall(
        callback(this, &BPSRelayController::fall_handler));

    error_handler_thread.start(
        callback(this, &BPSRelayController::error_handler));
    relay_controller_thread.start(
        callback(this, &BPSRelayController::relay_controller));
    bps_fault_indicator_thread.start(
        callback(this, &BPSRelayController::update_bps_fault_indicator));
}

/**
 * Update the state of the pack discharge contactor, pack charge contactor, and
 * BPS fault indicator. Since opening the pack discharge contactor causes the
 * boards to reset, we will only close contactors if the BPS sets them to 1
 * within the first 5 CAN messages. This is to ensure that the following flow
 * occurs: 0. Initial state - All contactors are closed
 *   1. BPS sets discharge and/or charge relay to 0
 *   2. update_state() opens both contactors
 *   3. PowerAux board resets
 *   4. The first five CAN messages all show that both contactors should be open
 * This is needed because the regulations require that a fault results in a
 * latching open state for both contactors.
 */
void BPSRelayController::update_state(BPSPackInformation *can_struct) {
    static int bps_pack_information_message_count = 0;

    uint32_t flags = 0;

    if (bps_discharge_state && !can_struct->discharge_relay_status) {
        flags |= BPS_DISCHARGE_DISABLED;
        log_debug("Set BPS_DISCHARGE_DISABLED flag");

        bps_fault = true;
    }
    if (bps_charge_state && !can_struct->charge_relay_status) {
        flags |= BPS_CHARGE_DISABLED;
        log_debug("Set BPS_CHARGE_DISABLED flag");

        bps_fault = true;
    }
    if (!bps_discharge_state && can_struct->discharge_relay_status) {
        if (bps_pack_information_message_count >= 5) {
            log_debug("BPS set discharge to 1 but "
                      "bps_pack_information_message_count >= 5");
        } else {
            flags |= BPS_DISCHARGE_ENABLED;
            log_debug("Set BPS_DISCHARGE_ENABLED flag");
        }
    }
    if (!bps_charge_state && can_struct->charge_relay_status &&
        bps_pack_information_message_count < 5) {
        if (bps_pack_information_message_count >= 5) {
            log_debug("BPS set charge to 1 but "
                      "bps_pack_information_message_count >= 5");
        } else {
            flags |= BPS_CHARGE_ENABLED;
            log_debug("Set BPS_CHARGE_ENABLED flag");
        }
    }

    event_flags.set(flags);

    bps_discharge_state = can_struct->discharge_relay_status;
    bps_charge_state = can_struct->charge_relay_status;

    if (bps_pack_information_message_count == 5 &&
        (!bps_discharge_state || !bps_charge_state)) {
        bps_fault = true;
    }

    if (bps_pack_information_message_count < 5) {
        bps_pack_information_message_count += 1;
    }
}

void BPSRelayController::update_state(BPSError *can_struct) {
    if (can_struct->has_error()) {
        bps_fault = true;
    }
}

bool BPSRelayController::bps_has_fault() { return bps_fault; }

bool BPSRelayController::bps_fault_indicator_on() {
    return bps_fault_indicator;
}

void BPSRelayController::rise_handler() {
    event_flags.set(PACK_CONTACTOR_CLOSED);
}

void BPSRelayController::fall_handler() {
    event_flags.set(PACK_CONTACTOR_OPENED);

    bps_fault = true;
}

void BPSRelayController::error_handler() {
    error_handler_thread.set_priority(osPriorityHigh);
    log_debug("Started error_handler_thread");

    while (true) {
        log_debug("error_handler_thread waiting for event");
        uint32_t flags =
            event_flags.wait_any(PACK_CONTACTOR_OPENED |
                                 BPS_DISCHARGE_DISABLED | BPS_CHARGE_DISABLED);
        log_debug("Iteration of error_handler with event flags 0x%X", flags);

        relay_controller_thread.terminate();

        discharge_en = false;
        charge_en = false;

        bps_fault = true;

        if (flags & PACK_CONTACTOR_OPENED) {
            log_error("Terminated error_handler_thread and opened discharge "
                      "and charge relays because pack contactor opened");
        }
        if (flags & BPS_DISCHARGE_DISABLED) {
            log_error("Terminated error_handler_thread and opened discharge "
                      "and charge relays because BPS disabled discharge");
        }
        if (flags & BPS_CHARGE_DISABLED) {
            log_error("Terminated error_handler_thread and opened discharge "
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
        uint32_t flags =
            event_flags.wait_any(BPS_DISCHARGE_ENABLED | BPS_CHARGE_ENABLED);
        log_debug("Iteration of relay_controller with flags 0x%X", flags);

        bool discharge = flags & BPS_DISCHARGE_ENABLED;
        bool charge = flags & BPS_CHARGE_ENABLED;

        log_debug("Waiting for pack contactor to close");
        if (pack_contactor_closed) {
            event_flags.set(PACK_CONTACTOR_CLOSED);
        }
        event_flags.wait_all(PACK_CONTACTOR_CLOSED);
        log_debug("Pack contactor closed");

        ThisThread::sleep_for(9s);

        if (discharge) {
            discharge_en = true;
            log_debug("Enabled discharge relay");
        }

        ThisThread::sleep_for(1s);

        if (charge) {
            charge_en = true;
            log_debug("Enabled charge relay");
        }
    }
}

void BPSRelayController::update_bps_fault_indicator() {
    while (true) {
        if (bps_fault) {
            bps_fault_indicator = !bps_fault_indicator;
        } else {
            bps_fault_indicator = false;
        }

        ThisThread::sleep_for(FLASH_PERIOD);
    }
}
