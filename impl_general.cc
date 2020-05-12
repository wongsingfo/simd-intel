//
// Created by Chengke Wong on 2020/5/11.
//

#include "impl_general.h"

RGB888 ImplGeneral::YUV2RGB(YUV420 image) {
    RGB888 result;

    for (int i = 0; i < kSize; i++) {
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

YUV420 ImplGeneral::AlphaBlending(YUV420 image, uint8_t alpha) {
    YUV420 result;

    for (int i = 0; i < kSize; i++) {
        int c = image.y_[i] - 16;
        int d = image.u_[i] - 128;
        int e = image.v_[i] - 128;

        int r = clamp((298 * c + 409 * e + 128) >> 8);
        int g = clamp((298 * c - 100 * d - 208 * e + 128) >> 8);
        int b = clamp((298 * c + 516 * d + 128) >> 8);

        r = (r * alpha) >> 8;
        g = (g * alpha) >> 8;
        b = (b * alpha) >> 8;

        result.y_[i] = clamp(((66 * r + 129 * g + 25 * b + 128) >> 8) + 16);
        result.u_[i] = clamp(((-38 * r - 74 * g + 112 * b + 128) >> 8) + 128);
        result.v_[i] = clamp(((112 * r - 94 * g - 18 * b + 128) >> 8) + 128);
    }

    return result;
}
