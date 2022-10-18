#include "ECUCANInterface.h"
#include "ECUCANStructs.h"
#include "ECUInputReader.h"
#include "Printing.h"
#include "log.h"
#include "pindef.h"
#include <mbed.h>
#include <rtos.h>
#include <math.h>

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

void motor_message_handler() {
    uint16_t regenRamp = 0;
    while (true) {
        // Read motor commands
        double result = pow(1, 0.4);

        // Tesla mode
        uint16_t pedalValue = input_reader.readThrottle();
        uint16_t regenValue;    
        uint16_t throttleValue;

        if (pedalValue <= 50) {
            throttleValue = 0;
            regenValue = 79.159 * pow(50-pedalValue, 0.3);
        } else if (pedalValue < 100) {
            throttleValue = 0;
            regenValue = 0;
        } else {
            throttleValue = -56.27610464*pow(156-(i-100),0.3) + 256;
            regenValue = 0;
        }
        to_motor.throttle = throttleValue;
        to_motor.regen = regenValue;
        log_error("R: %d T: %d", regenValue, throttleValue);
        
        // Tesla mode with exponential curve
        /*
        uint16_t pedalValue = input_reader.readThrottle();
        uint16_t regenValue;
        uint16_t throttleValue;

        if (pedalValue < 100) {
            throttleValue = 0;
            regenValue = (-0.0256 * pedalValue * pedalValue) + 256;
            
        } else if (pedalValue < 156) {
            throttleValue = 0;
            regenValue = 0;
        } else {
            throttleValue = (40 * (6.3 - pow((100 - (pedalValue - 156)), 0.4) )) + 4;
            regenValue = 0;
        }
        to_motor.throttle = throttleValue;
        to_motor.regen = regenValue;
        */        

        // Brake when let go
        /*
        to_motor.throttle = input_reader.readThrottle();
        if (to_motor.throttle == 0) {
            regenRamp += 10;
            if (regenRamp > 256) {
                regenRamp = 256;
            }
        } else {
            regenRamp = 0;
        }
        to_motor.regen = regenRamp;
        */

        // Normal
        /*
        to_motor.throttle = input_reader.readThrottle();
        to_motor.regen = input_reader.readRegen();
        */

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

int main() {
    log_set_level(LOG_LEVEL);
    log_debug("Start main()");

    motor_thread.start(motor_message_handler);
    poweraux_thread.start(poweraux_message_handler);

    while (true) {
        log_debug("Main thread loop");

        ThisThread::sleep_for(MAIN_LOOP_PERIOD);
    }
}
