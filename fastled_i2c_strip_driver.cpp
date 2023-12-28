#include "global_includes.h"
#ifdef FASTLED_I2S

typedef struct _os_led_strip_t
{
    uint8_t *pixels;
    uint32_t numpixels;
    int pins[1];
} _os_led_strip_t;

_os_led_strip_t *_fastled_i2s_os_led_strip_init(int bus, int gpio, uint32_t numpixels)
{
    _os_led_strip_t *strip = NULL;
    strip = (_os_led_strip_t *)malloc(sizeof(_os_led_strip_t));

    if (strip == NULL)
    {
        return NULL;
    }

    strip->pixels = (uint8_t *)malloc(sizeof(uint8_t) * numpixels);
    strip->numpixels = numpixels;
    strip->pins[0] = gpio;

    return strip;
}

int free_fastled_i2s_strip(_os_led_strip_t *strip)
{
    if (strip == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    // Free the fastled_i2s array
    free(strip->pixels);

    // Free the strip
    free(strip);

    return OS_RET_OK;
}

int _fastled_i2s_os_led_strip_set(_os_led_strip_t *strip, uint32_t pixel, uint8_t r, uint8_t g, uint8_t b)
{
    if (strip == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    int index = pixel * 3;
    strip->pixels[index] = g;
    strip->pixels[index + 1] = b;
    strip->pixels[index + 2] = r;

    return OS_RET_OK;
}

int _fastled_i2s_os_led_strip_show(_os_led_strip_t *strip)
{

    if (strip == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    return OS_RET_OK;
}

int _fastled_i2s_led_strip_set_brightness(_os_led_strip_t *strip, uint8_t brightness)
{
    return OS_RET_OK;
}
#endif