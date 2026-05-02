#pragma once
#include <vector>
#include <string>
#include <fstream>

struct Pixel {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};

struct BMP {
    unsigned int width;
    unsigned int height;
    std::vector<Pixel> pixels;
};

BMP OpenImage(const std::string& filename);
void WriteImage(const BMP& image, const std::string& filename);
