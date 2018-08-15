#ifndef __BLADE_VEC3_H__
#define __BLADE_VEC3_H__

#include "MathLib.h"
#include "Vec2.h"

BLADE_NAMESPACE_BEGIN

template <typename T>
class Vec3T
{
public:
#pragma pack(push, 1)
	union
	{
		struct
		{
			T x, y, z;
		};
		T m[3];
	};
#pragma pack(pop)

public:
	Vec3T();
	Vec3T(const T x, const T y, const T z);
	Vec3T(const Vec2T<T> &vec, T z);

public:
	Vec3T& operator += (const Vec3T& rhs);
	Vec3T& operator -= (const Vec3T& rhs);
	Vec3T& operator *= (const T value);
	Vec3T& operator /= (const T value);
	T& operator [] (int index);
	const T& operator [] (int index) const;
	bool operator < (const Vec3T& rhs) const;
	bool operator <= (const Vec3T& rhs) const;
	bool operator > (const Vec3T& rhs) const;
	bool operator >= (const Vec3T& rhs) const;

public:
	T                       dot(const Vec3T& rhs) const;
	Vec3T<T>                cross(const Vec3T& rhs) const;
	T                       length() const;
	T                       lengthSqr() const;
	void                    normalize();

public:
	static T                Dot(const Vec3T& lhs, const Vec3T& rhs);
	static Vec3T<T>         Cross(const Vec3T& lhs, const Vec3T& rhs);

public:
	template <typename T> friend bool     operator == (const Vec3T<T>& lhs, const Vec3T<T>& rhs);
	template <typename T> friend bool     operator != (const Vec3T<T>& lhs, const Vec3T<T>& rhs);
	template <typename T> friend Vec3T<T> operator + (const Vec3T<T> &rhs);
	template <typename T> friend Vec3T<T> operator - (const Vec3T<T> &rhs);
	template <typename T> friend Vec3T<T> operator + (const Vec3T<T> &a, const Vec3T<T> &b);
	template <typename T> friend Vec3T<T> operator - (const Vec3T<T> &a, const Vec3T<T> &b);
	template <typename T> friend Vec3T<T> operator * (const T f, const Vec3T<T> &v);
	template <typename T> friend Vec3T<T> operator * (const Vec3T<T> &v, const T f);
	template <typename T> friend Vec3T<T> operator / (const Vec3T<T> &a, const T f);
	template <typename T> friend Vec3T<T> operator / (const T f, const Vec3T<T> &a);
};

#include "Vec3-inl.h"

BLADE_NAMESPACE_END

#endif
