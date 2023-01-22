#include "ECUCANInterface.h"
#include "ECUCANStructs.h"
#include "ECUInputReader.h"
#include "Printing.h"
#include "log.h"
#include "pindef.h"
#include <mbed.h>
#include <rtos.h>

#define LOG_LEVEL              LOG_DEBUG
#define MAIN_LOOP_PERIOD       1s
#define MOTOR_THREAD_PERIOD    10ms
#define POWERAUX_THREAD_PERIOD 10ms

// Can Interface
ECUCANInterface vehicle_can_interface(CAN_RX, CAN_TX, CAN_STBY);

// Input Reader
ECUInputReader input_reader;

// CAN Messages
ECUMotorCommands to_motor;
ECUPowerAuxCommands to_poweraux;

// Cruise Control Logic
uint8_t current_speed;

// Message Sending Threads
Thread motor_thread;
Thread poweraux_thread;

#define HUDPUBLISHER_THREAD_PREIOD  10ms    
static UnbufferedSerial serial_port(USBTX, USBRX);

void motor_message_handler() {
    while (true) {
        // Read motor commands
        to_motor.throttle = input_reader.readThrottle();
        to_motor.regen = input_reader.readRegen();
        to_motor.forward_en = input_reader.readForwardEn();
        to_motor.reverse_en = input_reader.readReverseEn();
        to_motor.cruise_control_en = input_reader.readCruiseThrottleEn();
        to_motor.cruise_control_speed = current_speed +
                                        input_reader.readCruiseSpeedUp() -
                                        input_reader.readCruiseSpeedDown();
        to_motor.motor_on = input_reader.readMotorOn();

        // Send message
        vehicle_can_interface.send(&to_motor);

        // Sleep
        ThisThread::sleep_for(MOTOR_THREAD_PERIOD);
    }
}

void poweraux_message_handler() {
    while (true) {
        // Read poweraux commands
        to_poweraux.hazards = input_reader.readHazards();
        to_poweraux.brake_lights = input_reader.readBrakePedal();
        to_poweraux.headlights = input_reader.readRunningLights();
        to_poweraux.left_turn_signal = input_reader.readLeftTurnSignal();
        to_poweraux.right_turn_signal = input_reader.readRightTurnSignal();

        // Send message
        vehicle_can_interface.send(&to_poweraux);

        // Sleep
        ThisThread::sleep_for(POWERAUX_THREAD_PERIOD);
    }
}

// Handle methods for all the decoded mesages

/*
Questions:
1. After handling a given can_struct, should a timer or thread sleep/flags be utilized to wait before handling another message
*/
void ECUCANInterface::handle(ECUMotorCommands *can_struct) {
    serial_port.printf("ECUMotorCommands motor_on: %d", can_struct->motor_on);
    serial_port.printf("ECUMotorCommands forward_en: %d", can_struct->forward_en);
    serial_port.printf("ECUMotorCommands throttle: %d", can_struct->throttle);
    serial_port.printf("ECUMotorCommands regen: %d", can_struct->regen);
}

// incomplete
void ECUCANInterface::handle(ECUPowerAuxCommands *can_struct) {}
void ECUCANInterface::handle(PowerAuxError *can_struct) {}
void ECUCANInterface::handle(SolarCurrent *can_struct) {}
void ECUCANInterface::handle(SolarVoltage *can_struct) {}
void ECUCANInterface::handle(SolarTemp *can_struct) {}
void ECUCANInterface::handle(SolarPhoto *can_struct) {}
void ECUCANInterface::handle(MotorControllerPowerStatus *can_struct) {}
void ECUCANInterface::handle(MotorControllerDriveStatus *can_struct) {}
void ECUCANInterface::handle(MotorControllerError *can_struct) {}
void ECUCANInterface::handle(BPSPackInformation *can_struct) {}
void ECUCANInterface::handle(BPSError *can_struct) {}
void ECUCANInterface::handle(BPSCellVoltage *can_struct) {}
void ECUCANInterface::handle(BPSCellTemperature *can_struct) {}

int main() {
    log_set_level(LOG_LEVEL);
    log_debug("Start main()");

    motor_thread.start(motor_message_handler);
    poweraux_thread.start(poweraux_message_handler);

    // Set up Serial Port for Sending data
    serial_port.baud(9600);    //standard of (9600-8-N-1)
    serial_port.format(8, SerialBase::None, 1);
    while (true) {
        log_debug("Main thread loop");

        ThisThread::sleep_for(MAIN_LOOP_PERIOD);
    }
}
