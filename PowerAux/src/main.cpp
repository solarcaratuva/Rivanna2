#include "BPSCANInterface.h"
#include "Logging.h"
#include "PowerAuxCANInterface.h"
#include "Printing.h"
#include "pindef.h"
#include <mbed.h>
#include <rtos.h>

#define LOG_LEVEL          LOG_FATAL
#define MAIN_LOOP_PERIOD   1s
#define ERROR_CHECK_PERIOD 1s
#define FLASH_PERIOD       500ms

PowerAuxCANInterface vehicle_can_interface(MAIN_CAN_RX, MAIN_CAN_TX,
                                           MAIN_CAN_STBY);
BPSCANInterface bps_can_interface(BMS_CAN1_RX, BMS_CAN1_TX, BMS_CAN1_STBY);

bool flashHazards, flashLSignal, flashRSignal = false;
Thread signalFlashThread;

DigitalOut brake_lights(BRAKE_LIGHT_EN);
DigitalOut headlights(DRL_EN);
DigitalOut leftTurnSignal(LEFT_TURN_EN);
DigitalOut rightTurnSignal(RIGHT_TURN_EN);

void signalFlashHandler() {
    while (true) {
        if (flashHazards || flashLSignal || flashRSignal) {
            if (flashHazards) {
                leftTurnSignal = !leftTurnSignal;
                rightTurnSignal = !rightTurnSignal;
            } else if (flashLSignal & !flashHazards) {
                leftTurnSignal = !leftTurnSignal;
                rightTurnSignal = false;
            } else if (flashRSignal & !flashHazards) {
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
        if (msg.has_error()) {
            vehicle_can_interface.send(&msg);
        }
        ThisThread::sleep_for(ERROR_CHECK_PERIOD);
    }
}

int main() {
    log_set_level(LOG_LEVEL);
    log_debug("Start main()");

    headlights = true;

    signalFlashThread.start(signalFlashHandler);
    signalBPSThread.start(signalBPSStrobe);
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
}

void BPSCANInterface::handle(BPSPackInformation *can_struct) {
    can_struct->log(LOG_INFO);
    vehicle_can_interface.send(can_struct);
}

void BPSCANInterface::handle(BPSError *can_struct) {
    can_struct->log(LOG_INFO);
    vehicle_can_interface.send(can_struct);
    bpsFaultIndicator = can_struct->has_error();
}

void BPSCANInterface::handle(BPSCellVoltage *can_struct) {
    can_struct->log(LOG_INFO);
    vehicle_can_interface.send(can_struct);
}

void BPSCANInterface::handle(BPSCellTemperature *can_struct) {
    can_struct->log(LOG_INFO);
    vehicle_can_interface.send(can_struct);
}
