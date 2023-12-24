#include "global_includes.h"
#ifdef NEOPIXEL_LED_STRIP
#include "Adafruit_NeoPixel.h"
typedef struct _os_led_strip_t
{
    Adafruit_NeoPixel *pixels;
} _os_led_strip_t;

_os_led_strip_t *_neopixel_os_led_strip_init(int bus, int gpio, uint32_t numpixels)
{
    _os_led_strip_t *strip = NULL;
    strip = (_os_led_strip_t *)malloc(sizeof(_os_led_strip_t));

    if (strip == NULL)
    {
        return NULL;
    }
    // Generate Neopixel strip object
    strip->pixels = NULL;
    strip->pixels = new Adafruit_NeoPixel(numpixels, gpio, NEO_GRB + NEO_KHZ800);

    if (strip->pixels == NULL)
    {
        free(strip);
        return NULL;
    }

    strip->pixels->setBrightness(30);
    return strip;
}

int free_neopixel_strip(_os_led_strip_t *strip){
    if(strip == NULL){
        return OS_RET_NULL_PTR;
    }
    
    // Free the neopixel array
    free(strip->pixels);
    
    // Free the strip
    free(strip);
}

int _neopixel_os_led_strip_set(_os_led_strip_t *strip, uint32_t pixel, uint8_t r, uint8_t g, uint8_t b)
{
    if (strip == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    strip->pixels->setPixelColor(pixel, r, g, b);
    return OS_RET_OK;
}

int _neopixel_os_led_strip_show(_os_led_strip_t *strip)
{

    if (strip == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    strip->pixels->show();
    return OS_RET_OK;
}
#endif