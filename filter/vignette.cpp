#include "vignette.h"
#include "helpers.h"
#include <cmath>
#include <stdexcept>

Vignette::Vignette(double radius, double intensity) : radius_(radius), intensity_(intensity) {
}
BMP Vignette::Apply(const BMP& image) const {
    if (radius_ < 0.0 || radius_ > 1.0) {
        throw std::runtime_error("Радиус должен быть в диапазоне [0, 1]");
    }
    if (intensity_ < 0.0 || intensity_ > 1.0) {
        throw std::runtime_error("Интенсивность должна быть в диапазоне [0, 1]");
    }

    BMP result;
    result.width = image.width;
    result.height = image.height;
    result.pixels.resize(result.width * result.height);

    const double center_x = static_cast<double>(result.width) / 2.0;
    const double center_y = static_cast<double>(result.height) / 2.0;
    const double max_distance = std::sqrt(center_x * center_x + center_y * center_y);

    for (unsigned int y = 0; y < result.height; ++y) {
        for (unsigned int x = 0; x < result.width; ++x) {
            const double dx = static_cast<double>(x) - center_x;
            const double dy = static_cast<double>(y) - center_y;
            const double distance = std::sqrt(dx * dx + dy * dy);
            const double normalized = distance / max_distance;
            double factor = 1.0;

            if (normalized > radius_) {
                double t = (normalized - radius_) / (1.0 - radius_);
                if (t > 1.0) {
                    t = 1.0;
                }
                factor = 1.0 - intensity_ * t * t;
            }

            const unsigned int index = y * result.width + x;
            const Pixel& p = image.pixels[index];

            const int red = ClampColor(static_cast<int>(p.red * factor));
            const int green = ClampColor(static_cast<int>(p.green * factor));
            const int blue = ClampColor(static_cast<int>(p.blue * factor));

            result.pixels[index].red = static_cast<unsigned char>(red);
            result.pixels[index].green = static_cast<unsigned char>(green);
            result.pixels[index].blue = static_cast<unsigned char>(blue);
        }
    }

    return result;
}
