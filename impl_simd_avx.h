//
// Created by Chengke Wong on 2020/5/13.
//

#ifndef SIMD_IMPL_SIMD_AVX_H
#define SIMD_IMPL_SIMD_AVX_H

#include <immintrin.h>
#include <emmintrin.h>

#include "yuv_420.h"
#include "rgb_888.h"
#include "impl_simd.h"


class SimdAVX {

public:

	using Vector = __m256i;

	static constexpr size_t step = 256 / 16;

	inline static Vector constant(short c) {
		return _mm256_set1_epi16(c);
	}

	inline static Vector zero() {
		return _mm256_setzero_si256();
	}

	inline static Vector load(void* addr) {
		__m128i z = _mm_setzero_si128();
		__m128i lo = _mm_unpacklo_epi8(_mm_loadu_si64((uint8_t*) addr), z);
		__m128i hi = _mm_unpacklo_epi8(_mm_loadu_si64((uint8_t*) addr + 8), z);
		return _mm256_loadu2_m128i(&hi, &lo);
	}

	inline static void store(void* addr, Vector value) {
		Vector v = _mm256_packs_epi16(value, zero());
		__m128i lo;
		__m128i hi;
		_mm256_storeu2_m128i(&hi, &lo, v);
		_mm_storel_pd((double*) addr, lo);
		_mm_storel_pd((double*) addr + 1, hi);
	}

	inline static Vector add(const Vector& a, const Vector& b) {
		return _mm256_add_epi16(a, b);
	}

	inline static Vector sub(const Vector& a, const Vector& b) {
		return _mm256_sub_epi16(a, b);
	}

	inline static Vector srai(const Vector& a, int b) {
		return _mm256_srai_epi16(a, b);
	}

	inline static Vector mul(const Vector& a, const Vector& b) {
		return _mm256_mullo_epi16(a, b);
	}
};

using ImplSimdAVX = ImplSimd<SimdAVX>;


#endif //SIMD_IMPL_SIMD_AVX_H
