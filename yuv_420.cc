//
// Created by Chengke Wong on 2020/5/11.
//

#include <fstream>
#include <iostream>
#include "yuv_420.h"
#include "config.h"

YUV420::YUV420()
    : filename_("unknown"),
      y_(new uint8_t[kSize]),
      u_(new uint8_t[kSize]),
      v_(new uint8_t[kSize]) {}

void YUV420::read_from_yuv(const std::string &filename) {
    filename_ = filename;

    std::ifstream stream;

    stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    stream.open(filename, std::ifstream::binary);

    stream.seekg(0, stream.end);
    int length = stream.tellg();
    stream.seekg(0, stream.beg);

    stream.read((char*) y_, kSize);
    read_from_yuv4(stream, u_);
    read_from_yuv4(stream, v_);
}

void YUV420::read_from_yuv4(std::istream &stream, uint8_t *data) {
    for (int i = 0; i < kHeight; i += 2) {
        int offset = i * kWidth;
        for (int j = 0; j < kWidth; j += 2) {
            uint8_t c;
            stream.read((char*) &c, 1);
            data[offset + j] = c;
            data[offset + j + 1] = c;
            data[offset + j + kWidth] = c;
            data[offset + j + kWidth + 1] = c;
        }
    }
}

void YUV420::free() {
    delete[] y_;
    delete[] u_;
    delete[] v_;
}

void YUV420::write_to_yuv(const std::string &filename) {
    std::ofstream stream;

    stream.exceptions(std::ofstream::failbit | std::ofstream::badbit);

    stream.open(filename, std::ofstream::binary);

    stream.write((char*) y_, kSize);

    write_to_yuv4(stream, u_);

    write_to_yuv4(stream, v_);
}

void YUV420::write_to_yuv4(std::ostream &stream, uint8_t *data) {
    for (int i = 0; i < kHeight; i += 2) {
        int offset = i * kWidth;
        for (int j = 0; j < kWidth; j += 2) {
            char c = data[offset + j];
            stream.write((char*) &c, 1);
        }
    }
}

