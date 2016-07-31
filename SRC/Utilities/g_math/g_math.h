#pragma once

#include <cmath>
#include "g_vector.h"
#include "g_angle.h"
#include "g_color.h"

class g_math
{
public:
	template <typename T>
	static T Clamp(const T& iVal, const T& iMin, const T& iMax)
	{
		if (iVal > iMax)
			return iMax;
		if (iVal < iMin)
			return iMin;

		return iVal;
	}

	static float Floor(const float f)
	{
		__m128 mm1 = _mm_set_ss(f);

		__m128 mm2 = _mm_round_ps(mm1, _MM_FROUND_FLOOR);

		return _mm_cvtss_f32(mm2);
	}

	static float Ceil(const float f)
	{
		__m128 mm1 = _mm_set_ss(f);

		__m128 mm2 = _mm_round_ps(mm1, _MM_FROUND_CEIL);

		return _mm_cvtss_f32(mm2);
	}

	static float Trunc(const float f)
	{
		__m128 mm1 = _mm_set_ss(f);

		__m128 mm2 = _mm_round_ps(mm1, _MM_FROUND_TRUNC);

		return _mm_cvtss_f32(mm2);
	}

	static float Round(const float f)
	{
		__m128 mm1 = _mm_set_ss(f);

		__m128 mm2 = _mm_round_ps(mm1, _MM_FROUND_NINT);

		return _mm_cvtss_f32(mm2);
	}

	static float Rad2Deg(float x);
	static float Deg2Rad(float x);
	static void SinCos(float x, float& s, float& c);

	static void AngleVectors(const Angle& angles, Vector* forward);
	static void AngleVectors(const Angle& angles, Vector* forward, Vector* right, Vector* up);
	void AngleVectors(const Angle& angles, float* forward, float* right, float* up) const;
	static void VectorAngles(Vector& forward, Angle& angles);
	static float DotProduct(const Vector& v1, const Vector& v2);
	static void Transform(const Vector& vSome, const Matrix3x4& vMatrix, Vector& vOut);
};