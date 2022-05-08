#include "PowerAuxBPSCANInterface.h"
#include "PowerAuxCANInterface.h"
#include "Printing.h"
#include "STMUniqueID.h"
#include "pindef.h"
#include <mbed.h>
#include <rtos.h>

#define TESTING          // only defined if using test functions
// #define DEBUG   // only define if DEBUG

#define MAIN_LOOP_PERIOD   1s
#define ERROR_CHECK_PERIOD 1s
#define FLASH_PERIOD     500ms

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
        }
        else if (flashLSignal & !flashHazards) {
            leftTurnSignal = !leftTurnSignal;
        }
        else if (flashRSignal & !flashHazards) {
             rightTurnSignal = !rightTurnSignal;
        }
        else {
            leftTurnSignal = false;
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

AnalogIn fan_tach(FanTach);
AnalogIn brake_light_current(BRAKE_LIGHT_CURRENT);
AnalogIn headlight_current(DRL_CURRENT);
AnalogIn bms_strobe_current(BMS_STROBE_CURRENT);
AnalogIn left_turn_current(LEFT_TURN_CURRENT);
AnalogIn right_turn_current(RIGHT_TURN_CURRENT);
Thread peripheral_error_thread;

void peripheral_error_handler() {
    PowerAuxError msg;
    while (true) {
        msg.bms_strobe_error =
            (bms_strobe_current.read_u16() < 1000 && bpsFaultIndicator);
        msg.brake_light_error =
            (brake_light_current.read_u16() < 1000 && brake_lights.read());
        msg.fan_error = (fan_tach.read_u16() < 1000);
        msg.headlight_error =
            (headlight_current.read_u16() < 1000 && headlights.read());
        msg.left_turn_error =
            (left_turn_current.read_u16() < 1000 && leftTurnSignal.read());
        msg.right_turn_error =
            (right_turn_current.read_u16() < 1000 && rightTurnSignal.read());
#ifdef DEBUG
        msg.print();
#endif
        if (msg.has_error()) {
            vehicle_can_interface.send(&msg);
        }
        ThisThread::sleep_for(ERROR_CHECK_PERIOD);
    }
}

int main() {
#ifdef TESTING
    PRINT("start main() \r\n");
#endif // TESTING

    signalFlashThread.start(signalFlashHandler);
    signalBPSThread.start(signalBPSStrobe);
    peripheral_error_thread.start(peripheral_error_handler);
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
    can_struct->print();
#endif
    brake_lights = can_struct->brake_lights;
    headlights = can_struct->headlights;

    flashLSignal = can_struct->left_turn_signal;
    flashRSignal = can_struct->right_turn_signal;
    flashHazards = can_struct->hazards;
}

void PowerAuxBPSCANInterface::handle(BPSPackInformation *can_struct) {
    vehicle_can_interface.send(can_struct);
#ifdef DEBUG
    can_struct->print();
#endif
    PRINT("Received BPSPackInformation struct: pack_voltage=%u\n",
          can_struct->pack_voltage);
}

void PowerAuxBPSCANInterface::handle(BPSError *can_struct) {
    vehicle_can_interface.send(can_struct);
#ifdef DEBUG
    can_struct->print();
#endif
    bpsFaultIndicator = can_struct->has_error();
}

void PowerAuxBPSCANInterface::handle(BPSCellVoltage *can_struct) {
    vehicle_can_interface.send(can_struct);
#ifdef DEBUG
    can_struct->print();
#endif
    PRINT("Received BPSCellVoltage struct: low_cell_voltage=%u\n",
          can_struct->low_cell_voltage);
}

void PowerAuxBPSCANInterface::handle(BPSCellTemperature *can_struct) {
    vehicle_can_interface.send(can_struct);
#ifdef DEBUG
    can_struct->print();
#endif
    PRINT("Received BPSCellTemperature struct: low_temperature=%u\n",
          can_struct->low_temperature);
}
