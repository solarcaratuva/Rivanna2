#include "BPSCANInterface.h"
#include "BPSRelayController.h"
#include "DigitalOut.h"
#include "PowerAuxCANInterface.h"
#include "Printing.h"
#include "ThisThread.h"
#include "log.h"
#include "pindef.h"
#include <mbed.h>
#include <rtos.h>

#define LOG_LEVEL          LOG_DEBUG
#define MAIN_LOOP_PERIOD   1s
#define ERROR_CHECK_PERIOD 100ms
#define FLASH_PERIOD       500ms

PowerAuxCANInterface vehicle_can_interface(MAIN_CAN_RX, MAIN_CAN_TX,
                                           MAIN_CAN_STBY);
BPSCANInterface bps_can_interface(BMS_CAN1_RX, BMS_CAN1_TX, BMS_CAN1_STBY);

bool flashHazards, flashLSignal, flashRSignal = false;
Thread signalFlashThread;

DigitalOut brake_lights(BRAKE_LIGHT_EN);
DigitalOut leftTurnSignal(LEFT_TURN_EN);
DigitalOut rightTurnSignal(RIGHT_TURN_EN);

void signalFlashHandler() {
    while (true) {
        if (flashHazards || flashLSignal || flashRSignal) {
            if (flashHazards) {
                bool leftTurnSignalState = leftTurnSignal;
                leftTurnSignal = !leftTurnSignalState;
                rightTurnSignal = !leftTurnSignalState;
            } else if (flashLSignal) {
                leftTurnSignal = !leftTurnSignal;
                rightTurnSignal = false;
            } else if (flashRSignal) {
                rightTurnSignal = !rightTurnSignal;
                leftTurnSignal = false;
            } else {
                leftTurnSignal = false;
                rightTurnSignal = false;
            }

            ThisThread::sleep_for(FLASH_PERIOD);
        } else {
            leftTurnSignal = false;
            rightTurnSignal = false;
        }
        ThisThread::flags_wait_all(0x1);
    }
}

AnalogIn fan_tach(FanTach);
AnalogIn brake_light_current(BRAKE_LIGHT_CURRENT);
AnalogIn headlight_current(DRL_CURRENT);
AnalogIn bms_strobe_current(BMS_STROBE_CURRENT);
AnalogIn left_turn_current(LEFT_TURN_CURRENT);
AnalogIn right_turn_current(RIGHT_TURN_CURRENT);
Thread peripheral_error_thread;

BPSRelayController bps_relay_controller(HORN_EN, DRL_EN, AUX_PLUS,
                                        BMS_STROBE_EN);

void peripheral_error_handler() {
    PowerAuxError msg;
    while (true) {
        msg.bps_strobe_error = (bms_strobe_current.read_u16() < 1000 &&
                                bps_relay_controller.bps_fault_indicator_on());
        msg.brake_light_error =
            (brake_light_current.read_u16() < 1000 && brake_lights.read());
        msg.fan_error = (fan_tach.read_u16() < 1000);
        msg.left_turn_error =
            (left_turn_current.read_u16() < 1000 && leftTurnSignal.read());
        msg.right_turn_error =
            (right_turn_current.read_u16() < 1000 && rightTurnSignal.read());
        msg.bps_error = bps_relay_controller.bps_has_fault();

        vehicle_can_interface.send(&msg);
        ThisThread::sleep_for(ERROR_CHECK_PERIOD);
    }
}

int main() {
    log_set_level(LOG_LEVEL);
    log_debug("Start main()");

    signalFlashThread.start(signalFlashHandler);
    peripheral_error_thread.start(peripheral_error_handler);

    while (true) {
        log_debug("Main thread loop");

        ThisThread::sleep_for(MAIN_LOOP_PERIOD);
    }
}

void PowerAuxCANInterface::handle(ECUPowerAuxCommands *can_struct) {
    can_struct->log(LOG_INFO);

    brake_lights = can_struct->brake_lights;

    flashLSignal = can_struct->left_turn_signal;
    flashRSignal = can_struct->right_turn_signal;
    flashHazards = can_struct->hazards;

    signalFlashThread.flags_set(0x1);
}

void BPSCANInterface::handle(BPSPackInformation *can_struct) {
    can_struct->log(LOG_INFO);

    bps_relay_controller.update_state(can_struct);

    vehicle_can_interface.send(can_struct);
}

void BPSCANInterface::handle(BPSError *can_struct) {
    can_struct->log(LOG_INFO);

    bps_relay_controller.update_state(can_struct);

    vehicle_can_interface.send(can_struct);
}

void BPSCANInterface::handle(BPSCellVoltage *can_struct) {
    can_struct->log(LOG_INFO);

    vehicle_can_interface.send(can_struct);
}

void BPSCANInterface::handle(BPSCellTemperature *can_struct) {
    can_struct->log(LOG_INFO);

    vehicle_can_interface.send(can_struct);
}
