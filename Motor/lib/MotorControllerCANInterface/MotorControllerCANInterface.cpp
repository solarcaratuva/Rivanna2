#include "MotorControllerCANInterface.h"
#include "Printing.h"

MotorControllerCANInterface::MotorControllerCANInterface(PinName rd, PinName td, PinName standby_pin) : CANInterface(rd, td, standby_pin) {
    can.frequency(125000);
}

void MotorControllerCANInterface::sendRequest()
{
    char data[1];
    data[0] = 1;
    CANMessage msg(0x08F89540, data, 1, CANType::CANData, CANFormat::CANExtended);
    PRINT("result of writing to bus: %d\n", can.write(msg));
}

void MotorControllerCANInterface::rx_handler() 
{
    while (true)
    {
        CANMessage message;
        while (can.read(message))
        {
            PRINT("Received CAN message with id = %X\n", message.id);
            if (message.id == 0x08850225)
            {
                PRINT("%d", ((int) message.data & 0x3FF) / 2);
            }
        }
    }
}
