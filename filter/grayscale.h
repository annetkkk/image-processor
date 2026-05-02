#pragma once
#include "filter.h"

class Grayscale : public Filter {
public:
    BMP Apply(const BMP& image) const override;
};
