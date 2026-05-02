#pragma once
#include "filter.h"

class Vignette : public Filter {
public:
    Vignette(double radius, double intensity);
    BMP Apply(const BMP& image) const override;

private:
    double radius_;
    double intensity_;
};
