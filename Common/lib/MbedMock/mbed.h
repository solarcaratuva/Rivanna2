#ifndef MBED_H
#define MBED_H

#define TRUE (1==1)
#define FALSE (!TRUE)

#define DEVICE_CAN TRUE  // enable CAN

// mbed Peripheral components
#include "MbedSource/drivers/DigitalIn.h"
#include "MbedSource/drivers/DigitalOut.h"
#include "MbedSource/drivers/CAN.h"

#ifndef MBED_NO_GLOBAL_USING_DIRECTIVE
using namespace mbed;
using namespace std;
#endif

#endif