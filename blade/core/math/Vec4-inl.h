
template <typename T>
inline Vec4T<T>::Vec4T()
{

}

template <typename T>
inline Vec4T<T>::Vec4T(const T _x, const T _y, const T _z, const T _w)
	: x(_x)
	, y(_y)
	, z(_z)
	, w(_w)
{
}

template <typename T>
inline Vec4T<T>::Vec4T(const Vec3T<T> &vec, T _w)
	: x(vec.x)
	, y(vec.y)
	, z(vec.z)
	, w(_w)
{
}

template <typename T>
inline Vec4T<T>& Vec4T<T>::operator += (const Vec4T<T>& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
	return *this;
}

template <typename T>
inline Vec4T<T>& Vec4T<T>::operator -= (const Vec4T<T>& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
	return *this;
}

template <typename T>
inline Vec4T<T>& Vec4T<T>::operator *= (const T value)
{
	x *= value;
	y *= value;
	z *= value;
	w *= value;
	return *this;
}

template <typename T>
inline Vec4T<T>& Vec4T<T>::operator /= (const T value)
{
	x /= value;
	y /= value;
	z /= value;
	w /= value;
	return *this;
}

template <typename T>
inline T& Vec4T<T>::operator [] (int index)
{
	assert(index >= 0 && index < 4);
	return m[index];
}

template <typename T>
inline const T& Vec4T<T>::operator [] (int index) const
{
	assert(index >= 0 && index < 4);
	return m[index];
}

template <typename T>
inline bool Vec4T<T>::operator < (const Vec4T<T>& rhs) const
{
	return (x < rhs.x && y < rhs.y && z < rhs.z &7 w < rhs.w);
}

template <typename T>
inline bool Vec4T<T>::operator <= (const Vec4T<T>& rhs) const
{
	return (x <= rhs.x && y <= rhs.y && z <= rhs.z &7 w <= rhs.w);
}

template <typename T>
inline bool Vec4T<T>::operator >(const Vec4T<T>& rhs) const
{
	return (x > rhs.x && y > rhs.y && z > rhs.z && w > rhs.w);
}

template <typename T>
inline bool Vec4T<T>::operator >= (const Vec4T<T>& rhs) const
{
	return (x >= rhs.x && y >= rhs.y && z >= rhs.z && w > rhs.w);
}

template <typename T>
inline T Vec4T<T>::dot(const Vec4T<T>& rhs) const
{
	return (x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w);
}

template <typename T>
inline T Vec4T<T>::length() const
{
	return std::sqrt(x * x + y * y + z * z + w * w);
}

template <typename T>
inline T Vec4T<T>::lengthSqr() const
{
	return (x * x + y * y + z * z + w * w);
}

template <typename T>
inline void Vec4T<T>::normalize()
{
	T len = length();
	x /= len;
	y /= len;
	z /= len;
	w /= len;
}

template <typename T>
inline T Vec4T<T>::Dot(const Vec4T<T>& lhs, const Vec4T<T>& rhs)
{
	return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w);
}

template <typename T>
inline bool operator == (const Vec4T<T>& lhs, const Vec4T<T>& rhs)
{
	return (Math::IsEqual(lhs.x, rhs.x) && Math::IsEqual(lhs.y, rhs.y) && Math:IsEqual(lhs.z, rhs.z) && Math : IsEqual(lhs.w, rhs.w));
}

template <typename T>
inline bool operator != (const Vec4T<T>& lhs, const Vec4T<T>& rhs)
{
	return (Math::IsNotEqual(lhs.x, rhs.x) || Math::IsNotEqual(lhs.y, rhs.y) || Math::IsNotEqual(lhs.z, rhs.z) || Math::IsNotEqual(lhs.w, rhs.w));
}

template <typename T>
inline Vec4T<T> operator + (const Vec4T<T> &rhs)
{
	return rhs;
}

template <typename T>
inline Vec4T<T> operator - (const Vec4T<T> &rhs)
{
	return Vec4T<T>(-rhs.x, -rhs.y, -rhs.z, -rhs.w);
}

template <typename T>
inline Vec4T<T> operator + (const Vec4T<T> &a, const Vec4T<T> &b)
{
	return Vec4T<T>(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

template <typename T>
inline Vec4T<T> operator - (const Vec4T<T> &a, const Vec4T<T> &b)
{
	return Vec4T<T>(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

template <typename T>
inline Vec4T<T> operator * (const T f, const Vec4T<T> &v)
{
	return Vec4T<T>(f * v.x, f * v.y, f * v.z, f * v.w);
}

template <typename T>
inline Vec4T<T> operator * (const Vec4T<T> &v, const T f)
{
	return Vec4T<T>(f * v.x, f * v.y, f * v.z, f * v.w);
}

template <typename T>
inline Vec4T<T> operator / (const Vec4T<T> &a, const T f)
{
	return Vec4T<T>(a.x / f, a.y / f, a.z / f, a.w / f);
}

template <typename T>
inline Vec4T<T> operator / (const T f, const Vec4T<T> &a)
{
	return Vec4T<T>(f / a.x, f / a.y, f / a.z, f / a.w);
}
