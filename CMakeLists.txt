cmake_minimum_required(VERSION 3.16)

project(image_processor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(image_processor
        image_processor.cpp
        arg_parser.cpp
        bmp.cpp
        filter/crop.cpp
        filter/negative.cpp
        filter/grayscale.cpp
        filter/sharpen.cpp
        filter/edge.cpp
        filter/blur.cpp
        filter/vignette.cpp
        pipeline.cpp
        helpers.h
)

target_include_directories(image_processor PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
