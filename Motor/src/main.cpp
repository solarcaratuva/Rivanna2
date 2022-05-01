#include "MotorCANInterface.h"
#include "MotorControllerCANInterface.h"
#include "MotorInterface.h"
#include "MotorStateTracker.h"
#include "Printing.h"
#include "STMUniqueID.h"
#include "pindef.h"
#include <mbed.h>

#define TESTING          // only defined if using test functions
// #define DEBUG   // only define if debugging

#define MAIN_LOOP_PERIOD 1s

BufferedSerial device(USBTX, USBRX);

MotorCANInterface vehicle_can_interface(MAIN_CAN_RX, MAIN_CAN_TX);
MotorControllerCANInterface motor_controller_can_interface(MTR_CTRL_CAN_RX,
                                                           MTR_CTRL_CAN_TX,
                                                           MTR_CTRL_CAN_STBY);

// Motor Interface
I2C throttle(SDA_ACCEL, SCL_ACCEL);
I2C regen(SDA_REGEN, SCL_REGEN);
DigitalOut gear(FWD_REV_EN);
DigitalOut ignition(MAIN_SWITCH);

MotorInterface motor_interface(throttle, regen, gear, ignition);

// Motor State Tracker
MotorStateTracker motor_state_tracker;

int main() {
#ifdef TESTING
    PRINT("start main() \r\n");
#endif // TESTING

    while (1) {
        check_motor_board();
#ifdef TESTING
        PRINT("main thread loop \r\n");
#endif // TESTING

        ThisThread::sleep_for(MAIN_LOOP_PERIOD);
    }
}

void MotorCANInterface::handle(ECUMotorCommands *can_struct) {
    motor_interface.sendIgnition(can_struct->motor_on);
    motor_interface.sendDirection(
        can_struct->forward_en); // TODO: verify motor controller will not allow
                                 // gear change when velocity is non-zero
    motor_interface.sendThrottle(can_struct->throttle);
    motor_interface.sendRegen(can_struct->regen);
}

void MotorControllerCANInterface::handle(
    MotorControllerPowerStatus *can_struct) {
#ifdef DEBUG
    can_struct->print();
#endif
    vehicle_can_interface.send(can_struct);
    motor_state_tracker.setMotorControllerPowerStatus(*can_struct);
}

void MotorControllerCANInterface::handle(
    MotorControllerDriveStatus *can_struct) {
#ifdef DEBUG
    can_struct->print();
#endif
    vehicle_can_interface.send(can_struct);
    motor_state_tracker.setMotorControllerDriveStatus(*can_struct);
}

void MotorControllerCANInterface::handle(MotorControllerError *can_struct) {
#ifdef DEBUG
    can_struct->print();
#endif
    vehicle_can_interface.send(can_struct);
    motor_state_tracker.setMotorControllerError(*can_struct);
}

//
