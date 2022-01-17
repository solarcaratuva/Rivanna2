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

bool cruise_up_release_flag;
bool cruise_down_release_flag;

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
    bool read_input = cruise_speed_down.read();
    if (read_input && cruise_down_release_flag)
    {
        return 0;
    }
    else if (read_input)
    {
        cruise_down_release_flag = 1;
        return 1;
    }
    else
    {
        cruise_down_release_flag = 0;
        return 0;
    }
}

bool ECUInputReader::readCruiseSpeedUp() {
    bool read_input = cruise_speed_up.read();
    if (read_input && cruise_up_release_flag)
    {
        return 0;
    }
    else if (read_input)
    {
        cruise_up_release_flag = 1;
        return 1;
    }
    else
    {
        cruise_up_release_flag = 0;
        return 0;
    }
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

float ECUInputReader::readThrottle() {
    return throttle;
}

float ECUInputReader::readRegen() {
    return regen;
}