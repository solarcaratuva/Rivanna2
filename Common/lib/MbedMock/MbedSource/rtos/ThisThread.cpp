/* mbed Microcontroller Library
 * Copyright (c) 2006-2012 ARM Limited
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#define __STDC_LIMIT_MACROS
#define MBED_CONF_RTOS_PRESENT 1

#include "../rtos/ThisThread.h"

// #include "platform/mbed_toolchain.h"
#include "../rtos/Kernel.h"
// #include "platform/CriticalSectionLock.h"
// #include "platform/mbed_assert.h"
// #include "platform/mbed_critical.h"
// #include "platform/internal/mbed_os_timer.h"

using std::milli;
using std::chrono::duration;
using rtos::Kernel::Clock;
using rtos::Kernel::wait_for_u32_max;
using rtos::Kernel::wait_for_u32_forever;

// #if !MBED_CONF_RTOS_PRESENT
// /* If the RTOS is not present, we call mbed_thread.cpp to do the work */
// /* If the RTOS is present, mbed_thread.cpp calls us to do the work */
// #include "platform/mbed_thread.h"

// static uint32_t thread_flags;

// /* For the flags to be useful, need a way of setting them, but there's only the main
//  * thread, and that has no Thread object, so Thread class is not provided. Implement
//  * one CMSIS-RTOS function to provide access.
//  */
// extern "C"
// uint32_t osThreadFlagsSet(osThreadId_t /*thread_id*/, uint32_t flags)
// {
//     return core_util_atomic_fetch_or_u32(&thread_flags, flags) | flags;
// }
// #endif

namespace rtos {

uint32_t ThisThread::flags_clear(uint32_t flags) {return 0;}

uint32_t ThisThread::flags_get() {return 0;}


static uint32_t flags_wait_for(uint32_t flags, Clock::duration_u32 rel_time, bool clear, uint32_t options) {return 0;}

static uint32_t flags_wait(uint32_t flags, bool clear, uint32_t options) {return 0;}

static uint32_t flags_wait_until(uint32_t flags, Clock::time_point abs_time, bool clear, uint32_t options) {return 0;}

uint32_t ThisThread::flags_wait_all(uint32_t flags, bool clear) {return 0;}

uint32_t ThisThread::flags_wait_all_for(uint32_t flags, uint32_t millisec, bool clear) {return 0;}

uint32_t ThisThread::flags_wait_all_for(uint32_t flags, Clock::duration_u32 rel_time, bool clear) {return 0;}

uint32_t ThisThread::flags_wait_all_until(uint32_t flags, uint64_t millisec, bool clear) {return 0;}

uint32_t ThisThread::flags_wait_all_until(uint32_t flags, Clock::time_point abs_time, bool clear) {return 0;}

uint32_t ThisThread::flags_wait_any(uint32_t flags, bool clear) {return 0;}

uint32_t ThisThread::flags_wait_any_for(uint32_t flags, uint32_t millisec, bool clear) {return 0;}

uint32_t ThisThread::flags_wait_any_for(uint32_t flags, Clock::duration_u32 rel_time, bool clear) {return 0;}

uint32_t ThisThread::flags_wait_any_until(uint32_t flags, uint64_t millisec, bool clear) {return 0;}

uint32_t ThisThread::flags_wait_any_until(uint32_t flags, Clock::time_point abs_time, bool clear) {return 0;}

void ThisThread::sleep_for(uint32_t millisec) {}

void ThisThread::sleep_for(Clock::duration_u32 rel_time) {}

void ThisThread::sleep_until(uint64_t millisec) {}

void ThisThread::sleep_until(Clock::time_point abs_time) {}

void ThisThread::yield() {}

osThreadId_t ThisThread::get_id() {return 0;}

const char *ThisThread::get_name() {return 0;}

}
