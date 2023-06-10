#include <stdint.h>
#include "hsv2rgb.h"

RGB HSVtoRGB(HSV hsv) {
    RGB rgb;

    uint8_t region, remainder, p, q, t;

    if (hsv.s == 0) {
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;
        return rgb;
    }

    region = hsv.h / 43;
    remainder = (hsv.h - (region * 43)) * 6;

    p = (hsv.v * (255 - hsv.s)) >> 8;
    q = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
    t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;

    switch (region) {
        case 0:
            rgb.r = hsv.v;
            rgb.g = t;
            rgb.b = p;
            break;
        case 1:
            rgb.r = q;
            rgb.g = hsv.v;
            rgb.b = p;
            break;
        case 2:
            rgb.r = p;
            rgb.g = hsv.v;
            rgb.b = t;
            break;
        case 3:
            rgb.r = p;
            rgb.g = q;
            rgb.b = hsv.v;
            break;
        case 4:
            rgb.r = t;
            rgb.g = p;
            rgb.b = hsv.v;
            break;
        default:
            rgb.r = hsv.v;
            rgb.g = p;
            rgb.b = q;
            break;
    }

    return rgb;
}

HSV RGBtoHSV(RGB rgb) {
    HSV hsv;

    uint8_t min_value = rgb.r < rgb.g ? (rgb.r < rgb.b ? rgb.r : rgb.b) : (rgb.g < rgb.b ? rgb.g : rgb.b);
    uint8_t max_value = rgb.r > rgb.g ? (rgb.r > rgb.b ? rgb.r : rgb.b) : (rgb.g > rgb.b ? rgb.g : rgb.b);
    uint8_t delta = max_value - min_value;

    hsv.v = max_value;
    if (max_value == 0) {
        hsv.h = 0;
        hsv.s = 0;
        return hsv;
    }

    hsv.s = 255 * (uint16_t)delta / max_value;
    if (delta == 0) {
        hsv.h = 0;
        return hsv;
    }

    if (rgb.r == max_value)
        hsv.h = 0 + 43 * (rgb.g - rgb.b) / delta;
    else if (rgb.g == max_value)
        hsv.h = 85 + 43 * (rgb.b - rgb.r) / delta;
    else
        hsv.h = 171 + 43 * (rgb.r - rgb.g) / delta;

    return hsv;
}