//
// Created by Chengke Wong on 2020/5/11.
//

#ifndef SIMD_IMPL_GENERAL_H
#define SIMD_IMPL_GENERAL_H

#include "yuv_420.h"
#include "rgb_888.h"

class ImplGeneral {

public:

    static RGB888 YUV2RGB(YUV420 image);

    // image1 * alpha
    static YUV420 AlphaBlending(YUV420 image, uint8_t alpha);

private:

    static uint8_t clamp(int x);

};


#endif //SIMD_IMPL_GENERAL_H
