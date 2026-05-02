#include "sharpen.h"
#include "helpers.h"

BMP Sharpen::Apply(const BMP& image) const {
    const int center_weight = 5;

    BMP result;
    result.width = image.width;
    result.height = image.height;
    result.pixels.resize(result.width * result.height);

    for (unsigned int y = 0; y < result.height; ++y) {
        for (unsigned int x = 0; x < result.width; ++x) {
            const Pixel center = GetPixel(image, static_cast<int>(x), static_cast<int>(y));
            const Pixel top = GetPixel(image, static_cast<int>(x), static_cast<int>(y) - 1);
            const Pixel bottom = GetPixel(image, static_cast<int>(x), static_cast<int>(y) + 1);
            const Pixel left = GetPixel(image, static_cast<int>(x) - 1, static_cast<int>(y));
            const Pixel right = GetPixel(image, static_cast<int>(x) + 1, static_cast<int>(y));

            int new_red = center_weight * center.red - top.red - bottom.red - left.red - right.red;
            int new_green = center_weight * center.green - top.green - bottom.green - left.green - right.green;
            int new_blue = center_weight * center.blue - top.blue - bottom.blue - left.blue - right.blue;

            new_red = ClampColor(new_red);
            new_green = ClampColor(new_green);
            new_blue = ClampColor(new_blue);

            const unsigned int index = y * result.width + x;
            result.pixels[index].red = static_cast<unsigned char>(new_red);
            result.pixels[index].green = static_cast<unsigned char>(new_green);
            result.pixels[index].blue = static_cast<unsigned char>(new_blue);
        }
    }

    return result;
}
