#include "negative.h"

BMP Negative::Apply(const BMP& image) const {
    BMP result;
    result.width = image.width;
    result.height = image.height;
    result.pixels.resize(result.width * result.height);
    const int bits = 255;

    for (unsigned int i = 0; i < image.pixels.size(); i++) {
        const Pixel& p = image.pixels[i];
        Pixel& r = result.pixels[i];
        r.red = bits - p.red;
        r.green = bits - p.green;
        r.blue = bits - p.blue;
    }

    return result;
}
