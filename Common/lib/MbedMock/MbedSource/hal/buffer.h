// Adapted from Mbed Source

#ifndef MBED_BUFFER_H
#define MBED_BUFFER_H

#include <stddef.h>
#include <stdint.h>

/** Generic buffer structure
 */
typedef struct buffer_s {
    void    *buffer; /**< the pointer to a buffer */
    size_t   length; /**< the buffer length */
    size_t   pos;    /**< actual buffer position */
    uint8_t  width;  /**< The buffer unit width (8, 16, 32, 64), used for proper *buffer casting */
} buffer_t;

#endif

/** @}*/
