#pragma once
#include "bmp.h"

class Filter {
public:
    virtual ~Filter() = default;
    virtual BMP Apply(const BMP& image) const = 0;
};
