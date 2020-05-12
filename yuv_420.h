//
// Created by Chengke Wong on 2020/5/11.
//

#ifndef SIMD_YUV_420_H
#define SIMD_YUV_420_H

#include <string>
#include <memory>

class YUV420 {

public:

    YUV420(size_t width, size_t height);

    void read_from_file(const std::string& filename);

    void free();

	std::string filename_;

    size_t width_;

    size_t height_;

    size_t size_;

    uint8_t *y_;

    uint8_t *u_;

    uint8_t *v_;

};


#endif //SIMD_YUV_420_H
