template <typename T> inline 
ColorT<T>::ColorT(const T *pf)
{
	r = pf[0];
	g = pf[1];
	b = pf[2];
	a = pf[3];
}

template <typename T> inline 
ColorT<T>::ColorT(T fr, T fg, T fb, T fa)
{
	r = fr;
	g = fg;
	b = fb;
	a = fa;
}

// casting
template <typename T> inline 
ColorT<T>::operator uint32 () const
{
	return getARGB();
}

template <typename T> inline 
ColorT<T>::operator T * ()
{
	return (T *)&r;
}

template <typename T> inline 
ColorT<T>::operator const T * () const
{
	return (const T *) &r;
}

// assignment operators
template <typename T> inline 
ColorT<T>& ColorT<T>::operator += (const ColorT &c)
{
	r += c.r;
	g += c.g;
	b += c.b;
	a += c.a;
	return *this;
}

template <typename T> inline 
ColorT<T>& ColorT<T>::operator -= (const ColorT &c)
{
	r -= c.r;
	g -= c.g;
	b -= c.b;
	a -= c.a;
	return *this;
}

template <typename T> inline 
ColorT<T>& ColorT<T>::operator *= (const ColorT &c)
{
	r *= c.r;
	g *= c.g;
	b *= c.b;
	a *= c.a;

	return *this;
}

template <typename T> inline 
ColorT<T>& ColorT<T>::operator *= (T f)
{
	r *= f;
	g *= f;
	b *= f;
	a *= f;
	return *this;
}

template <typename T> inline 
ColorT<T>& ColorT<T>::operator /= (T f)
{
	T fInv = 1.0f / f;
	r *= fInv;
	g *= fInv;
	b *= fInv;
	a *= fInv;
	return *this;
}

// unary operators
template <typename T> inline 
ColorT<T> ColorT<T>::operator + () const
{
	return *this;
}

template <typename T> inline 
ColorT<T> ColorT<T>::operator - () const
{
	return ColorT(-r, -g, -b, -a);
}

// binary operators
template <typename T> inline 
ColorT<T> ColorT<T>::operator + (const ColorT &c) const
{
	return ColorT(r + c.r, g + c.g, b + c.b, a + c.a);
}

template <typename T> inline 
ColorT<T> ColorT<T>::operator - (const ColorT &c) const
{
	return ColorT(r - c.r, g - c.g, b - c.b, a - c.a);
}

template <typename T> inline 
ColorT<T> ColorT<T>::operator * (const ColorT &c) const
{
	return ColorT(r * c.r, g * c.g, b * c.b, a * c.a);
}

template <typename T> inline 
ColorT<T> ColorT<T>::operator * (T f) const
{
	return ColorT(r * f, g * f, b * f, a * f);
}

template <typename T> inline 
ColorT<T> ColorT<T>::operator / (T f) const
{
	T fInv = 1.0f / f;
	return ColorT(r * fInv, g * fInv, b * fInv, a * fInv);
}

template <typename T> inline 
T& ColorT<T>::operator [] (int index)
{
	return m[index];
}

template <typename T> inline 
const T& ColorT<T>::operator [] (int index) const
{
	return m[index];
}

template <typename T> inline 
bool ColorT<T>::operator == (const ColorT &c) const
{
	return Math::IsEqual(r, c.r) && Math::IsEqual(g, c.g) && Math::IsEqual(b, c.b) && Math::IsEqual(a, c.a);
}

template <typename T> inline 
bool ColorT<T>::operator != (const ColorT &c) const
{
	return Math::IsNotEqual(r, c.r) || Math::IsNotEqual(g, c.g) || Math::IsNotEqual(b, c.b) || Math::IsNotEqual(a, c.a);
}

template <typename T> inline 
void ColorT<T>::set(T fr, T fg, T fb, T fa)
{
	r = fr;
	g = fg;
	b = fb;
	a = fa;
}

template <typename T> inline 
void ColorT<T>::setARGB(uint32 argb)
{
	const T f = 1.0f / 255.0f;
	r = f * (T) (Byte) (argb >> 16);
	g = f * (T) (Byte) (argb >>  8);
	b = f * (T) (Byte) (argb);
	a = f * (T) (Byte) (argb >> 24);
}

template <typename T> inline 
void ColorT<T>::setABGR(uint32 abgr)
{
	const T f = 1.0f / 255.0f;
	r = f * (T) (Byte) (abgr);
	g = f * (T) (Byte) (abgr >>  8);
	b = f * (T) (Byte) (abgr >>  16);
	a = f * (T) (Byte) (abgr >> 24);
}

template <typename T> inline
void ColorT<T>::setRGBA(uint32 rgba)
{
	const T f = 1.0f / 255.0f;
	r = f * (T)(Byte)(rgba >> 24);
	g = f * (T)(Byte)(rgba >> 16);
	b = f * (T)(Byte)(rgba >> 8);
	a = f * (T)(Byte)(rgba);
}

template <typename T> inline 
uint32 ColorT<T>::getARGB() const
{
	uint32 dwR = std::clamp((uint32)(r * 255.0f), (uint32)0, (uint32)255);
	uint32 dwG = std::clamp((uint32)(g * 255.0f), (uint32)0, (uint32)255);
	uint32 dwB = std::clamp((uint32)(b * 255.0f), (uint32)0, (uint32)255);
	uint32 dwA = std::clamp((uint32)(a * 255.0f), (uint32)0, (uint32)255);
	return (dwA << 24) | (dwR << 16) | (dwG << 8) | dwB;
}

template <typename T> inline 
uint32 ColorT<T>::getABGR() const
{
	uint32 dwR = std::clamp((uint32)(r * 255.0f), (uint32)0, (uint32)255);
	uint32 dwG = std::clamp((uint32)(g * 255.0f), (uint32)0, (uint32)255);
	uint32 dwB = std::clamp((uint32)(b * 255.0f), (uint32)0, (uint32)255);
	uint32 dwA = std::clamp((uint32)(a * 255.0f), (uint32)0, (uint32)255);
	return (dwA << 24) | (dwB << 16) | (dwG << 8) | dwR;
}

template <typename T> inline 
uint32 ColorT<T>::getRGBA() const
{
	uint32 dwR = std::clamp((uint32)(r * 255.0f), (uint32)0, (uint32)255);
	uint32 dwG = std::clamp((uint32)(g * 255.0f), (uint32)0, (uint32)255);
	uint32 dwB = std::clamp((uint32)(b * 255.0f), (uint32)0, (uint32)255);
	uint32 dwA = std::clamp((uint32)(a * 255.0f), (uint32)0, (uint32)255);
	return (dwR << 24) | (dwG << 16) | (dwB << 8) | dwA;
}

template <typename T> inline 
uint32 ColorT<T>::getBGRA() const
{
	uint32 dwR = std::clamp((uint32)(r * 255.0f), (uint32)0, (uint32)255);
	uint32 dwG = std::clamp((uint32)(g * 255.0f), (uint32)0, (uint32)255);
	uint32 dwB = std::clamp((uint32)(b * 255.0f), (uint32)0, (uint32)255);
	uint32 dwA = std::clamp((uint32)(a * 255.0f), (uint32)0, (uint32)255);
	return (dwB << 24) | (dwG << 16) | (dwR << 8) | dwA;
}

template <typename T> inline 
ColorT<T>& ColorT<T>::saturate()
{
	if ( r > 1 ) r = 1;
	if ( g > 1 ) g = 1;
	if ( b > 1 ) b = 1;
	if ( a > 1 ) a = 1;

	if ( r < 0 ) r = 0;
	if ( g < 0 ) g = 0;
	if ( b < 0 ) b = 0;
	if ( a < 0 ) a = 0;

	return *this;
}

template <typename T> inline 
ColorT<T>& ColorT<T>::pow(T exponent)
{
	r = std::pow(r, exponent);
	g = std::pow(g, exponent);
	b = std::pow(b, exponent);
	a = std::pow(a, exponent);

	return *this;
}

template <typename T> inline 
ColorT<T> operator * (T f, const ColorT<T> &c)
{
	return ColorT<T>(f * c.r, f * c.g, f * c.b, f * c.a);
}