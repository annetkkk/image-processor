#pragma once
#include "filter.h"

class Negative : public Filter {
public:
    BMP Apply(const BMP& image) const override;
};
