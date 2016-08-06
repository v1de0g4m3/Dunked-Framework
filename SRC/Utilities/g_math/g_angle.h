#define M_PI		3.14159265358979323846f
#define M_INVPI     1 / M_PI
#define M_RADPI		57.295779513082f
#define RAD2DEG(x)	((float)(x) * (float)(180.f / M_PI))
#define DEG2RAD(x)	((float)(x) / (float)(180.f / M_PI))

class Angle : public Vector
{
public:
	explicit Angle(float _x = 0.f, float _y = 0.f, float _z = 0.f)
	{
		Init(_x, _y, _z);
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
	__forceinline Angle operator+(const T& in) const
	{
		return Angle(this->x + in, this->y + in, this->z + in);
	}

	template <typename T>
	__forceinline Angle operator-(const T& in) const
	{
		return Angle(this->x - in, this->y - in, this->z - in);
	}

	template <typename T>
	__forceinline Angle operator*(const T& in) const
	{
		return Angle(this->x * in, this->y * in, this->z * in);
	}

	template <typename T>
	__forceinline Angle operator/(const T& in) const
	{
		return Angle(this->x / in, this->y / in, this->z / in);
	}

	__forceinline Angle operator+(const Angle& in) const
	{
		return Angle(this->x + in.x, this->y + in.y, this->z + in.z);
	}

	__forceinline Angle operator-(const Angle& in) const
	{
		return Angle(this->x - in.x, this->y - in.y, this->z - in.z);
	}

	__forceinline Angle operator*(const Angle& in) const
	{
		return Angle(this->x * in.x, this->y * in.y, this->z * in.z);
	}

	__forceinline Angle operator/(const Angle& in) const
	{
		return Angle(this->x / in.x, this->y / in.y, this->z / in.z);
	}

	__forceinline Angle operator-=(const Angle& in)
	{
		this->x -= in.x;
		this->y -= in.y;
		this->z -= in.z;

		return *this;
	}

	template <typename T>
	__forceinline Angle operator-=(const T& in)
	{
		this->x -= in;
		this->y -= in;
		this->z -= in;

		return *this;
	}

	__forceinline Angle operator+=(const Angle& in)
	{
		this->x += in.x;
		this->y += in.y;
		this->z += in.z;

		return *this;
	}

	template <typename T>
	__forceinline Angle operator+=(const T& in)
	{
		this->x += in;
		this->y += in;
		this->z += in;

		return *this;
	}

	__forceinline Angle operator/=(const Angle& in)
	{
		this->x /= in.x;
		this->y /= in.y;
		this->z /= in.z;

		return *this;
	}

	template <typename T>
	__forceinline Angle operator/=(const T& in)
	{
		this->x /= in;
		this->y /= in;
		this->z /= in;

		return *this;
	}

	__forceinline Angle operator*=(const Angle& in)
	{
		this->x *= in.x;
		this->y *= in.y;
		this->z *= in.z;

		return *this;
	}

	template <typename T>
	__forceinline Angle operator*=(const T& in)
	{
		this->x *= in;
		this->y *= in;
		this->z *= in;

		return *this;
	}

	__forceinline bool operator==(const Angle& in)
	{
		auto& pVec = *this;

		return (fabs(pVec.x - in.x) < DBL_EPSILON) && (fabs(pVec.y - in.y) < DBL_EPSILON) && (fabs(pVec.z - in.z) < DBL_EPSILON);
	}

	__forceinline bool operator!=(const Angle& in)
	{
		auto& pVec = *this;

		return !((fabs(pVec.x - in.x) < DBL_EPSILON) && (fabs(pVec.y - in.y) < DBL_EPSILON) && (fabs(pVec.z - in.z) < DBL_EPSILON));
	}

	Angle Normalize()
	{
		if (this->x != this->x)
			this->x = 0.f;
		if (this->y != this->y)
			this->y = 0.f;
		if (this->z != this->z)
			this->z = 0.f;

		if (this->x > 89.f)
			this->x = 89.f;
		if (this->x < -89.f)
			this->x = -89.f;

		while (this->y > 180.f)
			this->y -= 360.f;
		while (this->y <= -180.f)
			this->y += 360.f;

		if (this->y > 180.f)
			this->y = 180.f;
		if (this->y < -180.f)
			this->y = -180.f;

		this->z = 0.f;

		return *this;
	}
};