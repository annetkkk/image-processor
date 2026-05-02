#pragma once
#include "filter.h"

class Edge : public Filter {
public:
    explicit Edge(double threshold) : threshold_(threshold) {
    }
    BMP Apply(const BMP& image) const override;

private:
    double threshold_;
};
