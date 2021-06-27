#ifndef MBED_H
#define MBED_H

#define TRUE (1==1)
#define FALSE (!TRUE)

#define DEVICE_ANALOGIN TRUE  // enable AnalogIn
#define DEVICE_CAN      TRUE  // enable CAN
#define DEVICE_I2C      TRUE  // enable I2C
#define DEVICE_SPI      TRUE  // enable SPI

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