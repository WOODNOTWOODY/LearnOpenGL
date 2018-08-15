#ifndef __BLADE_VEC2_H__
#define __BLADE_VEC2_H__

#include "MathLib.h"

BLADE_NAMESPACE_BEGIN

template <typename T>
class Vec2T
{
public:
#pragma pack(push, 1)
	union
	{
		struct
		{
			T x, y;
		};
		T m[2];
	};
#pragma pack(pop)

public:
	Vec2T();
	Vec2T(const T x, const T y);

public:
	Vec2T& operator += (const Vec2T& rhs);
	Vec2T& operator -= (const Vec2T& rhs);
	Vec2T& operator *= (const T value);
	Vec2T& operator /= (const T value);
	T& operator [] (int index);
	const T& operator [] (int index) const;
	bool operator < (const Vec2T& rhs) const;
	bool operator <= (const Vec2T& rhs) const;
	bool operator > (const Vec2T& rhs) const;
	bool operator >= (const Vec2T& rhs) const;

public:
	T                       dot(const Vec2T& rhs) const;
	T                       cross(const Vec2T& rhs) const;
	T                       length() const;
	T                       lengthSqr() const;
	void                    normalize();

public:
	static T                Dot(const Vec2T& lhs, const Vec2T& rhs);
	static T                Cross(const Vec2T& lhs, const Vec2T& rhs);

public:
	template <typename T> friend bool     operator == (const Vec2T<T>& lhs, const Vec2T<T>& rhs);
	template <typename T> friend bool     operator != (const Vec2T<T>& lhs, const Vec2T<T>& rhs);
	template <typename T> friend Vec2T<T> operator + (const Vec2T<T> &rhs);
	template <typename T> friend Vec2T<T> operator - (const Vec2T<T> &rhs);
	template <typename T> friend Vec2T<T> operator + (const Vec2T<T> &a, const Vec2T<T> &b);
	template <typename T> friend Vec2T<T> operator - (const Vec2T<T> &a, const Vec2T<T> &b);
	template <typename T> friend Vec2T<T> operator * (const T f, const Vec2T<T> &v);
	template <typename T> friend Vec2T<T> operator * (const Vec2T<T> &v, const T f);
	template <typename T> friend Vec2T<T> operator / (const Vec2T<T> &a, const T f);
	template <typename T> friend Vec2T<T> operator / (const T f, const Vec2T<T> &a);
};

#include "Vec2-inl.h"

BLADE_NAMESPACE_END

#endif
