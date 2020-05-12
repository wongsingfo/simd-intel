//
// Created by Chengke Wong on 2020/5/11.
//

#include "rgb_888.h"

#include <fstream>

void RGB888::write_to_ppm(const std::string &filename) {
    std::ofstream stream;

    stream.exceptions(std::ofstream::failbit | std::ofstream::badbit);

    stream.open(filename, std::ofstream::binary);

    // Binary Portable PixMap
    stream << "P6\n";
    stream << width_ << " " << height_ << " 255\n";

    int begin = stream.tellp();

    for (size_t i = 0; i < size_; i++) {
        stream.put((char) r_[i]);
        stream.put((char) g_[i]);
        stream.put((char) b_[i]);
    }

    int end = stream.tellp();

    assert((end - begin) == size_ * 3);
}

RGB888::RGB888(size_t width, size_t height)
        : filename_("unknown"),
          width_(width),
          height_(height),
          size_(width * height),
          r_(new uint8_t[size_]),
          g_(new uint8_t[size_]),
          b_(new uint8_t[size_]) {}

void RGB888::free() {
    delete[] r_;
    delete[] g_;
    delete[] b_;
}
