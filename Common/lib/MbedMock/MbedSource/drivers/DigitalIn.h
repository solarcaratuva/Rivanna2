// Adapted from Mbed source

#ifndef MBED_DIGITALIN_H
#define MBED_DIGITALIN_H

// #include "platform/platform.h"
// #include "hal/gpio_api.h"
#include "../PinNames.h"
#include "../PinNamesTypes.h"

namespace mbed {
/**
 * \defgroup drivers_DigitalIn DigitalIn class
 * \ingroup drivers-public-api-gpio
 * @{
 */

/** A digital input, used for reading the state of a pin
 *
 * @note Synchronization level: Interrupt safe
 *
 * Example:
 * @code
 * // Flash an LED while a DigitalIn is true
 *
 * #include "mbed.h"
 *
 * DigitalIn enable(p5);
 * DigitalOut led(LED1);
 *
 * int main() {
 *     while(1) {
 *         if(enable) {
 *             led = !led;
 *         }
 *         ThisThread::sleep_for(250);
 *     }
 * }
 * @endcode
 */
class DigitalIn {

  public:
    /** Create a DigitalIn connected to the specified pin
     *
     *  @param pin DigitalIn pin to connect to
     */
    DigitalIn(PinName pin);

    /** Create a DigitalIn connected to the specified pin
     *
     *  @param pin DigitalIn pin to connect to
     *  @param mode the initial mode of the pin
     */
    DigitalIn(PinName pin, PinMode mode);

    /** Read the input, represented as 0 or 1 (int)
     *
     *  @returns
     *    An integer representing the state of the input pin,
     *    0 for logical 0, 1 for logical 1
     */
    virtual int read() = 0;

    /** Set the input pin mode
     *
     *  @param pull PullUp, PullDown, PullNone, OpenDrain
     */
    virtual void mode(PinMode pull) = 0;

    /** Return the output setting, represented as 0 or 1 (int)
     *
     *  @returns
     *    Non zero value if pin is connected to uc GPIO
     *    0 if gpio object was initialized with NC
     */
    virtual int is_connected() = 0;

    /** An operator shorthand for read()
     * \sa DigitalIn::read()
     * @code
     *      DigitalIn  button(BUTTON1);
     *      DigitalOut led(LED1);
     *      led = button;   // Equivalent to led.write(button.read())
     * @endcode
     */
    virtual operator int() {
        // Underlying read is thread safe
        return read();
    }
};

/** @}*/

} // namespace mbed

#endif
