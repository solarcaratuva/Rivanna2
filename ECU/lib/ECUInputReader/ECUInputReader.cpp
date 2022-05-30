#include "ECUInputReader.h"
#include "Printing.h"
#include "pindef.h"
#include <cmath>
#include <mbed.h>

DigitalIn hazards(HAZARDS);
DigitalIn left_turn_signal(LEFT_TURN_SIG);
DigitalIn right_turn_signal(RIGHT_TURN_SIG);
DigitalIn cruise_speed_down(CRUISE_SPEED_DOWN);
DigitalIn cruise_speed_up(CRUISE_SPEED_UP);
DigitalIn cruise_throttle_en(CRUISE_THROTTLE_EN);
DigitalIn running_lights(RUNNING_LIGHTS_EN);
DigitalIn brake_pedal(BRAKE_PEDAL);
DigitalIn motor_on(MOTOR_ON);
DigitalIn forward_en(FORWARD_EN);
DigitalIn reverse_en(REVERSE_EN);
DigitalIn battery_contact(BATTERY_CONTACT);
DigitalIn ignition(IGNITION);
AnalogIn throttle(THROTTLE, 5.0f);
AnalogIn regen(REGEN);

bool cruise_up_release_flag;
bool cruise_down_release_flag;

ECUInputReader::ECUInputReader() {}

bool ECUInputReader::readHazards() { return hazards; }

bool ECUInputReader::readLeftTurnSignal() { return left_turn_signal; }

bool ECUInputReader::readRightTurnSignal() { return right_turn_signal; }

bool ECUInputReader::readCruiseSpeedDown() {
    bool read_input = cruise_speed_down.read();
    if (read_input && cruise_down_release_flag) {
        return 0;
    } else if (read_input) {
        cruise_down_release_flag = 1;
        return 1;
    } else {
        cruise_down_release_flag = 0;
        return 0;
    }
}

bool ECUInputReader::readCruiseSpeedUp() {
    bool read_input = cruise_speed_up.read();
    if (read_input && cruise_up_release_flag) {
        return 0;
    } else if (read_input) {
        cruise_up_release_flag = 1;
        return 1;
    } else {
        cruise_up_release_flag = 0;
        return 0;
    }
}

bool ECUInputReader::readCruiseThrottleEn() { return cruise_throttle_en; }

bool ECUInputReader::readRunningLights() { return running_lights; }

bool ECUInputReader::readBrakePedal() { return brake_pedal; }

bool ECUInputReader::readMotorOn() { return motor_on; }

bool ECUInputReader::readForwardEn() { return forward_en; }

bool ECUInputReader::readReverseEn() { return reverse_en; }

bool ECUInputReader::readBatteryContact() { return battery_contact; }

bool ECUInputReader::readIgnition() { return ignition; }

/**
 * THROTTLE_LOW_VOLTAGE +               THROTTLE_HIGH_VOLTAGE -
 * THROTTLE_LOW_VOLTAGE_BUFFER          THROTTLE_HIGH_VOLTAGE_BUFFER
 *          ▼                                                  ▼
 * -----------------------------------------------------------------
 * ▲                                                               ▲
 * THROTTLE_LOW_VOLTAGE                        THROTTLE_HIGH_VOLTAGE
 *
 * The input from the throttle pedal ranges from around THROTTLE_LOW_VOLTAGE to
 * THROTTLE_HIGH_VOLTAGE. Note that this includes the effect of the input
 * protection circuitry, which affects the voltage from the pedal.
 *
 * We have buffer space around each extreme to account for slight variations
 * in the output of the throttle pedal.
 */
#define THROTTLE_LOW_VOLTAGE         0.66
#define THROTTLE_LOW_VOLTAGE_BUFFER  0.20
#define THROTTLE_HIGH_VOLTAGE        3.08
#define THROTTLE_HIGH_VOLTAGE_BUFFER 0.10

uint16_t ECUInputReader::readThrottle() {
    float adjusted_throttle_input =
        ((throttle.read_voltage() - THROTTLE_LOW_VOLTAGE -
          THROTTLE_LOW_VOLTAGE_BUFFER) /
         (THROTTLE_HIGH_VOLTAGE - THROTTLE_HIGH_VOLTAGE_BUFFER -
          THROTTLE_LOW_VOLTAGE - THROTTLE_LOW_VOLTAGE_BUFFER));
    if (adjusted_throttle_input <= 0.0f) {
        return 0;
    } else if (adjusted_throttle_input >= 1.0f) {
        return 256;
    } else {
        return (uint16_t)(adjusted_throttle_input * 256.0);
    }
}

uint16_t ECUInputReader::readRegen() {
    return (uint16_t)(regen.read() * 200.0);
}
