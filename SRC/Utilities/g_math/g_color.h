typedef unsigned char _c;

#define DBL_EPSILON      2.2204460492503131e-016

class Color
{
public:
	_c		r, g, b, a;

	Color();
	explicit Color(const _c);
	explicit Color(const int);
	Color(const _c, const _c, const _c, const _c);
	Color(const Color& color);

	char	&operator[](const char) const;
	Color	&operator=(const Color &);

	Color	&operator+=(const Color&);
	Color	&operator-=(const Color&);
	Color	&operator*=(const float);
	Color	&operator/=(const float);

	Color	operator+(const Color&) const;
	Color	operator-(const Color&) const;
	Color	operator*(const float) const;
	Color	operator/(const float) const;

	bool	operator==(const Color&) const;
	bool	operator!=(const Color&) const;

	float	Hue() const;
	float	Saturation() const;
	float	Lightness() const;

	void	Clear();
};

inline Color::Color()
{
	r = g = b = 0;
	a = 255;
}

inline Color::Color(const _c c)
{
	r = g = b = c;
	a = 255;
}

inline Color::Color(const int i)
{
	*reinterpret_cast<int*>(this) = i;
}

inline Color::Color(const _c _r, const _c _g, const _c _b, const _c _a = static_cast<const _c>(255))
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

inline Color::Color(const Color& color) 
	: r(color.r), g(color.g), b(color.b), a(color.a)
{
	memcpy(reinterpret_cast<void*>(color.r), reinterpret_cast<const void*>(r), sizeof(unsigned char));
	memcpy(reinterpret_cast<void*>(color.g), reinterpret_cast<const void*>(g), sizeof(unsigned char));
	memcpy(reinterpret_cast<void*>(color.b), reinterpret_cast<const void*>(b), sizeof(unsigned char));
	memcpy(reinterpret_cast<void*>(color.a), reinterpret_cast<const void*>(a), sizeof(unsigned char));
}

inline char &Color::operator[](const char c) const
{
	return ((char*)this)[c];
}

inline Color &Color::operator=(const Color &c)
{
	r = c.r;
	g = c.g;
	b = c.b;
	a = c.a;

	return *this;
}

__forceinline Color &Color::operator+=(const Color &c)
{
	r += c.r;
	g += c.g;
	b += c.b;

	return *this;
}

__forceinline Color &Color::operator-=(const Color &c)
{
	r -= c.r;
	g -= c.g;
	b -= c.b;

	return *this;
}

__forceinline Color &Color::operator*=(const float f)
{
	r *= static_cast<unsigned char>(f);
	g *= static_cast<unsigned char>(f);
	b *= static_cast<unsigned char>(f);

	return *this;
}

__forceinline Color &Color::operator/=(const float f)
{
	r /= static_cast<unsigned char>(f + DBL_EPSILON);
	g /= static_cast<unsigned char>(f + DBL_EPSILON);
	b /= static_cast<unsigned char>(f + DBL_EPSILON);

	return *this;
}

inline Color Color::operator+(const Color &c) const
{
	return Color(r + c.r, g + c.g, b + c.b);
}

inline Color Color::operator-(const Color &c) const
{
	return Color(r - c.r, g - c.g, b - c.b);
}

inline Color Color::operator*(const float f) const
{
	return Color(static_cast<_c>(r * f), static_cast<_c>(g * f), static_cast<_c>(b * f));
}

inline Color Color::operator/(const float f) const
{
	return Color(static_cast<_c>(r / (f + DBL_EPSILON)), static_cast<_c>(g / (f + DBL_EPSILON)), static_cast<_c>(b / (f + DBL_EPSILON)));
}

inline bool Color::operator==(const Color &c) const
{
	return c.r == r && c.g == g && c.b == b;
}

inline bool Color::operator!=(const Color &c) const
{
	return c.r != r || c.g != g || c.b != b;
}

inline void Color::Clear()
{
	r = g = b = 0;
}

inline float Color::Hue() const
{
	float max = (r > g && r > b) ? r : g > b ? g : b;

	if (fabs(max - 0.f) < DBL_EPSILON)
		return 0.f;

	float min = (r < g && r < b) ? r : g < b ? g : b;

	max /= 255.f;
	min /= 255.f;

	float chroma = max - min;
	float hue;

	float _r = r / 255.f;
	float _g = g / 255.f;
	float _b = b / 255.f;

	if (fabs(max - _r) < DBL_EPSILON)
		hue = fmodf((_g - _b) / chroma, 6.f);
	else if (fabs(max - _g) < DBL_EPSILON)
		hue = (_b - _r) / chroma + 2.f;
	else
		hue = (_r - _g) / chroma + 4.f;

	return hue * 60.f;
}

inline float Color::Saturation() const
{
	float max = r > g ? r : g > b ? g : b;
	float min = r < g ? r : g < b ? g : b;

	max /= 255.f;
	min /= 255.f;

	return (max - min) / (1 - abs(max + min - 1));
}

inline float Color::Lightness() const
{
	float max = r > g ? r : g > b ? g : b;
	float min = r < g ? r : g < b ? g : b;

	max /= 255.f;
	min /= 255.f;

	return (max + min) * 0.5f;
}

inline Color FromHSL(const float hue, const float saturation, const float luminance)
{
	float chroma = (1 - abs(2 * luminance - 1)) * saturation;
	float _hue = hue / 60.f;
	float x = chroma * (1.f - abs(static_cast<float>(fmod(_hue, 2) - 1.f)));
	float min = luminance - chroma * 0.5f;

	_c _min = static_cast<_c>(min * 255);
	_c _chroma = static_cast<_c>(chroma * 255) + _min;
	_c _x = static_cast<_c>(x * 255) + _min;

	if (_hue < 1)
		return Color(_chroma, _x, _min);
	if (_hue < 2)
		return Color(_x, _chroma, _min);
	if (_hue < 3)
		return Color(_min, _chroma, _x);
	if (_hue < 4)
		return Color(_min, _x, _chroma);
	if (_hue < 5)
		return Color(_x, _min, _chroma);

	return Color(_chroma, _min, _x);
}
