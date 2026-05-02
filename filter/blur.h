#pragma once
#include "filter.h"

class Blur : public Filter {
public:
    explicit Blur(double sigma) : sigma_(sigma) {
    }
    BMP Apply(const BMP& image) const override;

private:
    double sigma_;
};
