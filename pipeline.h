#pragma once

#include "arg_parser.h"
#include "bmp.h"
#include "filter/filter.h"

#include <memory>
#include <vector>

class Pipeline {
public:
    explicit Pipeline(const std::vector<FilterArgs>& filter_args);
    BMP Run(const BMP& image) const;

private:
    std::vector<std::unique_ptr<Filter>> filters_;
};
