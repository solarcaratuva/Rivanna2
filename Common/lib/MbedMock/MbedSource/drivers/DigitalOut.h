// Adapted from Mbed source

#ifndef MBED_DIGITALOUT_H
#define MBED_DIGITALOUT_H

// #include "platform/platform.h"
// #include "hal/gpio_api.h"
#include "../PinNames.h"

namespace mbed {
/**
 * \defgroup drivers_DigitalOut DigitalOut class
 * \ingroup drivers-public-api-gpio
 * @{
 */

/** A digital output, used for setting the state of a pin
 *
 * @note Synchronization level: Interrupt safe
 *
 * Example:
 * @code
 * // Toggle a LED
 * #include "mbed.h"
 *
 * DigitalOut led(LED1);
 *
 * int main() {
 *     while(1) {
 *         led = !led;
 *         ThisThread::sleep_for(200);
 *     }
 * }
 * @endcode
 */
class DigitalOut {

public:
    /** Create a DigitalOut connected to the specified pin
     *
     *  @param pin DigitalOut pin to connect to
     */
    DigitalOut(PinName pin)
    {
        gpio = 0;
    }

    /** Create a DigitalOut connected to the specified pin
     *
     *  @param pin DigitalOut pin to connect to
     *  @param value the initial pin value
     */
    DigitalOut(PinName pin, int value)
    {
        gpio = value;
    }

    /** Set the output, specified as 0 or 1 (int)
     *
     *  @param value An integer specifying the pin output value,
     *      0 for logical 0, 1 (or any other non-zero value) for logical 1
     */
    void write(int value)
    {
        gpio = value;
    }

    /** Return the output setting, represented as 0 or 1 (int)
     *
     *  @returns
     *    an integer representing the output setting of the pin,
     *    0 for logical 0, 1 for logical 1
     */
    int read()
    {
        return gpio;
    }

    /** Return the output setting, represented as 0 or 1 (int)
     *
     *  @returns
     *    Non zero value if pin is connected to uc GPIO
     *    0 if gpio object was initialized with NC
     */
    int is_connected()
    {
        // Thread safe / atomic HAL call
        return 1;
    }

    /** A shorthand for write()
     * \sa DigitalOut::write()
     * @code
     *      DigitalIn  button(BUTTON1);
     *      DigitalOut led(LED1);
     *      led = button;   // Equivalent to led.write(button.read())
     * @endcode
     */
    DigitalOut &operator= (int value)
    {
        // Underlying write is thread safe
        write(value);
        return *this;
    }

    /** A shorthand for write() using the assignment operator which copies the
     * state from the DigitalOut argument.
     * \sa DigitalOut::write()
     */
    DigitalOut &operator= (DigitalOut &rhs);

    /** A shorthand for read()
     * \sa DigitalOut::read()
     * @code
     *      DigitalIn  button(BUTTON1);
     *      DigitalOut led(LED1);
     *      led = button;   // Equivalent to led.write(button.read())
     * @endcode
     */
    operator int()
    {
        // Underlying call is thread safe
        return read();
    }

protected:
#if !defined(DOXYGEN_ONLY)
    // gpio_t gpio;
    int gpio;
#endif //!defined(DOXYGEN_ONLY)
};

/** @}*/

} // namespace mbed

#endif
