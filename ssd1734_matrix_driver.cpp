#include "project_defs.h"

#ifdef SSD1734_ARDUINO_DRIVER

#include "CHAL_SHARED/csal_ledmatrix.h"
#include "rgbMatrix.h"

static int init_ledmatrix_ptr(void *ptr, int width, int height){

    RGBMatrixSLED1734  *matrix_driver = (RGBMatrixSLED1734*)ptr;
    // Initialize the driver
    matrix_driver->RGBMatrixInit();

    return OS_RET_OK;
}

static int matrix_setpixel_ptr(void *ptr, int x, int y, uint8_t r, uint8_t g, uint8_t b){
    RGBMatrixSLED1734  *matrix_driver = (RGBMatrixSLED1734*)ptr;

    uint8_t points[] = {x, y};
    matrix_driver->draw_point(points, r, g, b);
    return OS_RET_OK;
}

static int matrix_update_ptr(void *ptr){
    RGBMatrixSLED1734  *matrix_driver = (RGBMatrixSLED1734*)ptr;

    return OS_RET_OK;
}

int init_ssd1374_led_matrix(os_ledmatrix_t *matrix){
    matrix->data_ptr = (void*)new RGBMatrixSLED1734;
    os_ledmatrix_init_t init_params = {
        .init_func = init_ledmatrix_ptr, 
        .setpixel_func = matrix_setpixel_ptr, 
        .update_func = matrix_update_ptr, 
        .width = 8, 
        .height = 8, 
        .matrix_ptr = matrix->data_ptr
    };

    return os_init_ledmatrix(init_params, matrix);
}

#endif