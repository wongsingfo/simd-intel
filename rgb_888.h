//
// Created by Chengke Wong on 2020/5/11.
//

#ifndef SIMD_RGB_888_H
#define SIMD_RGB_888_H

#include <cstdint>
#include <string>
#include <memory>

#include "config.h"

class RGB888 {

public:

    RGB888();

    void free();

    void write_to_ppm(const std::string& filename);

	std::string filename_;

    uint8_t *r_;

    uint8_t *g_;

    uint8_t *b_;

};


#endif //SIMD_RGB_888_H
