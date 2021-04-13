// Adapted from Mbed source

#ifndef MBED_TICKER_H
#define MBED_TICKER_H

#include <chrono>
// #include <mstd_utility>
// #include "drivers/TickerDataClock.h"
// #include "drivers/TimerEvent.h"
// #include "platform/Callback.h"
// #include "platform/mbed_toolchain.h"
// #include "platform/NonCopyable.h"
// #include "hal/lp_ticker_api.h"
#include "../hal/ticker_api.h"

namespace mbed {

/**
 * \defgroup drivers_Ticker Ticker class
 * \ingroup drivers-public-api-ticker
 * @{
 */

/** A Ticker is used to call a function at a recurring interval
 *
 *  You can use as many separate Ticker objects as you require.
 *
 * @note Synchronization level: Interrupt safe
 *
 * Example:
 * @code
 * // Toggle the blinking LED after 5 seconds
 *
 * #include "mbed.h"
 * using namespace std::chrono;
 *
 * Ticker timer;
 * DigitalOut led1(LED1);
 * DigitalOut led2(LED2);
 *
 * int flip = 0;
 *
 * void attime() {
 *     flip = !flip;
 * }
 *
 * int main() {
 *     timer.attach(&attime, 5us);
 *     while(1) {
 *         if(flip == 0) {
 *             led1 = !led1;
 *         } else {
 *             led2 = !led2;
 *         }
 *         ThisThread::sleep_for(200ms);
 *     }
 * }
 * @endcode
 */
class TickerBase /*: public TimerEvent, private NonCopyable<TickerBase>*/ {
public:
    /** Attach a function to be called by the Ticker, specifying the interval in seconds
     *
     *  The method forwards its arguments to attach_us() rather than copying them which
     *  may not be trivial depending on the callback copied.
     *  The function is forcibly inlined to not use floating-point operations. This is
     *  possible given attach_us() expects an integer value for the callback interval.
     *  @param func pointer to the function to be called
     *  @param t the time between calls in seconds
     *  @deprecated Pass a chrono duration, not a float second count. For example use `10ms` rather than `0.01f`.
     */
    virtual void attach(void (*func)(void), float t) = 0;

    /** Attach a function to be called by the Ticker, specifying the interval in microseconds
     *
     *  @param func pointer to the function to be called
     *  @param t the time between calls in micro-seconds
     *
     *  @note setting @a t to a value shorter than it takes to process the ticker callback
     *  causes the system to hang. Ticker callback is called constantly with no time
     *  for threads scheduling.
     *  @deprecated Pass a chrono duration, not an integer microsecond count. For example use `10ms` rather than `10000`.
     *
     */
    virtual void attach_us(void (*func)(void), us_timestamp_t t) = 0;

    /** Attach a function to be called by the Ticker, specifying the interval in microseconds
     *
     *  @param func pointer to the function to be called
     *  @param t the time between calls in micro-seconds
     *
     *  @note setting @a t to a value shorter than it takes to process the ticker callback
     *  causes the system to hang. Ticker callback is called constantly with no time
     *  for threads scheduling.
     *
     */
    virtual void attach(void (*func)(void), std::chrono::microseconds t) = 0;

    /** Detach the function
     */
    virtual void detach() = 0;
};

class Ticker : public TickerBase {
public:
    Ticker();
};
/** @}*/

} // namespace mbed

#endif
