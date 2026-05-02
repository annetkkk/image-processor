#pragma once
#include "bmp.h"

inline int Clamp(int value, int min_value, int max_value) {
    if (value < min_value) {
        return min_value;
    }
    if (value > max_value) {
        return max_value;
    }
    return value;
}

inline Pixel GetPixel(const BMP& image, int x, int y) {
    x = Clamp(x, 0, static_cast<int>(image.width) - 1);
    y = Clamp(y, 0, static_cast<int>(image.height) - 1);

    const unsigned int clamped_x = static_cast<unsigned int>(x);
    const unsigned int clamped_y = static_cast<unsigned int>(y);
    const unsigned int index = clamped_y * image.width + clamped_x;

    return image.pixels[index];
}

inline int ClampColor(int value) {
    const int color_max = 255;

    if (value < 0) {
        return 0;
    }
    if (value > color_max) {
        return color_max;
    }
    return value;
}
