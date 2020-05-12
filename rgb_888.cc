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
    stream << kWidth << " " << kHeight << " 255\n";

    int begin = stream.tellp();

    for (size_t i = 0; i < kSize; i++) {
        stream.put((char) r_[i]);
        stream.put((char) g_[i]);
        stream.put((char) b_[i]);
    }

    int end = stream.tellp();

    assert((end - begin) == kSize * 3);
}

RGB888::RGB888()
        : filename_("unknown"),
          r_(new uint8_t[kSize]),
          g_(new uint8_t[kSize]),
          b_(new uint8_t[kSize]) {}

void RGB888::free() {
    delete[] r_;
    delete[] g_;
    delete[] b_;
}
