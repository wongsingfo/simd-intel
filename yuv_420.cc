//
// Created by Chengke Wong on 2020/5/11.
//

#include <fstream>
#include <iostream>
#include "yuv_420.h"

YUV420::YUV420(size_t width, size_t height)
        : filename_("unknown"), width_(width), height_(height),
          size_(width * height), 
          y_(new uint8_t[size_]),
          u_(new uint8_t[size_]),
          v_(new uint8_t[size_]) {}

void YUV420::read_from_file(const std::string &filename) {
    filename_ = filename;

    std::ifstream stream;

    stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    stream.open(filename, std::ifstream::binary);

    stream.seekg(0, stream.end);
    int length = stream.tellg();
    stream.seekg(0, stream.beg);

    assert(length % 36 == 0);

    assert(length / 36 * 24 == size_);

/*
 * Y1  Y2  Y3  Y4  Y5  Y6
 * Y7  Y8  Y9  Y10 Y11 Y12
 * Y13 Y14 Y15 Y16 Y17 Y18
 * Y19 Y29 Y21 Y22 Y23 Y24
 * U1  U2  U3  U4  U5  U6
 * V1  V2  V3  V4  V5  V6
 */
    static constexpr int Y2UV[24] =
            {1, 1, 2, 2, 3, 3,
             1, 1, 2, 2, 3, 3,
             4, 4, 5, 5, 6, 6,
             4, 4, 5, 5, 6, 6};

    uint8_t buffer[36];

    uint8_t *current_y = y_;
    uint8_t *current_u = u_;
    uint8_t *current_v = v_;

    size_t num_of_block = length / 36;

    for (int i = 0; i < num_of_block; i++) {
        stream.read((char *) buffer, 36);

        uint8_t *U = buffer + 24;
        uint8_t *V = buffer + 30;

        for (int j = 0; j < 24; j++) {
            int k = Y2UV[j] - 1;
            *(current_y) = buffer[j];
            *(current_u) = U[k];
            *(current_v) = V[k];

            current_y += 1;
            current_u += 1;
            current_v += 1;
        }
    }

}

void YUV420::free() {
    delete[] y_;
    delete[] u_;
    delete[] v_;
}
