#include <iostream>
#include "yuv_420.h"

int main() {
    try {
        YUV420 image1(1920, 1080);
        image1.read_from_file("dem1.yuv");

    } catch (const std::system_error& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Error: " << strerror(errno);
    }
    return 0;
}
