// Adapted from Mbed source

#ifndef MBED_ANALOGIN_H
#define MBED_ANALOGIN_H

// #include "platform/platform.h"

#if DEVICE_ANALOGIN || defined(DOXYGEN_ONLY)

// #include "hal/analogin_api.h"
// #include "platform/SingletonPtr.h"
// #include "platform/PlatformMutex.h"
#include "../hal/pinmap.h"

// #include <cmath>

namespace mbed {
/** \defgroup mbed-os-public Public API */

/** \defgroup drivers-public-api Drivers
 * \ingroup mbed-os-public
 */

/** \defgroup drivers-public-api-gpio GPIO
 * \ingroup drivers-public-api
 */

/**
 * \defgroup drivers_AnalogIn AnalogIn class
 * \ingroup drivers-public-api-gpio
 * @{
 */

/** An analog input, used for reading the voltage on a pin
 *
 * @note Synchronization level: Thread safe
 *
 * Example:
 * @code
 * // Print messages when the AnalogIn is greater than 50%
 *
 * #include "mbed.h"
 *
 * AnalogIn temperature(p20);
 *
 * int main() {
 *     while(1) {
 *         if(temperature > 0.5) {
 *             printf("Too hot! (%f)", temperature.read());
 *         }
 *     }
 * }
 * @endcode
 */
class AnalogIn {

public:

    /** Create an AnalogIn, connected to the specified pin
     *
     * @param pinmap reference to structure which holds static pinmap.
     * @param vref (optional) Reference voltage of this AnalogIn instance (defaults to target.default-adc-vref).
     *
     * @note An input voltage at or above the given vref value will produce a 1.0 result when `read` is called
     */
    // AnalogIn(const PinMap &pinmap, float vref = 0.0f);
    // AnalogIn(const PinMap &&, float vref = 0.0f) = delete; // prevent passing of temporary objects

    /** Create an AnalogIn, connected to the specified pin
     *
     * @param pin AnalogIn pin to connect to
     * @param vref (optional) Reference voltage of this AnalogIn instance (defaults to target.default-adc-vref).
     *
     * @note An input voltage at or above the given vref value will produce a 1.0 result when `read` is called
     */
    AnalogIn(PinName pin, float vref = 0.0f);

    /** Read the input voltage, represented as a float in the range [0.0, 1.0]
     *
     * @returns A floating-point value representing the current input voltage, measured as a percentage
     */
    virtual float read() = 0;

    /** Read the input voltage, represented as an unsigned short in the range [0x0, 0xFFFF]
     *
     * @returns
     *   16-bit unsigned short representing the current input voltage, normalized to a 16-bit value
     */
    virtual unsigned short read_u16() = 0;

    /**
     * Read the input voltage in volts. The output depends on the target board's
     * ADC reference voltage (typically equal to supply voltage). The ADC reference voltage
     * sets the maximum voltage the ADC can quantify (ie: ADC output == ADC_MAX_VALUE when Vin == Vref)
     *
     * The target's default ADC reference voltage is determined by the configuration
     * option target.default-adc_vref. The reference voltage for a particular input
     * can be manually specified by either the constructor or `AnalogIn::set_reference_voltage`.
     *
     * @returns A floating-point value representing the current input voltage, measured in volts.
     */
    virtual float read_voltage() = 0;

    /**
     * Sets this AnalogIn instance's reference voltage.
     *
     * The AnalogIn's reference voltage is used to scale the output when calling AnalogIn::read_volts
     *
     * @param[in] vref New ADC reference voltage for this AnalogIn instance.
     */
    virtual void set_reference_voltage(float vref) = 0;

    /**
     * Gets this AnalogIn instance's reference voltage.
     *
     * @returns A floating-point value representing this AnalogIn's reference voltage, measured in volts.
     */
    virtual float get_reference_voltage() const = 0;

    /** An operator shorthand for read()
     *
     * The float() operator can be used as a shorthand for read() to simplify common code sequences
     *
     * Example:
     * @code
     * float x = volume.read();
     * float x = volume;
     *
     * if(volume.read() > 0.25) { ... }
     * if(volume > 0.25) { ... }
     * @endcode
     */
    operator float()
    {
        // Underlying call is thread safe
        return read();
    }

    virtual ~AnalogIn() = 0;
};

/** @}*/

} // namespace mbed

#endif

#endif
