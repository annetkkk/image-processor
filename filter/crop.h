#pragma once
#include "filter.h"

class Crop : public Filter {
public:
    Crop(unsigned int widht, unsigned int height) : width_(widht), height_(height) {
    }
    BMP Apply(const BMP& image) const override;

private:
    unsigned int width_;
    unsigned int height_;
};
