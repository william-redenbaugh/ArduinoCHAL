/**
 * @file hsv_rgb_converter.h
 * @brief Header file for HSV to RGB and RGB to HSV conversion functions.
 */

#ifndef HSV_RGB_CONVERTER_H
#define HSV_RGB_CONVERTER_H

#include <stdint.h>

/**
 * @struct RGB
 * @brief Structure representing RGB values.
 */
typedef struct {
    uint8_t r; /**< Red value (0-255) */
    uint8_t g; /**< Green value (0-255) */
    uint8_t b; /**< Blue value (0-255) */
} RGB;

/**
 * @struct HSV
 * @brief Structure representing HSV values.
 */
typedef struct {
    uint8_t h; /**< Hue value (0-255) */
    uint8_t s; /**< Saturation value (0-255) */
    uint8_t v; /**< Value value (0-255) */
} HSV;

/**
 * @brief Converts HSV (Hue, Saturation, Value) to RGB (Red, Green, Blue).
 *
 * @param hsv The HSV structure containing the input values.
 * @return The RGB structure with the converted RGB values.
 */
RGB HSVtoRGB(HSV hsv);

/**
 * @brief Converts RGB (Red, Green, Blue) to HSV (Hue, Saturation, Value).
 *
 * @param rgb The RGB structure containing the input values.
 * @return The HSV structure with the converted HSV values.
 */
HSV RGBtoHSV(RGB rgb);

#endif /* HSV_RGB_CONVERTER_H */