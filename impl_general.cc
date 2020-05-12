//
// Created by Chengke Wong on 2020/5/11.
//

#include "impl_general.h"

RGB888 ImplGeneral::YUV2RGB(YUV420 image) {
    RGB888 result(image.width_, image.height_);

    int size = image.size_;

    for (int i = 0; i < size; i++) {
        int c = image.y_[i] - 16;
        int d = image.u_[i] - 128;
        int e = image.v_[i] - 128;
        result.r_[i] = clamp((298 * c + 409 * e + 128) >> 8);
        result.g_[i] = clamp((298 * c - 100 * d - 208 * e + 128) >> 8);
        result.b_[i] = clamp((298 * c + 516 * d + 128) >> 8);
    }

    return result;
}

uint8_t ImplGeneral::clamp(int x) {
    if (x < 0) {
        x = 0;
    }
    if (x > 255) {
        x = 255;
    }
    return x;
}
