#include "../../sdk.h"

float g_math::Rad2Deg(float x)
{
	return (x * (180.0f / M_PI));
}

float g_math::Deg2Rad(float x)
{
	return (x * (M_PI / 180.0f));
}

float g_math::Sin(float f)
{
	static const float A = 7.57424729353990669582E-03f;
	static const float B = -1.65827042313329378398E-01f;
	static const float C = 9.99771407817154332926E-01f;

	int k;
	float f2;

	/* find offset of f from the range -pi/2 to pi/2 */
	k = static_cast<int>(Round(f * M_INVPI));

	/* bring f into range */
	f -= k * M_PI;

	/* calculate sine */
	f2 = f * f;
	f = f * (C + f2 * (B + A * f2));

	/* if f is in an odd pi count we must flip */
	if (k % 2)
		f = -f;

	return f;
}

float g_math::Cos(float f)
{
	static const float A = 3.72093273724652635657E-02f;
	static const float B = -4.96392330120080597572E-01f;
	static const float C = 9.99579515069196269871E-01f;

	int k;
	float f2;

	/* find offset of f from the range -pi/2 to pi/2 */
	k = static_cast<int>(Round(f * M_INVPI));

	/* bring f into range */
	f -= k * M_PI;

	/* calculate cosine */
	f2 = f * f;
	f = C + f2 * (B + (A * f2));

	/* if f is in an odd pi count we must flip */
	if (k % 2)
		f = -f;

	return f;
}

float g_math::Tan(float f)
{
	static const float SA = 7.57424729353990669582E-03f;
	static const float SB = -1.65827042313329378398E-01f;
	static const float SC = 9.99771407817154332926E-01f;

	static const float CA = 3.72093273724652635657E-02f;
	static const float CB = -4.96392330120080597572E-01f;
	static const float CC = 9.99579515069196269871E-01f;

	int k;
	float f2;

	/* find offset of f from the range -pi/2 to pi/2 */
	k = static_cast<int>(Round(f * M_INVPI));

	/* bring f into range */
	f -= k * M_PI;

	/* calculate sine and cosine*/
	f2 = f * f;

	float s = f * (SC + f2 * (SB + SA * f2));
	float c = CC + f2 * (CB + (CA * f2));

	/* if f is in an odd pi count we must flip */
	if (k % 2) {
		s = -s;
		c = -c;
	}

	return s / c;
}

float g_math::Sqrt(const float f)
{
	__m128 mm1 = _mm_set_ss(f);
	__m128 mm2 = _mm_sqrt_ss(mm1);
	return _mm_cvtss_f32(mm2);
}

float g_math::InvSqrt(float x)
{
	return 1.0f / Sqrt(x);
}

void g_math::SinCos(float f, float& s, float& c)
{
	static const float SA = 7.57424729353990669582E-03f;
	static const float SB = -1.65827042313329378398E-01f;
	static const float SC = 9.99771407817154332926E-01f;

	static const float CA = 3.72093273724652635657E-02f;
	static const float CB = -4.96392330120080597572E-01f;
	static const float CC = 9.99579515069196269871E-01f;

	int k;
	float f2;

	/* find offset of f from the range -pi/2 to pi/2 */
	k = static_cast<int>(Round(f * M_PI));

	/* bring f into range */
	f -= k * M_PI;

	/* calculate sine and cosine*/
	f2 = f * f;

	s = f * (SC + f2 * (SB + SA * f2));
	c = CC + f2 * (CB + (CA * f2));

	/* if f is in an odd pi count we must flip */
	if (!(k % 2))
		return;

	s = -s;
	c = -c;
}


void g_math::AngleVectors(const Angle& angles, Vector* forward)
{
	float sp, sy, cp, cy;

	SinCos(Deg2Rad(angles.x), sp, cp);
	SinCos(Deg2Rad(angles.y), sy, cy);

	if (forward)
	{
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}
}

void g_math::AngleVectors(const Angle& angles, Vector* forward, Vector* right, Vector* up)
{
	float sr, sp, sy, cr, cp, cy;

	SinCos(Deg2Rad(angles.x), sp, cp);
	SinCos(Deg2Rad(angles.y), sy, cy);
	SinCos(Deg2Rad(angles.z), sr, cr);

	if (forward)
	{
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if (right)
	{
		right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
		right->y = (-1 * sr * sp * sy + -1 * cr * cy);
		right->z = -1 * sr * cp;
	}

	if (up)
	{
		up->x = (cr * sp * cy + -sr * -sy);
		up->y = (cr * sp * sy + -sr * cy);
		up->z = cr * cp;
	}
}

void g_math::AngleVectors(const Angle& angles, float* forward, float* right, float* up)
{
	float angle;
	static float sp, sy, cp, cy;

	angle = angles[0] * (M_PI / 180.f);
	sp = Sin(angle);
	cp = Cos(angle);

	angle = angles[1] * (M_PI / 180.f);
	sy = Sin(angle);
	cy = Cos(angle);

	if (forward)
	{
		forward[0] = cp * cy;
		forward[1] = cp * sy;
		forward[2] = -sp;
	}
	if (right || up)
	{
		static float sr, cr;

		angle = angles[2] * (M_PI / 180.f);
		sr = Sin(angle);
		cr = Cos(angle);

		if (right)
		{
			right[0] = -1 * sr * sp * cy + -1 * cr * -sy;
			right[1] = -1 * sr * sp * sy + -1 * cr * cy;
			right[2] = -1 * sr * cp;
		}
		if (up)
		{
			up[0] = cr * sp * cy + -sr * -sy;
			up[1] = cr * sp * sy + -sr * cy;
			up[2] = cr * cp;
		}
	}
}

void g_math::VectorAngles(Vector& forward, Angle& angles)
{
	float tmp, yaw, pitch;

	if ((Abs(forward.y) < DBL_EPSILON) && (Abs(forward.x) < DBL_EPSILON))
	{
		yaw = 0;

		if (forward.z > 0)
			pitch = 270;
		else
			pitch = 90;
	}
	else
	{
		yaw = Rad2Deg(atan2f(forward.y, forward.x));

		if (yaw < 0)
			yaw += 360;

		tmp = forward.Length2D();
		pitch = Rad2Deg(atan2f(-forward.z, tmp));

		if (pitch < 0)
			pitch += 360;
	}

	angles.x = pitch;
	angles.y = yaw;
	angles.z = 0;
}

float g_math::DotProduct(const Vector& v1, const Vector& v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

void g_math::Transform(const Vector& vSome, const Matrix3x4& vMatrix, Vector& vOut)
{
	for (auto i = 0; i < 3; i++)
		vOut[i] = vSome.Dot(Vector(vMatrix[i])) + vMatrix[i][3];
}

g_math* g_utilList::math = new g_math;