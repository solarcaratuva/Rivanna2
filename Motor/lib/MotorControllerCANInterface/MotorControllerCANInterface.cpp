#include "MotorControllerCANInterface.h"

void MotorControllerCANInterface::sendRequest()
{
    uint64_t frame_zero = 1;
    can.write(frame_zero);
}

void MotorControllerCANInterface::rx_handler() 
{
    while (true)
    {
        CANMessage message;
        while (can.read(message))
        {
            if (message.id == 0)
            {
                printf("%d", ((int) message.data & 0x3FF) / 2);
            }
        }
    }
}
