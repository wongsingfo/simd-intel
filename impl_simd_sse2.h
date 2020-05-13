//
// Created by Chengke Wong on 2020/5/13.
//

#ifndef SIMD_IMPL_SIMD_SSE2_H
#define SIMD_IMPL_SIMD_SSE2_H

#include <immintrin.h>
#include <emmintrin.h>

#include "yuv_420.h"
#include "rgb_888.h"
#include "impl_simd.h"


class SimdSSE2 {

public:

	using Vector = __m128i;

	static constexpr size_t step = 128 / 16;

	inline static Vector constant(short c) {
		return _mm_set1_epi16(c);
	}

	inline static Vector zero() {
		return _mm_setzero_si128();
	}

	inline static Vector load(void* addr) {
		Vector result = _mm_loadu_si64(addr);
		return _mm_unpacklo_epi8(result, zero());
	}

	inline static void store(void* addr, Vector value) {
		Vector v = _mm_packs_epi16(value, zero());
		_mm_storel_pd((double*) addr, v);
	}

	inline static Vector add(const Vector& a, const Vector& b) {
		return _mm_add_epi16(a, b);
	}

	inline static Vector sub(const Vector& a, const Vector& b) {
		return _mm_sub_epi16(a, b);
	}

	inline static Vector srai(const Vector& a, int b) {
		return _mm_srai_epi16(a, b);
	}

	inline static Vector mul(const Vector& a, const Vector& b) {
		return _mm_mullo_epi16(a, b);
	}

	static YUV420 AlphaBlending(YUV420 image, uint8_t alpha) {
        YUV420 result;

        Vector c16 = _mm_set1_epi16(16);
        Vector c128 = _mm_set1_epi16(128);
        Vector calpha = _mm_set1_epi16(alpha);
        Vector zero = _mm_setzero_si128();

        for (int i = 0; i < kSize; i += step) {
            Vector tmp = _mm_loadu_si64((void*) &image.y_[i]);
            Vector x = _mm_unpacklo_epi8(tmp, zero);
            x = _mm_add_epi16(_mm_srai_epi16(_mm_mullo_epi16(calpha, _mm_sub_epi16(x, c16)), 8), c16);
            tmp = _mm_packs_epi16(x, zero);
			_mm_storel_pd((double*) &result.y_[i], tmp);
        }

        for (int i = 0; i < kSize; i += step) {
            Vector tmp = _mm_loadu_si64((void*) &image.u_[i]);
            Vector x = _mm_unpacklo_epi8(tmp, zero);
            x = _mm_add_epi16(_mm_srai_epi16(_mm_mullo_epi16(calpha, _mm_sub_epi16(x, c128)), 8), c128);
            tmp = _mm_packs_epi16(x, zero);
			_mm_storel_pd((double*) &result.u_[i], tmp);
        }

        for (int i = 0; i < kSize; i += step) {
            Vector tmp = _mm_loadu_si64((void*) &image.v_[i]);
            Vector x = _mm_unpacklo_epi8(tmp, zero);
            x = _mm_add_epi16(_mm_srai_epi16(_mm_mullo_epi16(calpha, _mm_sub_epi16(x, c128)), 8), c128);
            tmp = _mm_packs_epi16(x, zero);
			_mm_storel_pd((double*) &result.v_[i], tmp);
        }

        return result;
    }
};

using ImplSimdSSE2 = SimdSSE2;


#endif //SIMD_IMPL_SIMD_SSE2_H
