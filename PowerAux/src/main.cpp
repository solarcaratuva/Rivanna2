#include "PowerAuxBPSCANInterface.h"
#include "PowerAuxCANInterface.h"
#include "Printing.h"
#include "STMUniqueID.h"
#include "pindef.h"
#include <mbed.h>
#include <rtos.h>

#define TESTING          // only defined if using test functions
// #define DEBUG   // only define if DEBUG

#define MAIN_LOOP_PERIOD 1s
#define CAN_PERIOD       1s
#define FLASH_PERIOD     10ms

PowerAuxCANInterface vehicle_can_interface(MAIN_CAN_RX, MAIN_CAN_TX,
                                           MAIN_CAN_STBY);
PowerAuxBPSCANInterface bps_can_interface(BMS_CAN1_RX, BMS_CAN1_TX,
                                          BMS_CAN1_STBY);

bool flashHazards, flashLSignal, flashRSignal;
Thread signalFlashThread;

DigitalOut brake_lights(BRAKE_LIGHT_EN);
DigitalOut headlights(DRL_EN);
DigitalOut leftTurnSignal(LEFT_TURN_EN);
DigitalOut rightTurnSignal(RIGHT_TURN_EN);

void signalFlashHandler() {
    while (true) {
        if (flashHazards) {
            leftTurnSignal = !leftTurnSignal;
            rightTurnSignal = !rightTurnSignal;
        } else {
            leftTurnSignal = false;
            rightTurnSignal = false;
        }

        if (flashLSignal & !flashHazards) {
            leftTurnSignal = !leftTurnSignal;
        } else {
            leftTurnSignal = false;
        }

        if (flashRSignal & !flashHazards) {
            rightTurnSignal = !rightTurnSignal;
        } else {
            rightTurnSignal = false;
        }

        ThisThread::sleep_for(FLASH_PERIOD);
    }
}

bool bpsFaultIndicator;
Thread signalBPSThread;

DigitalOut bpsLight(BMS_STROBE_EN);

void signalBPSStrobe() {
    while (true) {
        if (bpsFaultIndicator) {
            bpsLight = !bpsLight;
        } else {
            bpsLight = false;
        }

        ThisThread::sleep_for(FLASH_PERIOD);
    }
}

int main() {
#ifdef TESTING
    PRINT("start main() \r\n");
#endif // TESTING

    signalFlashThread.start(signalFlashHandler);
    signalBPSThread.start(signalBPSStrobe);

    while (1) {
        check_power_aux_board();
#ifdef TESTING
        PRINT("main thread loop \r\n");
#endif // TESTING

        ThisThread::sleep_for(MAIN_LOOP_PERIOD);
    }
}

void PowerAuxCANInterface::handle(ECUPowerAuxCommands *can_struct) {
#ifdef DEBUG
    can_struct->printStruct();
#endif
    brake_lights = can_struct->brake_lights;
    headlights = can_struct->headlights;

    flashLSignal = can_struct->left_turn_signal;
    flashRSignal = can_struct->right_turn_signal;
    flashHazards = can_struct->hazards;
}

void PowerAuxBPSCANInterface::handle(PackInformation *can_struct) {
#ifdef DEBUG
    can_struct->printStruct();
#endif
    bpsFaultIndicator = can_struct->has_error();

    PRINT("Received PackInformation struct: pack_voltage=%u\n",
          can_struct->pack_voltage);
}

void PowerAuxBPSCANInterface::handle(CellVoltage *can_struct) {
#ifdef DEBUG
    can_struct->printStruct();
#endif
    PRINT("Received CellVoltage struct: low_cell_voltage=%u\n",
          can_struct->low_cell_voltage);
}

void PowerAuxBPSCANInterface::handle(CellTemperature *can_struct) {
#ifdef DEBUG
    can_struct->printStruct();
#endif
    PRINT("Received CellTemperature struct: low_temperature=%u\n",
          can_struct->low_temperature);
}
