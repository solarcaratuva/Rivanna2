#include <mbed.h>
#include "MotorInterface.h"
#include <rtos.h>
#include "pindef.h"
#include "Printing.h"
#include "MotorCANInterface.h"
#include "MotorControllerCANInterface.h"

#define TESTING     // only defined if using test functions
// #define DEBUGGING   // only define if debugging

#define MAIN_LOOP_PERIOD 1s
#define CAN_PERIOD 1s

BufferedSerial device(USBTX, USBRX);

MotorCANInterface vehicle_can_interface(MAIN_CAN_RX, MAIN_CAN_TX);
MotorControllerCANInterface motor_controller_can_interface(MTR_CTRL_CAN_RX, MTR_CTRL_CAN_TX, MTR_CTRL_CAN_STBY);

I2C throttle(SDA_ACCEL, SCL_ACCEL);
I2C regen(SDA_REGEN, SCL_REGEN);

MotorInterface motor_interface(throttle, regen);

int main() {
#ifdef TESTING
    PRINT("start main() \r\n");
#endif //TESTING

    while(1){
        #ifdef TESTING
            // PRINT("main thread loop \r\n");
        #endif //TESTING

        // PowerAuxExampleStruct a(1, 2, 3, 4);
        // vehicle_can_interface.send(&a);

        // motor_interface.sendThrottle(256);
        // ThisThread::sleep_for(MAIN_LOOP_PERIOD);
        // motor_interface.sendThrottle(200);
        // ThisThread::sleep_for(MAIN_LOOP_PERIOD);
        // motor_interface.sendThrottle(150);
        // ThisThread::sleep_for(MAIN_LOOP_PERIOD);
        // motor_interface.sendThrottle(100);
        // ThisThread::sleep_for(MAIN_LOOP_PERIOD);
        // motor_interface.sendThrottle(50);
        // ThisThread::sleep_for(MAIN_LOOP_PERIOD);
        // motor_interface.sendThrottle(0);
        // ThisThread::sleep_for(MAIN_LOOP_PERIOD);
        // motor_interface.sendThrottle(100.0f);
        // motor_interface.sendThrottle(50.0f);
        // motor_interface.sendRegen(100.0f);
        // motor_controller_can_interface.request_frames(true, true, true);
        // ThisThread::sleep_for(10ms);

    }
}

void MotorCANInterface::handle(ECUMotorCommands *can_struct)
{
    
    PRINT("Received ECUMotorCommands: throttle=%u, regen=%u, forward_en=%d, cruise_control_en=%d, cruise_control_speed=%u, motor_on=%d\r\n", 
        can_struct->throttle, can_struct->regen, can_struct->forward_en, can_struct->cruise_control_en, can_struct->cruise_control_speed, can_struct->motor_on);

    

}

void MotorControllerCANInterface::handle(Frame0 *can_struct)
{
    // PRINT("%d\n", can_struct->advanced_lead_angle / 2);
}

void MotorControllerCANInterface::handle(Frame1 *can_struct)
{
    // PRINT("%d\n", can_struct->regeneration_vr_position);
}

void MotorControllerCANInterface::handle(Frame2 *can_struct)
{
    // PRINT("%d\n", can_struct->ad_sensor_error);
}
