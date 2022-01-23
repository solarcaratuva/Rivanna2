#include <mbed.h>
#include <rtos.h>
#include "pindef.h"
#include "Printing.h"
#include "PowerAuxCANInterface.h"
#include "PowerAuxBPSCANInterface.h"

#define TESTING     // only defined if using test functions
// #define DEBUGGING   // only define if debugging

#define MAIN_LOOP_PERIOD 1s
#define CAN_PERIOD 1s
#define FLASH_PERIOD 1s

PowerAuxCANInterface vehicle_can_interface(MAIN_CAN_RX, MAIN_CAN_TX, MAIN_CAN_STBY);
PowerAuxBPSCANInterface bps_can_interface(BMS_CAN1_RX, BMS_CAN1_TX, BMS_CAN1_STBY);

bool flashHazards, flashLSignal, flashRSignal;
Thread signalFlashThread;

DigitalOut breakLights(BRAKE_LIGHT_EN);
DigitalOut headlights(DRL_EN);
DigitalOut horn(HORN_EN);
DigitalOut leftTurnSignal(LEFT_TURN_EN);
DigitalOut rightTurnSignal(RIGHT_TURN_EN);

// DigitalOut ignition(IGNITION);

void signalFlashHandler() {
    if (flashHazards) {
        if (leftTurnSignal && rightTurnSignal) {
            leftTurnSignal = false;
            rightTurnSignal = false;
        } else {
            leftTurnSignal = true;
            rightTurnSignal = true;
        }
    } else {
        leftTurnSignal = false;
        rightTurnSignal = false;
    }

    if (flashLSignal) {
        if (leftTurnSignal) {
            leftTurnSignal = false;
        } else {
            leftTurnSignal = true;
        }
    } else {
        leftTurnSignal = false;
    }

    if (flashRSignal) {
        if (rightTurnSignal) {
            rightTurnSignal = false;
        } else {
            rightTurnSignal = true;
        }
    } else {
        rightTurnSignal = false;
    }

    ThisThread::sleep_for(FLASH_PERIOD);
}

int main() {
    // device.set_baud(38400);

#ifdef TESTING
    PRINT("start main() \r\n");
#endif //TESTING

    signalFlashThread.start(signalFlashHandler);

    while(1) {
        #ifdef TESTING
            PRINT("main thread loop \r\n");
        #endif //TESTING

        ThisThread::sleep_for(MAIN_LOOP_PERIOD);
    }
}

void PowerAuxCANInterface::handle(ECUPowerAuxCommands *can_struct)
{
    breakLights = can_struct->brake_lights;
    headlights = can_struct->headlights;
    horn = can_struct->horn;

    flashLSignal = can_struct->left_turn_signal;
    flashRSignal = can_struct->right_turn_signal;
    flashHazards = can_struct->hazards;

    //    igntion = can_struct->ignition;
    //    battery__contact = can_struct->battery_contact;
}

void PowerAuxBPSCANInterface::handle(PackInformation *can_struct)
{
    PRINT("Received PackInformation struct: pack_voltage=%u\n", can_struct->pack_voltage);
}

void PowerAuxBPSCANInterface::handle(CellVoltage *can_struct)
{
    PRINT("Received CellVoltage struct: low_cell_voltage=%u\n", can_struct->low_cell_voltage);
}

void PowerAuxBPSCANInterface::handle(CellTemperature *can_struct)
{
    PRINT("Received CellTemperature struct: low_temperature=%u\n", can_struct->low_temperature);
}
