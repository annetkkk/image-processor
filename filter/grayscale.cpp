#include "grayscale.h"

BMP Grayscale::Apply(const BMP& image) const {
    const double red_weight = 0.299;
    const double green_weight = 0.587;
    const double blue_weight = 0.114;

    BMP result;
    result.width = image.width;
    result.height = image.height;
    result.pixels.resize(result.width * result.height);

    for (unsigned int i = 0; i < result.width * result.height; i++) {
        const Pixel& p = image.pixels[i];
        Pixel& r = result.pixels[i];
        unsigned char gray =
            static_cast<unsigned char>(red_weight * p.red + green_weight * p.green + blue_weight * p.blue);
        r.red = gray;
        r.green = gray;
        r.blue = gray;
    }

    return result;
}
