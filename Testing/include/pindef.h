#ifndef PINDEF_H
#define PINDEF_H

#ifdef TARGET_UVA_SOLAR_CAR

#define BRAKE_LIGHT = PB_13
#define LEFT_TURN_LIGHT = PA_0
#define RIGHT_TURN_LIGHT = PA_1
#define DRO = PB_12
#define BMS_STROBE = PC_

enum DigitalInputPins {
    LEFT_TURN = PB0,
    RIGHT_TURN = PB15,
    HAZARDS = PC13,
    BRAKE = PA9,
    REGEN = PC6,
    FORWARD = PB1
};

enum AnalogInputPins {
    THROTTLE = 27,
};

enum DigitalOutputPins {
    BRAKE_LIGHT,
    LEFT_TURN_LIGHT,
    RIGHT_TURN_LIGHT,
    DRO,
    BMS_STROBE
};

#endif

#endif // PINDEF_H