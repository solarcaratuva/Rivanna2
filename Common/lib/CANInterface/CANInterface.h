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
};

#endif