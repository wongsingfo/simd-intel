//
// Created by Chengke Wong on 2020/5/11.
//

#ifndef SIMD_RGB_888_H
#define SIMD_RGB_888_H

#include <cstdint>
#include <string>
#include <memory>


class RGB888 {

public:

    RGB888(size_t width, size_t height);

    ~RGB888();

    void write_to_ppm(const std::string& filename);

private:

	std::string filename_;

    size_t width_;

    size_t height_;

    size_t size_;

    uint8_t *r_;

    uint8_t *g_;

    uint8_t *b_;

};


#endif //SIMD_RGB_888_H
