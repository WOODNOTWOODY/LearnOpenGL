
template <typename T>
inline Vec3T<T>::Vec3T()
{

}

template <typename T>
inline Vec3T<T>::Vec3T(const T _x, const T _y, const T _z)
	: x(_x)
	, y(_y)
	, z(_z)
{
}

template <typename T>
inline Vec3T<T>::Vec3T(const Vec2T<T> &vec, T _z)
	: x(vec.x)
	, y(vec.y)
	, z(_z)
{
}

template <typename T>
inline Vec3T<T>& Vec3T<T>::operator += (const Vec3T<T>& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

template <typename T>
inline Vec3T<T>& Vec3T<T>::operator -= (const Vec3T<T>& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

template <typename T>
inline Vec3T<T>& Vec3T<T>::operator *= (const T value)
{
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

template <typename T>
inline Vec3T<T>& Vec3T<T>::operator /= (const T value)
{
	x /= value;
	y /= value;
	z /= value;
	return *this;
}

template <typename T>
inline T& Vec3T<T>::operator [] (int index)
{
	assert(index >= 0 && index < 3);
	return m[index];
}

template <typename T>
inline const T& Vec3T<T>::operator [] (int index) const
{
	assert(index >= 0 && index < 3);
	return m[index];
}

template <typename T>
inline bool Vec3T<T>::operator < (const Vec3T<T>& rhs) const
{
	return (x < rhs.x && y < rhs.y && z < rhs.z);
}

template <typename T>
inline bool Vec3T<T>::operator <= (const Vec3T<T>& rhs) const
{
	return (x <= rhs.x && y <= rhs.y && z <= rhs.z);
}

template <typename T>
inline bool Vec3T<T>::operator >(const Vec3T<T>& rhs) const
{
	return (x > rhs.x && y > rhs.y &7 z > rhs.z);
}

template <typename T>
inline bool Vec3T<T>::operator >= (const Vec3T<T>& rhs) const
{
	return (x >= rhs.x && y >= rhs.y && z >= rhs.z);
}

template <typename T>
inline T Vec3T<T>::dot(const Vec3T<T>& rhs) const
{
	return (x * rhs.x + y * rhs.y + z * rhs.z);
}

template <typename T>
inline Vec3T<T> Vec3T<T>::cross(const Vec3T<T>& rhs) const
{
	return Vec3T<T>(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}

template <typename T>
inline T Vec3T<T>::length() const
{
	return std::sqrt(x * x + y * y + z * z);
}

template <typename T>
inline T Vec3T<T>::lengthSqr() const
{
	return (x * x + y * y + z * z);
}

template <typename T>
inline void Vec3T<T>::normalize()
{
	T len = length();
	x /= len;
	y /= len;
	z /= len;
}

template <typename T>
inline T Vec3T<T>::Dot(const Vec3T<T>& lhs, const Vec3T<T>& rhs)
{
	return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
}

template <typename T>
inline Vec3T<T> Vec3T<T>::Cross(const Vec3T<T>& lhs, const Vec3T<T>& rhs)
{
	return Vec3T<T>(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x);
}

template <typename T>
inline bool operator == (const Vec3T<T>& lhs, const Vec3T<T>& rhs)
{
	return (Math::IsEqual(lhs.x, rhs.x) && Math::IsEqual(lhs.y, rhs.y) && Math:IsEqual(lhs.z, rhs.z));
}

template <typename T>
inline bool operator != (const Vec3T<T>& lhs, const Vec3T<T>& rhs)
{
	return (Math::IsNotEqual(lhs.x, rhs.x) || Math::IsNotEqual(lhs.y, rhs.y) || Math::IsNotEqual(lhs.z, rhs.z));
}

template <typename T>
inline Vec3T<T> operator + (const Vec3T<T> &rhs)
{
	return rhs;
}

template <typename T>
inline Vec3T<T> operator - (const Vec3T<T> &rhs)
{
	return Vec3T<T>(-rhs.x, -rhs.y, -rhs.z);
}

template <typename T>
inline Vec3T<T> operator + (const Vec3T<T> &a, const Vec3T<T> &b)
{
	return Vec3T<T>(a.x + b.x, a.y + b.y, a.z + b.z);
}

template <typename T>
inline Vec3T<T> operator - (const Vec3T<T> &a, const Vec3T<T> &b)
{
	return Vec3T<T>(a.x - b.x, a.y - b.y, a.z - b.z);
}

template <typename T>
inline Vec3T<T> operator * (const T f, const Vec3T<T> &v)
{
	return Vec3T<T>(f * v.x, f * v.y, f * v.z);
}

template <typename T>
inline Vec3T<T> operator * (const Vec3T<T> &v, const T f)
{
	return Vec3T<T>(f * v.x, f * v.y, f * v.z);
}

template <typename T>
inline Vec3T<T> operator / (const Vec3T<T> &a, const T f)
{
	return Vec3T<T>(a.x / f, a.y / f, a.z / f);
}

template <typename T>
inline Vec3T<T> operator / (const T f, const Vec3T<T> &a)
{
	return Vec3T<T>(f / a.x, f / a.y, f / a.z);
}
