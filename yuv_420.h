//
// Created by Chengke Wong on 2020/5/11.
//

#ifndef SIMD_YUV_420_H
#define SIMD_YUV_420_H

#include <string>
#include <memory>
#include <istream>

class YUV420 {

public:

    YUV420();

    void read_from_yuv(const std::string& filename);

    void write_to_yuv(const std::string& filename);

    void free();

	std::string filename_;

    size_t width_;

    size_t height_;

    size_t size_;

    uint8_t *y_;

    uint8_t *u_;

    uint8_t *v_;

private:

    void read_from_yuv4(std::istream &stream, uint8_t *data);

    void write_to_yuv4(std::ostream &stream, uint8_t *data);

};


#endif //SIMD_YUV_420_H
