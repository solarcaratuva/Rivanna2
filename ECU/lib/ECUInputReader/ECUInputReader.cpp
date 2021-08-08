#include "ECUInputReader.h"
#include "pindef.h"
#include <mbed.h>

DigitalIn hazards(HAZARDS);
DigitalIn left_turn_signal(LEFT_TURN_SIG);
DigitalIn right_turn_signal(RIGHT_TURN_SIG);
DigitalIn horn(HORN);
DigitalIn cruise_speed_down(CRUISE_SPEED_DOWN);
DigitalIn cruise_speed_up(CRUISE_SPEED_UP);
DigitalIn cruise_throttle_en(CRUISE_THROTTLE_EN);
DigitalIn running_lights(RUNNING_LIGHTS_EN);
DigitalIn brake_pedal(BRAKE_PEDAL);
DigitalIn motor_on(MOTOR_ON);
DigitalIn reverse_en(REVERSE_EN);
DigitalIn forward_en(FORWARD_EN);
DigitalIn battery_contact(BATTERY_CONTACT);
DigitalIn ignition(IGNITION);
AnalogIn throttle(THROTTLE);
AnalogIn regen(REGEN);

ECUInputReader::ECUInputReader() {}

bool ECUInputReader::readHazards() {
    return hazards;
}

bool ECUInputReader::readLeftTurnSignal() {
    return left_turn_signal;
}

bool ECUInputReader::readRightTurnSignal() {
    return right_turn_signal;
}

bool ECUInputReader::readHorn() {
    return horn;
}

bool ECUInputReader::readCruiseSpeedDown() {
    return cruise_speed_down;
}

bool ECUInputReader::readCruiseSpeedUp() {
    return cruise_speed_up;
}

bool ECUInputReader::readCruiseThrottleEn() {
    return cruise_throttle_en;
}

bool ECUInputReader::readRunningLights() {
    return running_lights;
}

bool ECUInputReader::readBrakePedal() {
    return brake_pedal;
}

bool ECUInputReader::readMotorOn() {
    return motor_on;
}

bool ECUInputReader::readReverseEn() {
    return reverse_en;
}

bool ECUInputReader::readBatteryContact() {
    return battery_contact;
}

bool ECUInputReader::readIgnition() {
    return ignition;
}

uint16_t ECUInputReader::readThrottle() {
    return throttle;
}

uint16_t ECUInputReader::readRegen() {
    return regen;
}