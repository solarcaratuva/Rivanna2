#include "CANInterface.h"
#include "Logging.h"

CANInterface::CANInterface(const char *name, PinName rd, PinName td,
                           PinName standby_pin)
    : name(name), can(rd, td), standby(standby_pin) {
    if (standby_pin != NC) {
        standby = 0;
    }
    message_handler_thread.start(
        callback(this, &CANInterface::message_handler));
    status_thread.start(callback(this, &CANInterface::check_bus_status));
    can.attach(callback(this, &CANInterface::can_isr), CAN::RxIrq);
}

void CANInterface::check_bus_status() {
    while (true) {
        unsigned char rderror = can.rderror();
        unsigned char tderror = can.tderror();

        // Based on my testing, the rderror value will reach 128 if the bus
        // enters the passive error state and tderror will reach a maximum of
        // 128.
        if (rderror >= 128 || tderror >= 128) {
            can.reset();
            log_error("%s reset due to RX error %d TX error %d", name, rderror,
                      tderror);
        } else {
            log_debug("%s RX error %d TX error %d", name, rderror, tderror);
        }

        ThisThread::sleep_for(500ms);
    }
}

void CANInterface::can_isr() { message_handler_thread.flags_set(0x1); }

void CANInterface::write_CAN_message_data_to_buffer(char *buffer,
                                                    CANMessage *message) {
    buffer[0] = '\0';
    for (int i = 0; i < message->len; i += 1) {
        sprintf(buffer + (i * 2), "%02X", message->data[i]);
    }
}
