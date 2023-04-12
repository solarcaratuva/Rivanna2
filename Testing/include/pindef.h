#ifndef PINDEF_H
#define PINDEF_H

#ifdef TARGET_UVA_SOLAR_CAR

#define LEFT_TURN PB0
#define RIGHT_TURN PB15
#define HAZARDS PC13
#define BRAKE PA9
#define REGEN PC6
#define FORWARD PB1

enum AnalogInputPins {
    THROTTLE = 27,
};

enum DigitalOutputPins {
    BRAKE_LIGHT = 26,
    LEFT_TURN_LIGHT = 8,
    RIGHT_TURN_LIGHT = 9,
    DRO = 25,
    BMS_STROBE = 16
};
#else

#endif

#endif
