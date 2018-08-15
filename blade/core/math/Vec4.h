#ifndef __BLADE_VEC4_H__
#define __BLADE_VEC4_H__

#include "MathLib.h"
#include "Vec3.h"

BLADE_NAMESPACE_BEGIN

template <typename T>
class Vec4T
{
public:
#pragma pack(push, 1)
	union
	{
		struct
		{
			T x, y, z, w;
		};
		T m[4];
	};
#pragma pack(pop)

public:
	Vec4T();
	Vec4T(const T x, const T y, const T z, const T w);
	Vec4T(const Vec3T<T>& vec, T w);

public:
	Vec4T& operator += (const Vec4T& rhs);
	Vec4T& operator -= (const Vec4T& rhs);
	Vec4T& operator *= (const T value);
	Vec4T& operator /= (const T value);
	T& operator [] (int index);
	const T& operator [] (int index) const;
	bool operator < (const Vec4T& rhs) const;
	bool operator <= (const Vec4T& rhs) const;
	bool operator > (const Vec4T& rhs) const;
	bool operator >= (const Vec4T& rhs) const;

public:
	T                       dot(const Vec4T& rhs) const;
	T                       length() const;
	T                       lengthSqr() const;
	void                    normalize();

public:
	static T                Dot(const Vec4T& lhs, const Vec4T& rhs);

public:
	template <typename T> friend bool     operator == (const Vec4T<T>& lhs, const Vec4T<T>& rhs);
	template <typename T> friend bool     operator != (const Vec4T<T>& lhs, const Vec4T<T>& rhs);
	template <typename T> friend Vec4T<T> operator + (const Vec4T<T> &rhs);
	template <typename T> friend Vec4T<T> operator - (const Vec4T<T> &rhs);
	template <typename T> friend Vec4T<T> operator + (const Vec4T<T> &a, const Vec4T<T> &b);
	template <typename T> friend Vec4T<T> operator - (const Vec4T<T> &a, const Vec4T<T> &b);
	template <typename T> friend Vec4T<T> operator * (const T f, const Vec4T<T> &v);
	template <typename T> friend Vec4T<T> operator * (const Vec4T<T> &v, const T f);
	template <typename T> friend Vec4T<T> operator / (const Vec4T<T> &a, const T f);
	template <typename T> friend Vec4T<T> operator / (const T f, const Vec4T<T> &a);
};

#include "Vec4-inl.h"

BLADE_NAMESPACE_END

#endif
