//
// Created by Chengke Wong on 2020/5/11.
//

#include <iostream>
#include "yuv_420.h"
#include "rgb_888.h"
#include "impl_general.h"

template <typename Impl>
void do_work(Impl impl) {
	YUV420 image1;
    image1.read_from_yuv("dem1.yuv");
    RGB888 output = impl.YUV2RGB(image1);
    output.write_to_ppm("output.ppm");

    image1.free();
    output.free();
}

int main() {
    try {
        
        do_work(ImplGeneral());

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Error: " << strerror(errno);
    }

    return 0;
}
