#include "MotorControllerCANInterface.h"
#include "Printing.h"

MotorControllerCANInterface::MotorControllerCANInterface(PinName rd, PinName td, PinName standby_pin) : CANInterface(rd, td, standby_pin) {
    can.frequency(125000);
}

void MotorControllerCANInterface::request_frames(bool frame0, bool frame1, bool frame2)
{
    CANMessage message;
    FrameRequest request(frame0, frame1, frame2);
    request.serialize(&message);
    message.id = request.get_message_ID();
    message.format = CANFormat::CANExtended;
    can.write(message);
}

void MotorControllerCANInterface::rx_handler() 
{
    while (true)
    {
        CANMessage message;
        while (can.read(message))
        {
            if (message.id == MOTOR_CONTROLLER_Frame0_MESSAGE_ID)
            {
                Frame0 can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            }
            else if (message.id == MOTOR_CONTROLLER_Frame1_MESSAGE_ID)
            {
                Frame1 can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            }
            if (message.id == MOTOR_CONTROLLER_Frame2_MESSAGE_ID)
            {
                Frame2 can_struct;
                can_struct.deserialize(&message);
                handle(&can_struct);
            }
        }
    }
}
