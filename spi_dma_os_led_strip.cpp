#include "global_includes.h"
#include "ESP32DMASPIMaster.h"

#define ARDUINO_SPI_ESP32_STRIP
#ifdef ARDUINO_SPI_ESP32_STRIP

#define BYTES_FOR_LED_BYTE 4
#define NB_COLORS 3
#define BYTES_FOR_LED BYTES_FOR_LED_BYTE *NB_COLORS
#define DATA_SIZE BYTES_FOR_LED *NB_LEDS
#define RESET_SIZE 200

typedef struct _os_led_strip_t
{
    ESP32DMASPI::Master master;
    uint8_t *pixels;
    uint32_t size;
    uint8_t brightness;
} _os_led_strip_t;

static uint8_t get_protocol_eq(uint8_t data, int pos)
{
    uint8_t eq = 0;
    if (data & (1 << (2 * (3 - pos))))
        eq = 0b1110;
    else
        eq = 0b1000;
    if (data & (2 << (2 * (3 - pos))))
        eq += 0b11100000;
    else
        eq += 0b10000000;
    return eq;
}

_os_led_strip_t *_spi_dma_os_led_strip_init(int bus, int gpio, uint32_t numpixels)
{
    _os_led_strip_t *strip = NULL;

    strip = new _os_led_strip_t;

    if (strip == NULL)
    {
        return NULL;
    }

    strip->size = (sizeof(uint8_t) * 12 * numpixels + 200);
    strip->pixels = strip->master.allocDMABuffer(sizeof(uint8_t) * 12 * numpixels + 200);
    strip->master.setDataMode(SPI_MODE0);
    strip->master.setFrequency(2400000);
    strip->master.begin(bus, -1, -1, gpio, -1);
    memset(strip->pixels, 0, strip->size);
    strip->brightness = 30;

    if (strip->pixels == NULL)
    {
        printf("Couldn't allocate DMA buffer for LED Strip");
        delete strip;
        return NULL;
    }

    _spi_dma_os_led_strip_show(strip);

    return strip;
}

int free_spi_dma_strip(_os_led_strip_t *strip)
{
    if (strip == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    // Free the neopixel array
    free(strip->pixels);

    // Free the strip
    free(strip);

    return OS_RET_OK;
}

int _spi_dma_os_led_strip_set(_os_led_strip_t *strip, uint32_t pixel, uint8_t r, uint8_t g, uint8_t b)
{
    if (strip == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    r = (r * strip->brightness) >> 8;
    g = (g * strip->brightness) >> 8;
    b = (b * strip->brightness) >> 8;

    for (int j = 0; j < 4; j++)
        strip->pixels[BYTES_FOR_LED * pixel + j] = get_protocol_eq(g, j);
    for (int j = 0; j < 4; j++)
        strip->pixels[BYTES_FOR_LED * pixel + BYTES_FOR_LED_BYTE + j] = get_protocol_eq(r, j);
    for (int j = 0; j < 4; j++)
        strip->pixels[BYTES_FOR_LED * pixel + BYTES_FOR_LED_BYTE * 2 + j] = get_protocol_eq(b, j);

    return OS_RET_OK;
}

int _spi_dma_os_led_strip_show(_os_led_strip_t *strip)
{

    if (strip == NULL)
    {
        return OS_RET_NULL_PTR;
    }
    size_t bytes = strip->master.transfer(strip->pixels, strip->size);
    if (bytes <= 0)
    {
        return OS_RET_INT_ERR;
    }

    return OS_RET_OK;
}

int _spi_dma_os_led_strip_set_brightness(_os_led_strip_t *strip, uint8_t brightness)
{
    strip->brightness = brightness;

    return OS_RET_OK;
}

#endif