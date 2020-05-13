//
// Created by Chengke Wong on 2020/5/12.
//

#ifndef SIMD_IMPL_SIMD_MMX_H
#define SIMD_IMPL_SIMD_MMX_H

#include <mmintrin.h>

#include "yuv_420.h"
#include "rgb_888.h"
#include "impl_simd.h"


class SimdMMX {

public:

	using Vector = __m64;

	static constexpr size_t step = 64 / 16;

	inline static Vector constant(int c) {
		return _mm_set1_pi16(c);
	}

	inline static Vector zero() {
		return _mm_setzero_si64();
	}

	inline static Vector load(void* addr) {
		int d = *(int*)addr;
		Vector result = _mm_cvtsi32_si64(d);
		result = _mm_unpacklo_pi8(result, zero());
		return result;
	}

	inline static void store(void* addr, Vector value) {
		int v = _m_to_int(_mm_packs_pu16(value, zero()));
		*(int*) addr = v;
	}

	inline static Vector add(const Vector& a, const Vector& b) {
		return _mm_add_pi16(a, b);
	}

	inline static Vector sub(const Vector& a, const Vector& b) {
		return _mm_sub_pi16(a, b);
	}

	inline static Vector srai(const Vector& a, int b) {
		return _mm_srai_pi16(a, b);
	}

	inline static Vector mul(const Vector& a, const Vector& b) {
		return _mm_mullo_pi16(a, b);
	}
};

using ImplSimdMMX = ImplSimd<SimdMMX>;


#endif //SIMD_IMPL_SIMD_MMX_H
