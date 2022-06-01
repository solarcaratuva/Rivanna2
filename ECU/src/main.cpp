#include "ECUCANInterface.h"
#include "ECUCANStructs.h"
#include "ECUInputReader.h"
#include "Printing.h"
#include "STMUniqueID.h"
#include "log.h"
#include "pindef.h"
#include <mbed.h>
#include <rtos.h>

#define LOG_LEVEL              LOG_FATAL
#define MAIN_LOOP_PERIOD       1s
#define MOTOR_THREAD_PERIOD    10ms
#define POWERAUX_THREAD_PERIOD 10ms
#define WHEEL_CIRCUMFERENCE    4.9087 // feet
#define Kp                     1

// Can Interface
ECUCANInterface vehicle_can_interface(CAN_RX, CAN_TX, CAN_STBY);

// Input Reader
ECUInputReader input_reader;

// CAN Messages
ECUMotorCommands to_motor;
ECUPowerAuxCommands to_poweraux;

// Cruise Control Logic
uint8_t current_speed;
uint8_t target_speed = 0;

// Message Sending Threads
Thread motor_thread;
Thread poweraux_thread;

void motor_message_handler() {
    while (true) {
        // Read motor commands

        // Cruise Control Enabled
        if (input_reader.readCruiseThrottleEn()) {
            if (input_reader.readCruiseSpeedUp()) {
                if (target_speed == 0) {
                    target_speed = current_speed;
                } else {
                    target_speed++;
                }
            } else if (input_reader.readCruiseSpeedDown()) {
                if (target_speed == 0) {
                    target_speed = current_speed;
                } else {
                    target_speed--;
                }
            }
            PRINT("Cruise Control Target: %d mph\n", target_speed);
        } else {
            target_speed = 0;
        }
        to_motor.throttle = input_reader.readThrottle();
        to_motor.regen = input_reader.readRegen();
        to_motor.forward_en = input_reader.readForwardEn();
        to_motor.reverse_en = input_reader.readReverseEn();
        // to_motor.cruise_control_en = input_reader.readCruiseThrottleEn();
        // to_motor.cruise_control_speed = current_speed +
        //                                 input_reader.readCruiseSpeedUp() -
        //                                 input_reader.readCruiseSpeedDown();
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

int main() {
    log_set_level(LOG_LEVEL);
    log_debug("Start main()");

    motor_thread.start(motor_message_handler);
    poweraux_thread.start(poweraux_message_handler);

    while (true) {
        check_ecu_board();
        log_debug("Main thread loop");

        ThisThread::sleep_for(MAIN_LOOP_PERIOD);
    }
}

void ECUCANInterface::handle(MotorControllerPowerStatus *can_struct) {
    can_struct->log(LOG_INFO);
    current_speed = can_struct->motor_speed * WHEEL_CIRCUMFERENCE * 60 / 5280;
    PRINT("Current Speed: %d mph\n", current_speed);
}
