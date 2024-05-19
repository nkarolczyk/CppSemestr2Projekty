#include "image.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cmath>

void Image::load(const std::string& filename)
{
    constexpr auto MAGIC = "P6";

    this->filename = filename;

    std::ifstream in(filename, std::ios::binary);
    if (!in)
        throw std::invalid_argument("failed to open \"" + filename + "\"");

    in >> magic;
    if (magic != MAGIC)
        throw std::logic_error("unknown magic number " + magic);

    in >> my_width >> my_height >> color_depth;

    if (!in || my_width < 0 || my_width > 10000 || my_height < 0 || my_height > 10000 || color_depth <= 0 || color_depth > 255)
        throw std::logic_error("invalid image parameter(s): " + std::to_string(my_width) + " " + std::to_string(my_height) + " " + std::to_string(color_depth));
    in.ignore(1);

    pixels.resize(my_height, std::vector<RGB>(my_width));
    for (auto& line : pixels)
    {
        in.read(reinterpret_cast<char*>(line.data()), my_width * sizeof(RGB));
        if (!in)
            throw std::logic_error("failed to read binary pixel data from file " + filename);
    }
}

void Image::save_as(const std::string& filename)
{
    std::ofstream out(filename, std::ios::binary);
    if (!out)
        throw std::invalid_argument("failed to open \"" + filename + "\" for writing");

    out << "P6\n" << my_width << " " << my_height << "\n255\n";

    for (const auto& line : pixels)
    {
        out.write(reinterpret_cast<const char*>(line.data()), my_width * sizeof(RGB));
    }
}

void Image::add_watermark() {
    for (int y = 0; y < my_height; ++y) {
        for (int x = 0; x < my_width; ++x) {
            if (x == y || x == my_width - y - 1) {
                pixels[y][x] = {255, 0, 0};
            }
        }
    }
}

void Image::blurr() {
    std::vector<std::vector<RGB>> temp(my_height, std::vector<RGB>(my_width));

    for (int y = 0; y < my_height; ++y) {
        for (int x = 0; x < my_width; ++x) {
            int sum_red = 0, sum_green = 0, sum_blue = 0;
            int count = 0;

            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    int new_y = y + dy;
                    int new_x = x + dx;

                    if (new_y >= 0 && new_y < my_height && new_x >= 0 && new_x < my_width) {
                        sum_red += pixels[new_y][new_x].red;
                        sum_green += pixels[new_y][new_x].green;
                        sum_blue += pixels[new_y][new_x].blue;
                        ++count;
                    }
                }
            }
            temp[y][x].red = static_cast<unsigned char>(sum_red / count);
            temp[y][x].green = static_cast<unsigned char>(sum_green / count);
            temp[y][x].blue = static_cast<unsigned char>(sum_blue / count);
        }
    }
    pixels = temp;
}


void Image::extract_layer(ColorLayer color_layer) {
    for (int y = 0; y < my_height; ++y) {
        for (int x = 0; x < my_width; ++x) {
            if (color_layer != ColorLayer::Red) {
                pixels[y][x].red = 0;
            }
            if (color_layer != ColorLayer::Green) {
                pixels[y][x].green = 0;
            }
            if (color_layer != ColorLayer::Blue) {
                pixels[y][x].blue = 0;
            }
        }
    }
}

void Image::filter() {
    std::vector<std::vector<RGB>> temp = pixels;
    for (int y = 0; y < my_height - 1; ++y) {
        for (int x = 0; x < my_width - 1; ++x) {
            temp[y][x].red = std::abs(pixels[y][x].red - pixels[y + 1][x + 1].red);
            temp[y][x].green = std::abs(pixels[y][x].green - pixels[y + 1][x + 1].green);
            temp[y][x].blue = std::abs(pixels[y][x].blue - pixels[y + 1][x + 1].blue);
        }
    }
    pixels = temp;
}

void Image::flip_horizontally() {
    for (int y = 0; y < my_height; ++y) {
        for (int x = 0; x < my_width / 2; ++x) {
            std::swap(pixels[y][x], pixels[y][my_width - x - 1]);
        }
    }
}

void Image::flip_vertically() {
    for (int y = 0; y < my_height / 2; ++y) {
        std::swap(pixels[y], pixels[my_height - y - 1]);
    }
}

void Image::inflate() {
    int new_width = my_width * 2;
    int new_height = my_height * 2;
    std::vector<std::vector<RGB>> new_image(new_height, std::vector<RGB>(new_width));

    for (int y = 0; y < my_height; ++y) {
        for (int x = 0; x < my_width; ++x) {
            new_image[2 * y][2 * x] = pixels[y][x];
            new_image[2 * y][2 * x + 1] = pixels[y][x];
            new_image[2 * y + 1][2 * x] = pixels[y][x];
            new_image[2 * y + 1][2 * x + 1] = pixels[y][x];
        }
    }
    pixels = new_image;
    my_width = new_width;
    my_height = new_height;
}

void Image::negative() {
    for (int y = 0; y < my_height; ++y) {
        for (int x = 0; x < my_width; ++x) {
            pixels[y][x].red = 255 - pixels[y][x].red;
            pixels[y][x].green = 255 - pixels[y][x].green;
            pixels[y][x].blue = 255 - pixels[y][x].blue;
        }
    }
}

void Image::rotate_clockwise_90() {
    int new_width = my_height;
    int new_height = my_width;
    std::vector<std::vector<RGB>> new_image(new_height, std::vector<RGB>(new_width));

    for (int y = 0; y < my_height; ++y) {
        for (int x = 0; x < my_width; ++x) {
            new_image[x][my_height - y - 1] = pixels[y][x];
        }
    }
    pixels = new_image;
    my_width = new_width;
    my_height = new_height;
}

void Image::sepia() {
    for (int y = 0; y < my_height; ++y) {
        for (int x = 0; x < my_width; ++x) {
            int r = pixels[y][x].red;
            int g = pixels[y][x].green;
            int b = pixels[y][x].blue;
            int tr = static_cast<int>(0.393 * r + 0.769 * g + 0.189 * b);
            int tg = static_cast<int>(0.349 * r + 0.686 * g + 0.168 * b);
            int tb = static_cast<int>(0.272 * r + 0.534 * g + 0.131 * b);
            pixels[y][x].red = std::min(255, tr);
            pixels[y][x].green = std::min(255, tg);
            pixels[y][x].blue = std::min(255, tb);
        }
    }
}

void Image::shrink() {
    int new_width = my_width / 2;
    int new_height = my_height / 2;
    std::vector<std::vector<RGB>> new_image(new_height, std::vector<RGB>(new_width));

    for (int y = 0; y < new_height; ++y) {
        for (int x = 0; x < new_width; ++x) {
            int r = 0, g = 0, b = 0;
            for (int dy = 0; dy < 2; ++dy) {
                for (int dx = 0; dx < 2; dx++) {
                    r += pixels[y * 2 + dy][x * 2 + dx].red;
                    g += pixels[y * 2 + dy][x * 2 + dx].green;
                    b += pixels[y * 2 + dy][x * 2 + dx].blue;
                }
            }
            new_image[y][x].red = r / 4;
            new_image[y][x].green = g / 4;
            new_image[y][x].blue = b / 4;
        }
    }
    pixels = new_image;
    my_width = new_width;
    my_height = new_height;
}

void Image::to_grayscale() {
    for (int y = 0; y < my_height; ++y) {
        for (int x = 0; x < my_width; ++x) {
            unsigned char gray = static_cast<unsigned char>((pixels[y][x].red + pixels[y][x].green + pixels[y][x].blue) / 3);
            pixels[y][x].red = gray;
            pixels[y][x].green = gray;
            pixels[y][x].blue = gray;
        }
    }
}

int Image::height() const {
    return my_height;
}

int Image::width() const {
    return my_width;
}
