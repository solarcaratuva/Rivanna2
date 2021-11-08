#include "CANInterface.h"

CANInterface::CANInterface(PinName rd, PinName td, PinName standby_pin) : can(rd, td), standby(standby_pin)
{
    standby = 0;
}

void CANInterface::start_CAN_transmission(void)
{
    rx_thread.start(callback(this, &CANInterface::rx_handler));
}

void CANInterface::send(CANStruct *can_struct)
{
    CANMessage message;
    can_struct->serialize(&message);
    message.id = can_struct->get_message_ID();
    can.write(message);
}

void CANInterface::rx_handler()
{
    while (true)
    {
        CANMessage message;
        while (can.read(message))
        {
            if (message.id == ECUMotorCommands_MESSAGE_ID)
            {
                ECUMotorCommands can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            }
            else if (message.id == ECUPowerAuxCommands_MESSAGE_ID)
            {
                ECUPowerAuxCommands can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            }
            else if (message.id == PowerAuxExampleStruct_MESSAGE_ID)
            {
                PowerAuxExampleStruct can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            }
            else if (message.id == SolarCurrent_MESSAGE_ID)
            {
                SolarCurrent can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            }
            else if (message.id == SolarTemp_MESSAGE_ID)
            {
                SolarTemp can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            }
            else if (message.id == SolarVoltage_MESSAGE_ID)
            {
                SolarVoltage can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            }
            else if (message.id == SolarPhoto_MESSAGE_ID)
            {
                SolarPhoto can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            }
        }
    }
}
