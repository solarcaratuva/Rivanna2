#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H

#include <mbed.h>

/**
 * Abstract CAN interface. Uses an mbed::CAN object to read and write from the
 * CAN bus. Subclasses must implement message_handler.
 */
class CANInterface {
  public:
    CANInterface(const char *name, PinName rd, PinName td, PinName standby_pin = NC);

  protected:
    /**
     * Name of interface (e.g. MainCANInterface, BPSCANInterface)
     */
    const char *name;
    CAN can;
    DigitalOut standby;
    Thread message_handler_thread;
    Thread status_thread;
    /**
     * ISR method called on receipt of CAN message. Sets 0x1 flag of can_thread.
     */
    void can_isr();
    /**
     * Method to check if bus has entered passive error state or is not working
     * for another reason. Will reset bus in attempt to fix issue.
     */
    void check_bus_status();
    /**
     * Method to handle CAN messages. Should wait for 0x1 flag of can_thread
     * before reading from CAN, then deserialize and call the appropriate handle
     * method. Must be implemented by subclasses.
     */
    virtual void message_handler() = 0;
    /**
     * Writes data of CAN message to buffer.
     * A message of length 2 with byte 0 = 0x12 and byte 1 = 0x34 would result
     * in a buffer of "1234".
     * @param buffer char buffer of size (len * 2) + 1, where len = message.len
     * @param message CAN message
     */
    static void write_CAN_message_data_to_buffer(char *buffer,
                                                 CANMessage *message);
};

#endif
