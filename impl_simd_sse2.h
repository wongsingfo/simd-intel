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
};

using ImplSimdSSE2 = ImplSimd<SimdSSE2>;


#endif //SIMD_IMPL_SIMD_SSE2_H
