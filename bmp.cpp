#include "bmp.h"
#include <fstream>
#include <stdexcept>
#include <cstdint>

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t signature;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t data_offset;
};

struct BMPInfoHeader {
    uint32_t header_size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t image_size;
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t colors_used;
    uint32_t important_colors;
};
#pragma pack(pop)
BMP OpenImage(const std::string& filename) {
    const int bits = 24;
    const int bmp = 0x4D42;
    const int header = 40;
    const int bits2 = 14;

    if (sizeof(BMPFileHeader) != bits2 || sizeof(BMPInfoHeader) != header) {
        throw std::runtime_error("Неправильные размеры заголовков");
    }

    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для чтения");
    }

    BMPFileHeader file_header{};
    file.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));

    if (file_header.signature != bmp) {
        throw std::runtime_error("Неверный формат файла");
    }

    BMPInfoHeader info_header{};
    file.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    if (info_header.width <= 0 || info_header.height <= 0) {
        throw std::runtime_error("Некорректные размеры изображения");
    }

    if (info_header.bits_per_pixel != bits) {
        throw std::runtime_error(" Поддерживается только 24-битный BMP");
    }

    if (info_header.compression != 0) {
        throw std::runtime_error("Поддерживается только несжатый BMP");
    }

    BMP image;
    image.width = info_header.width;
    image.height = info_header.height;
    image.pixels.resize(image.width * image.height);

    file.seekg(file_header.data_offset, std::ios::beg);
    auto padding = (4 - (image.width * 3) % 4) % 4;

    for (unsigned int file_row = 0; file_row < image.height; file_row++) {
        unsigned int image_y = image.height - file_row - 1;
        for (unsigned int x = 0; x < image.width; x++) {
            Pixel pixel;
            file.read(reinterpret_cast<char*>(&pixel), sizeof(Pixel));
            unsigned int index = image_y * image.width + x;
            image.pixels[index] = pixel;
        }
        file.ignore(padding);
    }

    return image;
}

void WriteImage(const BMP& image, const std::string& filename) {
    const int bits = 24;
    const int header = 40;
    const uint16_t bmp_signature = 0x4D42;

    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для записи");
    }

    auto padding = (4 - (image.width * 3) % 4) % 4;
    auto image_size = (image.width * 3 + padding) * image.height;

    BMPFileHeader file_header{};
    file_header.signature = bmp_signature;
    file_header.data_offset = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
    file_header.file_size = file_header.data_offset + image_size;
    file_header.reserved1 = 0;
    file_header.reserved2 = 0;

    file.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));

    BMPInfoHeader info_header{};
    info_header.header_size = header;
    info_header.width = static_cast<int32_t>(image.width);
    info_header.height = static_cast<int32_t>(image.height);
    info_header.planes = 1;
    info_header.bits_per_pixel = bits;
    info_header.compression = 0;
    info_header.image_size = image_size;
    info_header.x_pixels_per_meter = 0;
    info_header.y_pixels_per_meter = 0;
    info_header.colors_used = 0;
    info_header.important_colors = 0;

    file.write(reinterpret_cast<const char*>(&info_header), sizeof(info_header));

    for (unsigned int file_row = 0; file_row < image.height; file_row++) {
        unsigned int image_y = image.height - file_row - 1;
        for (unsigned int x = 0; x < image.width; x++) {
            unsigned int index = image_y * image.width + x;
            const Pixel& pixel = image.pixels[index];
            file.write(reinterpret_cast<const char*>(&pixel), sizeof(Pixel));
        }
        for (unsigned int k = 0; k < padding; k++) {
            file.put(0);
        }
    }
}
