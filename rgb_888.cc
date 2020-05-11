//
// Created by Chengke Wong on 2020/5/11.
//

#include "rgb_888.h"

#include <fstream>

void RGB888::write_to_ppm(const std::string& filename) {
	std::ofstream stream;

    stream.exceptions(std::ofstream::failbit | std::ofstream::badbit);

    stream.open(filename, std::ofstream::binary);

    // Binary Portable PixMap
    stream << "P6\n";
    stream << width_ << " " << height_ << "\n";
    stream << "255 ";

    for (size_t i = 0; i < size_; i++) {
    	stream.put((char) r_[i]);
    	stream.put((char) g_[i]);
    	stream.put((char) b_[i]);
    }
}
