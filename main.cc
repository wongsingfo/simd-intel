//
// Created by Chengke Wong on 2020/5/11.
//

#include <iostream>
#include "yuv_420.h"
#include "rgb_888.h"
#include "impl_general.h"
#include "impl_simd_mmx.h"
#include "impl_simd_sse2.h"
#include "impl_simd_avx.h"
#include "stopwatch.h"

template <typename Impl>
void do_work(Impl impl) {
    Stopwatch stopwatch;
	YUV420 image1;
    image1.read_from_yuv("dem1.yuv");
    YUV420 output = impl.AlphaBlending(image1, 128);
    // output.write_to_yuv("output.yuv");

    image1.free();
    output.free();

    std::cout << stopwatch.getElapsedInMicroseconds() / 1000 << " ms " << std::endl;
}

int main() {
    try {
        
        do_work(ImplGeneral());
        do_work(ImplSimdMMX());
        do_work(ImplSimdSSE2());
        do_work(ImplSimdAVX());


    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Error: " << strerror(errno);
    }

    return 0;
}
