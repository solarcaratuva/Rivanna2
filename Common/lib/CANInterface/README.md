# `CANInterface`

## Usage

`CANInterface.h` defines an abstract CAN interface. Its constructor requires `rd` (the RX pin of the associated CAN transceiver), `td` (the TX pin), and an optional `standby_pin`.

`CANInterface` cannot be used directly; a subclass (such as `SolarCANInterface`) should be used. 

## Implementation

The `CANInterface` implementation uses an `mbed::CAN` object to read and write from the CAN bus. `CANInterface` creates `rx_thread` to constantly read from the CAN bus. This thread calls the `rx_handler` function, which is to be implemented by subclasses.
