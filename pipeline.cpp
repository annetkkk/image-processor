#include "pipeline.h"

#include "filter/blur.h"
#include "filter/crop.h"
#include "filter/edge.h"
#include "filter/grayscale.h"
#include "filter/negative.h"
#include "filter/sharpen.h"
#include "filter/vignette.h"

#include <memory>
#include <stdexcept>
#include <string>

namespace {

std::unique_ptr<Filter> CreateFilter(const FilterArgs& filter_args) {
    if (filter_args.filter_name == "-crop") {
        unsigned int width = std::stoul(filter_args.filter_args[0]);
        unsigned int height = std::stoul(filter_args.filter_args[1]);
        return std::make_unique<Crop>(width, height);
    }

    if (filter_args.filter_name == "-neg") {
        return std::make_unique<Negative>();
    }

    if (filter_args.filter_name == "-gs") {
        return std::make_unique<Grayscale>();
    }

    if (filter_args.filter_name == "-sharp") {
        return std::make_unique<Sharpen>();
    }

    if (filter_args.filter_name == "-edge") {
        double threshold = std::stod(filter_args.filter_args[0]);
        return std::make_unique<Edge>(threshold);
    }

    if (filter_args.filter_name == "-blur") {
        double sigma = std::stod(filter_args.filter_args[0]);
        return std::make_unique<Blur>(sigma);
    }

    if (filter_args.filter_name == "-vignette") {
        double radius = std::stod(filter_args.filter_args[0]);
        double intensity = std::stod(filter_args.filter_args[1]);
        return std::make_unique<Vignette>(radius, intensity);
    }

    throw std::runtime_error("Неизвестный фильтр: " + filter_args.filter_name);
}

}  // namespace

Pipeline::Pipeline(const std::vector<FilterArgs>& filter_args) {
    for (const FilterArgs& filter_arg : filter_args) {
        filters_.push_back(CreateFilter(filter_arg));
    }
}

BMP Pipeline::Run(const BMP& image) const {
    BMP result = image;

    for (const std::unique_ptr<Filter>& filter : filters_) {
        result = filter->Apply(result);
    }

    return result;
}
