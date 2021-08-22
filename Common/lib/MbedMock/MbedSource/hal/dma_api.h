// Adapted from Mbed Source

#ifndef MBED_DMA_API_H
#define MBED_DMA_API_H

#include <stdint.h>

#define DMA_ERROR_OUT_OF_CHANNELS (-1)

typedef enum {
    DMA_USAGE_NEVER,
    DMA_USAGE_OPPORTUNISTIC,
    DMA_USAGE_ALWAYS,
    DMA_USAGE_TEMPORARY_ALLOCATED,
    DMA_USAGE_ALLOCATED
} DMAUsage;

#ifdef __cplusplus
extern "C" {
#endif

void dma_init(void);

int dma_channel_allocate(uint32_t capabilities);

int dma_channel_free(int channelid);

#ifdef __cplusplus
}
#endif

#endif

/** @}*/
