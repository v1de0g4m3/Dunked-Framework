#pragma once

class Vector
{
public:
	float x, y, z;

	explicit Vector(float _x = 0, float _y = 0, float _z = 0)
	{
		Init(_x, _y, _z);
	}

	explicit Vector(const float* v)
	{
		x = v[0];
		y = v[1];
		z = 0;
	}

	void Init(float _x = 0, float _y = 0, float _z = 0)
	{
		this->x = _x;
		this->y = _y;
		this->z = _z;
	}

	template <typename T>
	__forceinline float& operator[](T i)
	{
		return reinterpret_cast<float*>(this)[static_cast<int>(i)];
	}

	template <typename T>
	__forceinline float operator[](T i) const
	{
		return ((float*)this)[static_cast<int>(i)];
	}
	
	template <typename T>
	__forceinline Vector operator+(const T& in) const
	{
		return Vector(this->x + in, this->y + in, this->z + in);
	}

	template <typename T>
	__forceinline Vector operator-(const T& in) const
	{
		return Vector(this->x - in, this->y - in, this->z - in);
	}

	template <typename T>
	__forceinline Vector operator*(const T& in) const
	{
		return Vector(this->x * in, this->y * in, this->z * in);
	}

	template <typename T>
	__forceinline Vector operator/(const T& in) const
	{
		return Vector(this->x / in, this->y / in, this->z / in);
	}

	__forceinline Vector operator+(const Vector& in) const
	{
		return Vector(this->x + in.x, this->y + in.y, this->z + in.z);
	}

	__forceinline Vector operator-(const Vector& in) const
	{
		return Vector(this->x - in.x, this->y - in.y, this->z - in.z);
	}

	__forceinline Vector operator*(const Vector& in) const
	{
		return Vector(this->x * in.x, this->y * in.y, this->z * in.z);
	}

	__forceinline Vector operator/(const Vector& in) const
	{
		return Vector(this->x / in.x, this->y / in.y, this->z / in.z);
	}

	__forceinline Vector operator-=(const Vector& in)
	{
		this->x -= in.x;
		this->y -= in.y;
		this->z -= in.z;

		return *this;
	}

	template <typename T>
	__forceinline Vector operator-=(const T& in)
	{
		this->x -= in;
		this->y -= in;
		this->z -= in;

		return *this;
	}

	__forceinline Vector operator+=(const Vector& in)
	{
		this->x += in.x;
		this->y += in.y;
		this->z += in.z;

		return *this;
	}

	template <typename T>
	__forceinline Vector operator+=(const T& in)
	{
		this->x += in;
		this->y += in;
		this->z += in;

		return *this;
	}

	__forceinline Vector operator/=(const Vector& in)
	{
		this->x /= in.x;
		this->y /= in.y;
		this->z /= in.z;

		return *this;
	}

	template <typename T>
	__forceinline Vector operator/=(const T& in)
	{
		this->x /= in;
		this->y /= in;
		this->z /= in;

		return *this;
	}

	__forceinline Vector operator*=(const Vector& in)
	{
		this->x *= in.x;
		this->y *= in.y;
		this->z *= in.z;

		return *this;
	}

	template <typename T>
	__forceinline Vector operator*=(const T& in)
	{
		this->x *= in;
		this->y *= in;
		this->z *= in;

		return *this;
	}

	__forceinline bool operator==(const Vector& in)
	{
		auto& pVec = *this;

		return (fabs(pVec.x - in.x) < DBL_EPSILON) && (fabs(pVec.y - in.y) < DBL_EPSILON) && (fabs(pVec.z - in.z) < DBL_EPSILON);
	}

	__forceinline bool operator!=(const Vector& in)
	{
		auto& pVec = *this;

		return !((fabs(pVec.x - in.x) < DBL_EPSILON) && (fabs(pVec.y - in.y) < DBL_EPSILON) && (fabs(pVec.z - in.z) < DBL_EPSILON));
	}

	bool IsZero()
	{
		return *this == Vector();
	}

	void Clear()
	{
		this->x = this->y = this->z = .0f;
	}

	float Length() const
	{
		return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	float LengthSqr() const
	{
		return (this->x * this->x + this->y * this->y + this->z * this->z);
	}

	float Length2D() const
	{
		return sqrtf(this->x * this->x + this->y * this->y);
	}

	float Length2DSqr() const
	{
		return (this->x * this->x + this->y * this->y);
	}

	float Dot(const Vector& v) const
	{
		return (x * v.x + y * v.y + z * v.z);
	}
};

class Matrix3x4
{
public:
	Matrix3x4()
	{
		this->m[0][0] = 0.f;
		this->m[0][1] = 0.f;
		this->m[0][2] = 0.f;
		this->m[0][3] = 0.f;

		this->m[1][0] = 0.f;
		this->m[1][1] = 0.f;
		this->m[1][2] = 0.f;
		this->m[1][3] = 0.f;

		this->m[2][0] = 0.f;
		this->m[2][1] = 0.f;
		this->m[2][2] = 0.f;
		this->m[2][3] = 0.f;
	}

	float* operator[](int i)
	{
		return m[i];
	}

	const float* operator[](int i) const
	{
		return m[i];
	}

	float m[3][4];
};

class Matrix4x4
{
public:
	Matrix4x4()
	{
		this->m[0][0] = 0.f;
		this->m[0][1] = 0.f;
		this->m[0][2] = 0.f;
		this->m[0][3] = 0.f;

		this->m[1][0] = 0.f;
		this->m[1][1] = 0.f;
		this->m[1][2] = 0.f;
		this->m[1][3] = 0.f;

		this->m[2][0] = 0.f;
		this->m[2][1] = 0.f;
		this->m[2][2] = 0.f;
		this->m[2][3] = 0.f;

		this->m[3][0] = 0.f;
		this->m[3][1] = 0.f;
		this->m[3][2] = 0.f;
		this->m[3][3] = 0.f;
	}

	float* operator[](int i)
	{
		return m[i];
	}

	const float* operator[](int i) const
	{
		return m[i];
	}

	float m[4][4];
};
