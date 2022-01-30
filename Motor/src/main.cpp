#include <mbed.h>
#include "MotorInterface.h"
#include <rtos.h>
#include "pindef.h"
#include "Printing.h"
#include "MotorCANInterface.h"
#include "MotorControllerCANInterface.h"
#include "MotorStateTracker.h"

#define TESTING     // only defined if using test functions
// #define DEBUGGING   // only define if debugging

#define MAIN_LOOP_PERIOD 1s
#define CAN_PERIOD 1s

BufferedSerial device(USBTX, USBRX);

MotorCANInterface vehicle_can_interface(MAIN_CAN_RX, MAIN_CAN_TX);
MotorControllerCANInterface motor_controller_can_interface(MTR_CTRL_CAN_RX, MTR_CTRL_CAN_TX, MTR_CTRL_CAN_STBY);

// Motor Interface
I2C throttle(SDA_ACCEL, SCL_ACCEL);
I2C regen(SDA_REGEN, SCL_REGEN);
DigitalOut gear(FWD_REV_EN);

MotorInterface motor_interface(throttle, regen, gear);

// Motor State Tracker
MotorStateTracker motor_state_tracker;

int main() {
#ifdef TESTING
    PRINT("start main() \r\n");
#endif //TESTING

    while(1)
    {
        #ifdef TESTING
            // PRINT("main thread loop \r\n");
        #endif //TESTING
        
        PRINT("Motor State\r\n");
        PRINT("-------------------\r\n");
        PRINT("Battery Voltage: %d\r\n", motor_state_tracker.getFrame0().battery_voltage);
        PRINT("Motor Rotating Speed: %d\r\n", motor_state_tracker.getFrame0().motor_rotating_speed);
        PRINT("Power Eco: %d\r\n", motor_state_tracker.getFrame1().power_eco);
        PRINT("Motor Status: %d/r/n", motor_state_tracker.getFrame1().motor_status);
    }
}

void MotorCANInterface::handle(ECUMotorCommands *can_struct)
{
    motor_interface.sendIgnition(can_struct->motor_on);
    motor_interface.sendDirection(can_struct->forward_en); // TODO: verify motor controller will not allow gear change when velocity is non-zero
    motor_interface.sendThrottle(can_struct->throttle);
    motor_interface.sendRegen(can_struct->regen);
    PRINT("Received ECUMotorCommands: throttle=%u, regen=%u, forward_en=%d, cruise_control_en=%d, cruise_control_speed=%u, motor_on=%d\r\n", 
        can_struct->throttle, can_struct->regen, can_struct->forward_en, can_struct->cruise_control_en, can_struct->cruise_control_speed, can_struct->motor_on);    

}

void MotorControllerCANInterface::handle(Frame0 *can_struct)
{
    motor_state_tracker.setFrame0(*can_struct);
}

void MotorControllerCANInterface::handle(Frame1 *can_struct)
{
    motor_state_tracker.setFrame1(*can_struct);
}

void MotorControllerCANInterface::handle(Frame2 *can_struct)
{
    motor_state_tracker.setFrame2(*can_struct);
}
