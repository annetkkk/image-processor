#include "arg_parser.h"
#include <stdexcept>

ImageProcessorArgs ExtractImageProcessorArgs(int argc, char** argv) {
    ImageProcessorArgs args;

    if (argc < 3) {
        throw std::runtime_error("Неверное количество аргументов");
    }

    args.input_file = std::string(argv[1]);
    args.output_file = std::string(argv[2]);

    int i = 3;
    while (i < argc) {
        std::string filter_name = argv[i];
        FilterArgs filter;
        filter.filter_name = filter_name;

        if (filter_name == "-neg") {
            ++i;
        } else if (filter_name == "-crop") {
            if (i + 2 >= argc) {
                throw std::runtime_error("Недостаточно аргументов для фильтра crop");
            }

            filter.filter_args.push_back(argv[i + 1]);
            filter.filter_args.push_back(argv[i + 2]);

            i += 3;
        } else if (filter_name == "-gs") {
            ++i;
        } else if (filter_name == "-sharp") {
            ++i;
        } else if (filter_name == "-edge") {
            if (i + 1 >= argc) {
                throw std::runtime_error("Недостаточно аргументов для фильтра edge");
            }
            filter.filter_args.push_back(argv[i + 1]);
            i += 2;
        } else if (filter_name == "-blur") {
            if (i + 1 >= argc) {
                throw std::runtime_error("Недостаточно аргументов для фильтра blur");
            }
            filter.filter_args.push_back(argv[i + 1]);
            i += 2;
        } else if (filter_name == "-vignette") {
            if (i + 2 >= argc) {
                throw std::runtime_error("Недостаточно аргументов для фильтра vignette");
            }
            filter.filter_args.push_back(argv[i + 1]);
            filter.filter_args.push_back(argv[i + 2]);
            i += 3;
        } else {
            throw std::runtime_error("Неизвестный фильтр: " + filter_name);
        }

        args.filters.push_back(filter);
    }
    return args;
}
