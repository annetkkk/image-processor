#include "blur.h"
#include "helpers.h"

#include <cmath>
#include <stdexcept>
#include <vector>

BMP Blur::Apply(const BMP& image) const {
    if (sigma_ <= 0) {
        throw std::runtime_error("Сигма должна быть положительным числом");
    }
    const int radius = static_cast<int>(std::ceil(3 * sigma_));
    std::vector<double> kernel;
    double sum_weights = 0;

    for (int offset = -radius; offset <= radius; offset++) {
        double weight = std::exp(-(offset * offset) / (2 * sigma_ * sigma_));
        kernel.push_back(weight);
        sum_weights += weight;
    }

    for (int offset = 0; offset < kernel.size(); offset++) {
        kernel[offset] /= sum_weights;
    }

    BMP result;
    result.width = image.width;
    result.height = image.height;
    result.pixels.resize(result.width * result.height);

    std::vector<double> temp_red(image.width * image.height);
    std::vector<double> temp_green(image.width * image.height);
    std::vector<double> temp_blue(image.width * image.height);

    for (int y = 0; y < static_cast<int>(image.height); y++) {
        for (int x = 0; x < static_cast<int>(image.width); x++) {
            double sum_red = 0;
            double sum_green = 0;
            double sum_blue = 0;

            for (int dx = -radius; dx <= radius; dx++) {
                auto pixel = GetPixel(image, x + dx, y);
                auto weight = kernel[dx + radius];

                sum_red += pixel.red * weight;
                sum_green += pixel.green * weight;
                sum_blue += pixel.blue * weight;
            }

            const unsigned int index = static_cast<unsigned int>(y) * image.width + static_cast<unsigned int>(x);
            temp_red[index] = sum_red;
            temp_green[index] = sum_green;
            temp_blue[index] = sum_blue;
        }
    }

    for (int y = 0; y < static_cast<int>(image.height); y++) {
        for (int x = 0; x < static_cast<int>(image.width); x++) {
            double sum_red = 0;
            double sum_green = 0;
            double sum_blue = 0;

            for (int dy = -radius; dy <= radius; dy++) {
                const int clamped_y = Clamp(y + dy, 0, static_cast<int>(image.height) - 1);
                const unsigned int index =
                    static_cast<unsigned int>(clamped_y) * image.width + static_cast<unsigned int>(x);
                const double weight = kernel[dy + radius];

                sum_red += temp_red[index] * weight;
                sum_green += temp_green[index] * weight;
                sum_blue += temp_blue[index] * weight;
            }
            const unsigned int result_index =
                static_cast<unsigned int>(y) * result.width + static_cast<unsigned int>(x);
            result.pixels[result_index].red =
                static_cast<unsigned char>(ClampColor(static_cast<int>(std::round(sum_red))));
            result.pixels[result_index].green =
                static_cast<unsigned char>(ClampColor(static_cast<int>(std::round(sum_green))));
            result.pixels[result_index].blue =
                static_cast<unsigned char>(ClampColor(static_cast<int>(std::round(sum_blue))));
        }
    }
    return result;
}
