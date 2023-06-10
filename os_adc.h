#ifndef OS_ADC_H
#define OS_ADH_H

#include "stdlib.h"
#include "stdint.h"
typedef struct os_adc_t{
    int fd;
    int bus;
    int fifosize;
    size_t num_bits;
}os_adc_t;

/**
 * @brief Initializes the ADC module
*/
int os_adc_begin(os_adc_t *adc);

/**
 * @brief Deinitializes the ADC Module
*/
int os_adc_end(os_adc_t *adc);

/**
 * @brief Get's a value from the adc module
*/
int os_adc_read(os_adc_t *adc, void *value);

/**
 * @brief Gathers a sequence of values from the ADC module
*/
int os_adc_read_values(os_adc_t *adc, uint32_t size, void *values);

#endif