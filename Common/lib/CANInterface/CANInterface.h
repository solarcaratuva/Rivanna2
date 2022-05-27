#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H

#include <mbed.h>

/**
 * Abstract CAN interface. Uses an mbed::CAN object to read and write from the
 * CAN bus. Creates rx_thread to constantly read from the CAN bus. This thread
 * calls the rx_handler function, which is to be implemented by subclasses.
 */
class CANInterface {
  public:
    CANInterface(PinName rd, PinName td, PinName standby_pin = NC);

  protected:
    CAN can;
    DigitalOut standby;
    Thread rx_thread;
    virtual void rx_handler() = 0;
    /**
     * @brief Writes data of CAN message to buffer.
     * A message of length 2 with byte 0 = 0x12 and byte 1 = 0x34 would result
     * in a buffer of "1234".
     * @param buffer char buffer of size (len * 2) + 1, where len = message.len
     * @param message CAN message
     */
    static void write_CAN_message_data_to_buffer(char *buffer, CANMessage *message);
};

#endif
