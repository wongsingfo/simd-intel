//
// Created by Chengke Wong on 2020/5/12.
//

#ifndef SIMD_IMPL_SIMD_H
#define SIMD_IMPL_SIMD_H

#include "yuv_420.h"
#include "rgb_888.h"

template <typename SIMD>
class ImplSimd {

public:

    using Vector = typename SIMD::Vector;

    // image1 * alpha
    static YUV420 AlphaBlending(YUV420 image, uint8_t alpha) {
        YUV420 result;

        Vector c16 = SIMD::constant(16);
        Vector c128 = SIMD::constant(128);
        Vector calpha = SIMD::constant(alpha);

        for (int i = 0; i < kSize; i += SIMD::step) {
            Vector x = SIMD::load(&image.y_[i]);
            x = SIMD::add(SIMD::srai(SIMD::mul(calpha, SIMD::sub(x, c16)), 8), c16);
            SIMD::store(&result.y_[i], x);
        }

        for (int i = 0; i < kSize; i += SIMD::step) {
            Vector x = SIMD::load(&image.u_[i]);
            x = SIMD::add(SIMD::srai(SIMD::mul(calpha, SIMD::sub(x, c128)), 8), c128);
            SIMD::store(&result.u_[i], x);
        }

        for (int i = 0; i < kSize; i += SIMD::step) {
            Vector x = SIMD::load(&image.v_[i]);
            x = SIMD::add(SIMD::srai(SIMD::mul(calpha, SIMD::sub(x, c128)), 8), c128);
            SIMD::store(&result.v_[i], x);
        }

        return result;
    }


};


#endif //SIMD_IMPL_SIMD_H
