// Adapted from Mbed source

#ifndef MBED_PINNAMESTYPES_H
#define MBED_PINNAMESTYPES_H

// #include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/*  Defines to be used by application */
// typedef enum {
//     PIN_INPUT = 0,
//     PIN_OUTPUT
// } PinDirection;

typedef enum {
    PullNone = 0,
    PullUp = 1,
    PullDown = 2,
    OpenDrainPullUp = 3,
    OpenDrainNoPull = 4,
    OpenDrainPullDown = 5,
    PushPullNoPull = PullNone,
    PushPullPullUp = PullUp,
    PushPullPullDown = PullDown,
    OpenDrain = OpenDrainPullUp,
    PullDefault = PullNone
} PinMode;

#ifdef __cplusplus
}
#endif

#endif
