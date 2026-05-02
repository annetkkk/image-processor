#include "crop.h"
#include <algorithm>

BMP Crop::Apply(const BMP& image) const {
    unsigned int new_width = std::min(width_, image.width);
    unsigned int new_height = std::min(height_, image.height);

    BMP result;
    result.width = new_width;
    result.height = new_height;
    result.pixels.resize(result.width * result.height);

    for (unsigned int y = 0; y < result.height; y++) {
        for (unsigned int x = 0; x < result.width; x++) {
            unsigned int old_index = y * image.width + x;
            unsigned int new_index = y * result.width + x;
            result.pixels[new_index] = image.pixels[old_index];
        }
    }

    return result;
}
