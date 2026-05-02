#include "arg_parser.h"
#include "bmp.h"
#include "pipeline.h"

#include <iostream>
#include <stdexcept>

int main(int argc, char** argv) {
    try {
        ImageProcessorArgs args = ExtractImageProcessorArgs(argc, argv);
        BMP image = OpenImage(args.input_file);

        Pipeline pipeline(args.filters);
        BMP result = pipeline.Run(image);

        WriteImage(result, args.output_file);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
