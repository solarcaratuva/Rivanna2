// Adapted from Mbed source

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <stdint.h>
#include <chrono>
#include "../rtos/mbed_rtos_types.h"
#include "../internal/mbed_rtos1_types.h"
#include "../internal/mbed_rtos_storage.h"
#include "../rtos/Kernel.h"
//#include "platform/mbed_toolchain.h"
//#include "platform/NonCopyable.h"

namespace rtos {
/** \addtogroup rtos-public-api */
/** @{*/

/**
 * \defgroup rtos_Semaphore Semaphore class
 * @{
 */

/** The Semaphore class is used to manage and protect access to a set of shared resources.
 *
 * @note
 * Memory considerations: The semaphore control structures will be created on current thread's stack, both for the mbed OS
 * and underlying RTOS objects (static or dynamic RTOS memory pools are not being used).
 */
class Semaphore {
public:
    /** Create and Initialize a Semaphore object used for managing resources.
      @param count      number of available resources; maximum index value is (count-1). (default: 0).

      @note You cannot call this function from ISR context.
    */
    Semaphore(int32_t count = 0);

    /** Create and Initialize a Semaphore object used for managing resources.
      @param  count     number of available resources
      @param  max_count maximum number of available resources

      @note You cannot call this function from ISR context.
    */
    Semaphore(int32_t count, uint16_t max_count);

    /** Wait until a Semaphore resource becomes available.

      @note You cannot call this function from ISR context.
    */
    virtual void acquire() = 0;

    /** Try to acquire a Semaphore resource, and return immediately
      @return true if a resource was acquired, false otherwise.
      @note equivalent to try_acquire_for(0)

    @note You may call this function from ISR context.
    */
    virtual bool try_acquire() = 0;

    /** Wait until a Semaphore resource becomes available.
      @param   millisec  timeout value.
      @return true if a resource was acquired, false otherwise.

      @note You may call this function from ISR context if the millisec parameter is set to 0.
      @deprecated Pass a chrono duration, not an integer millisecond count. For example use `5s` rather than `5000`.
    */
    //MBED_DEPRECATED_SINCE("mbed-os-6.0.0", "Pass a chrono duration, not an integer millisecond count. For example use `5s` rather than `5000`.")
    virtual bool try_acquire_for(uint32_t millisec) = 0;

    /** Wait until a Semaphore resource becomes available.
       @param   rel_time  timeout value.
       @return true if a resource was acquired, false otherwise.

       @note You may call this function from ISR context if the rel_time parameter is set to 0.
     */
    virtual bool try_acquire_for(Kernel::Clock::duration_u32 rel_time) = 0;

    /** Wait until a Semaphore resource becomes available.
      @param   millisec  absolute timeout time, referenced to Kernel::get_ms_count()
      @return true if a resource was acquired, false otherwise.
      @note the underlying RTOS may have a limit to the maximum wait time
            due to internal 32-bit computations, but this is guaranteed to work if the
            wait is <= 0x7fffffff milliseconds (~24 days). If the limit is exceeded,
            the acquire attempt will time out earlier than specified.

      @note You cannot call this function from ISR context.
      @deprecated Pass a chrono time_point, not an integer millisecond count. For example use
                  `Kernel::Clock::now() + 5s` rather than `Kernel::get_ms_count() + 5000`.
    */
    //MBED_DEPRECATED_SINCE("mbed-os-6.0.0", "Pass a chrono time_point, not an integer millisecond count. For example use `Kernel::Clock::now() + 5s` rather than `Kernel::get_ms_count() + 5000`.")
    virtual bool try_acquire_until(uint64_t millisec) = 0;

    /** Wait until a Semaphore resource becomes available.
      @param   millisec  absolute timeout time, referenced to Kernel::Clock
      @return true if a resource was acquired, false otherwise.
      @note the underlying RTOS may have a limit to the maximum wait time
            due to internal 32-bit computations, but this is guaranteed to work if the
            wait is <= 0x7fffffff milliseconds (~24 days). If the limit is exceeded,
            the acquire attempt will time out earlier than specified.

      @note You cannot call this function from ISR context.
    */
    virtual bool try_acquire_until(Kernel::Clock::time_point abs_time) = 0;

    /** Release a Semaphore resource that was obtain with Semaphore::acquire.
      @return status code that indicates the execution status of the function:
              @a osOK the token has been correctly released.
              @a osErrorResource the maximum token count has been reached.
              @a osErrorParameter internal error.

      @note You may call this function from ISR context.
    */
    virtual osStatus release(void) = 0;

    /** Semaphore destructor
     *
     * @note You cannot call this function from ISR context.
     */
    ~Semaphore() {}

private:
    virtual void constructor(int32_t count, uint16_t max_count) = 0;

#if MBED_CONF_RTOS_PRESENT
    virtual int32_t _wait(uint32_t millisec) = 0;

    osSemaphoreId_t               _id;
    mbed_rtos_storage_semaphore_t _obj_mem;
#else
    static bool semaphore_available(void *);
    int32_t _count;
    uint16_t _max_count;
#endif
};
/** @}*/
/** @}*/
}
#endif
