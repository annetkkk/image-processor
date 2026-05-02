#include "edge.h"
#include "helpers.h"
#include "filter/grayscale.h"

BMP Edge::Apply(const BMP& image) const {
    const int center_weight = 4;
    const int bits = 255;

    Grayscale grayscale;
    BMP gray_image = grayscale.Apply(image);

    BMP result;
    result.width = image.width;
    result.height = image.height;
    result.pixels.resize(result.width * result.height);

    double threshold_value = threshold_ * bits;

    for (unsigned int y = 0; y < result.height; ++y) {
        for (unsigned int x = 0; x < result.width; ++x) {
            const Pixel center = GetPixel(gray_image, static_cast<int>(x), static_cast<int>(y));
            const Pixel top = GetPixel(gray_image, static_cast<int>(x), static_cast<int>(y) - 1);
            const Pixel bottom = GetPixel(gray_image, static_cast<int>(x), static_cast<int>(y) + 1);
            const Pixel left = GetPixel(gray_image, static_cast<int>(x) - 1, static_cast<int>(y));
            const Pixel right = GetPixel(gray_image, static_cast<int>(x) + 1, static_cast<int>(y));

            int value = center_weight * center.red - top.red - bottom.red - left.red - right.red;
            value = ClampColor(value);

            const unsigned int index = y * result.width + x;

            if (value > threshold_value) {
                result.pixels[index].red = bits;
                result.pixels[index].green = bits;
                result.pixels[index].blue = bits;
            } else {
                result.pixels[index].red = 0;
                result.pixels[index].green = 0;
                result.pixels[index].blue = 0;
            }
        }
    }

    return result;
}
