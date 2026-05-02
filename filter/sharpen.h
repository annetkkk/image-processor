#pragma once
#include "filter.h"

class Sharpen : public Filter {
public:
    BMP Apply(const BMP& image) const override;
};
