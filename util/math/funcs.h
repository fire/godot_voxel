#ifndef VOXEL_MATH_FUNCS_H
#define VOXEL_MATH_FUNCS_H

#include <core/math/vector3.h>
#include "core/math/math_funcs.h"

template <typename T>
inline T min(const T a, const T b) {
	return a < b ? a : b;
}

template <typename T>
inline T max(const T a, const T b) {
	return a > b ? a : b;
}

template <typename T>
inline T min(const T a, const T b, const T c, const T d) {
	return min(min(a, b), min(c, d));
}

template <typename T>
inline T max(const T a, const T b, const T c, const T d) {
	return max(max(a, b), max(c, d));
}

template <typename T>
inline T min(const T a, const T b, const T c, const T d, const T e, const T f) {
	return min(min(min(a, b), min(c, d)), min(e, f));
}

template <typename T>
inline T max(const T a, const T b, const T c, const T d, const T e, const T f) {
	return max(max(max(a, b), max(c, d)), max(e, f));
}

template <typename T>
inline T min(const T a, const T b, const T c, const T d, const T e, const T f, const T g, const T h) {
	return min(min(a, b, c, d), min(e, f, g, h));
}

template <typename T>
inline T max(const T a, const T b, const T c, const T d, const T e, const T f, const T g, const T h) {
	return max(max(a, b, c, d), max(e, f, g, h));
}

template <typename T>
inline T clamp(const T x, const T min_value, const T max_value) {
	// TODO Clang can optimize a min/max implementation. Worth changing to that?
	if (x < min_value) {
		return min_value;
	}
	if (x >= max_value) {
		return max_value;
	}
	return x;
}

template <typename T>
inline T squared(const T x) {
	return x * x;
}

template <typename T>
inline void sort_min_max(T &a, T &b) {
	if (a > b) {
		T temp = a;
		a = b;
		b = temp;
	}
}

// TODO Rename udiv => floordiv

// Performs euclidean division, aka floored division.
// This implementation expects a strictly positive divisor.
//
//    x   | `/` | udiv
// ----------------------
//    -6  | -2  | -2
//    -5  | -1  | -2
//    -4  | -1  | -2
//    -3  | -1  | -1
//    -2  | 0   | -1
//    -1  | 0   | -1
//    0   | 0   | 0
//    1   | 0   | 0
//    2   | 0   | 0
//    3   | 1   | 1
//    4   | 1   | 1
//    5   | 1   | 1
//    6   | 2   | 2
static inline int udiv(int x, int d) {
#ifdef DEBUG_ENABLED
	CRASH_COND(d < 0);
#endif
	if (x < 0) {
		return (x - d + 1) / d;
	} else {
		return x / d;
	}
}

// Math::wrapf with zero min
inline float wrapf(float x, float d) {
	return Math::is_zero_approx(d) ? 0.f : x - (d * Math::floor(x / d));
}

// Similar to Math::smoothstep but doesn't use macro to clamp
inline float smoothstep(float p_from, float p_to, float p_weight) {
	if (Math::is_equal_approx(p_from, p_to)) {
		return p_from;
	}
	float x = clamp((p_weight - p_from) / (p_to - p_from), 0.0f, 1.0f);
	return x * x * (3.0f - 2.0f * x);
}

inline Vector3 fract(const Vector3 &p) {
	return Vector3(Math::fract(p.x), Math::fract(p.y), Math::fract(p.z));
}

#endif // VOXEL_MATH_FUNCS_H
