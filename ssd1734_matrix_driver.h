#ifndef _SSD1734_MATRIX_DRIVER_H
#define _SSD1734_MATRIX_DRIVER_H
#include "project_defs.h"

#ifdef SSD1734_ARDUINO_DRIVER
#include "CHAL_SHARED/csal_ledmatrix.h"

int init_ssd1374_led_matrix(os_ledmatrix_t *matrix);
#endif
#endif