#ifndef MBED_H
#define MBED_H

#include "device.h"

// mbed RTOS
#if MBED_CONF_RTOS_API_PRESENT || PIO_FRAMEWORK_MBED_RTOS_PRESENT
#define MBED_CONF_RTOS_PRESENT 1
#include "MbedSource/rtos/rtos.h"
#endif

// mbed Peripheral components
#include "MbedSource/drivers/AnalogIn.h"
#include "MbedSource/drivers/DigitalIn.h"
#include "MbedSource/drivers/DigitalOut.h"
#include "MbedSource/drivers/CAN.h"
#include "MbedSource/drivers/Ticker.h"
#include "MbedSource/drivers/SPI.h"
#include "MbedSource/drivers/I2C.h"

// standard library includes
#include <string>   // for string class
#include <stdio.h>  // for printf()

#ifndef MBED_NO_GLOBAL_USING_DIRECTIVE
using namespace mbed;
using namespace std;
#endif

#endif