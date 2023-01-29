#include "ECUCANInterface.h"
#include "ECUCANStructs.h"
#include "ECUInputReader.h"
#include "Printing.h"
#include "log.h"
#include "pindef.h"
#include <mbed.h>
#include <rtos.h>
#include <math.h>
#include <chrono>

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
uint8_t currentSpeed;

// Message Sending Threads
Thread motor_thread;
Thread poweraux_thread;

long millis() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

int pid(double p, double i, double d, double setpoint, double input, double& lasterror, double& integral, double dt) {
	double error = setpoint - input;
	integral += i * error * dt;
    double p_ = p * error;
    double i_ = integral;
    double d_ = d * (error - lasterror) / dt;
    log_debug("p: %d, i: %d, d: %d, error: %d, last_error: %d, setpoint: %d, input: %d, dt: %d",
        (int) (p_),
        (int) (i_),
        (int) (d_),
        (int) (error),
        (int) (lasterror),
        (int) (setpoint),
        (int) (input),
        (int) (dt)
    );
	lasterror = error;
	return p_ + i_ + d_;
}

void motor_message_handler() {
    uint16_t regenRamp = 0;
    double $p = 0.05, $i = 0.05, $d = 0.05, $integral = 0, $lasterror = 0;
    double lastTime = millis();
    while (true) {
        // Read motor commands
        double currentTime = millis();

        // Tesla mode
        uint16_t pedalValue = input_reader.readThrottle();
        uint16_t regenValue;    
        uint16_t throttleValue;

        log_error("RawPedalInput: pedal %d", pedalValue);

        if (pedalValue <= 50) {
            throttleValue = 0;
            regenValue = 79.159 * pow(50 - pedalValue, 0.3);
        } else if (pedalValue < 100) {
            throttleValue = 0;
            regenValue = 0;
        } else {
            bool PID_ENABLED = false;
            if (PID_ENABLED) {
                // pedal from 100 --> 256
                double targetSpeed = ((pedalValue - 100.0) / 156.0 * 255.0);
                int pidValue = pid($p, $i, $d, targetSpeed, (double) currentSpeed, $lasterror, $integral, 1); // (currentTime - lastTime) / 1000.0);
                // Clamp integral to a reasonable value
                if ($integral > 255) {
                    $integral = 255;
                } else if ($integral < -255) {
                    $integral = -255;
                }
                // Clamp between 0 and 255
                throttleValue = pidValue > 255 ? 255 : (pidValue < 0 ? 0 : pidValue);
            } else {
                throttleValue = -56.27610464 * pow(156 - (pedalValue - 100), 0.3) + 256;
            }
            regenValue = 0;
        }
        to_motor.throttle = throttleValue;
        to_motor.regen = regenValue;
        log_error("R: %d T: %d", regenValue, throttleValue);

        to_motor.forward_en = input_reader.readForwardEn();
        to_motor.reverse_en = input_reader.readReverseEn();
        to_motor.cruise_control_en = input_reader.readCruiseThrottleEn();
        to_motor.cruise_control_speed = currentSpeed +
                                        input_reader.readCruiseSpeedUp() -
                                        input_reader.readCruiseSpeedDown();
        to_motor.motor_on = input_reader.readMotorOn();

        // Send message
        vehicle_can_interface.send(&to_motor);

        lastTime = currentTime;

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

void ECUCANInterface::handle(MotorControllerPowerStatus *can_struct) {
    currentSpeed = can_struct->motor_rpm;
}
