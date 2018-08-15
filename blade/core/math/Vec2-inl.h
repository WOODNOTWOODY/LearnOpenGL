
template <typename T> 
inline Vec2T<T>::Vec2T()
{

}

template <typename T>
inline Vec2T<T>::Vec2T(const T _x, const T _y)
	: x(_x)
	, y(_y)
{
}

template <typename T>
inline Vec2T<T>& Vec2T<T>::operator += (const Vec2T<T>& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

template <typename T>
inline Vec2T<T>& Vec2T<T>::operator -= (const Vec2T<T>& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

template <typename T>
inline Vec2T<T>& Vec2T<T>::operator *= (const T value)
{
	x *= value;
	y *= value;
	return *this;
}

template <typename T>
inline Vec2T<T>& Vec2T<T>::operator /= (const T value)
{
	x /= value;
	y /= value;
	return *this;
}

template <typename T>
inline T& Vec2T<T>::operator [] (int index)
{
	assert(index >= 0 && index < 2);
	return m[index];
}

template <typename T> 
inline const T& Vec2T<T>::operator [] (int index) const
{
	assert(index >= 0 && index < 2);
	return m[index];
}

template <typename T>
inline bool Vec2T<T>::operator < (const Vec2T<T>& rhs) const
{
	return (x < rhs.x && y < rhs.y);
}

template <typename T>
inline bool Vec2T<T>::operator <= (const Vec2T<T>& rhs) const
{
	return (x <= rhs.x && y <= rhs.y);
}

template <typename T>
inline bool Vec2T<T>::operator >(const Vec2T<T>& rhs) const
{
	return (x > rhs.x && y > rhs.y);
}

template <typename T>
inline bool Vec2T<T>::operator >= (const Vec2T<T>& rhs) const
{
	return (x >= rhs.x && y >= rhs.y);
}

template <typename T>
inline T Vec2T<T>::dot(const Vec2T<T>& rhs) const
{
	return (x * rhs.x + y * rhs.y);
}

template <typename T>
inline T Vec2T<T>::cross(const Vec2T<T>& rhs) const
{
	return (x * rhs.y - y * rhs.x);
}

template <typename T>
inline T Vec2T<T>::length() const
{
	return std::sqrt(x * x + y * y);
}

template <typename T>
inline T Vec2T<T>::lengthSqr() const
{
	return (x * x + y * y);
}

template <typename T>
inline void Vec2T<T>::normalize()
{
	T len = length();
	x /= len;
	y /= len;
}

template <typename T>
inline T Vec2T<T>::Dot(const Vec2T<T>& lhs, const Vec2T<T>& rhs)
{
	return (lhs.x * rhs.x + lhs.y * rhs.y);
}

template <typename T>
inline T Vec2T<T>::Cross(const Vec2T<T>& lhs, const Vec2T<T>& rhs)
{
	return (lhs.x * rhs.y - lhs.y * rhs.x);
}

template <typename T> 
inline bool operator == (const Vec2T<T>& lhs, const Vec2T<T>& rhs)
{
	return (Math::IsEqual(lhs.x, rhs.x) && Math::IsEqual(lhs.y, rhs.y));
}

template <typename T> 
inline bool operator != (const Vec2T<T>& lhs, const Vec2T<T>& rhs)
{
	return (Math::IsNotEqual(lhs.x, rhs.x) || Math::IsNotEqual(lhs.y, rhs.y));
}

template <typename T> 
inline Vec2T<T> operator + (const Vec2T<T> &rhs)
{
	return rhs;
}

template <typename T>
inline Vec2T<T> operator - (const Vec2T<T> &rhs)
{
	return Vec2T<T>(-rhs.x, -rhs.y);
}

template <typename T> 
inline Vec2T<T> operator + (const Vec2T<T> &a, const Vec2T<T> &b)
{
	return Vec2T<T>(a.x + b.x, a.y + b.y);
}

template <typename T> 
inline Vec2T<T> operator - (const Vec2T<T> &a, const Vec2T<T> &b)
{
	return Vec2T<T>(a.x - b.x, a.y - b.y);
}

template <typename T> 
inline Vec2T<T> operator * (const T f, const Vec2T<T> &v)
{
	return Vec2T<T>(f * v.x, f * v.y);
}

template <typename T> 
inline Vec2T<T> operator * (const Vec2T<T> &v, const T f)
{
	return Vec2T<T>(f * v.x, f * v.y);
}

template <typename T> 
inline Vec2T<T> operator / (const Vec2T<T> &a, const T f)
{
	return Vec2T<T>(a.x / f, a.y / f);
}

template <typename T> 
inline Vec2T<T> operator / (const T f, const Vec2T<T> &a)
{
	return Vec2T<T>(f / a.x, f / a.y);
}
