#ifndef __BLADE_MAT4_H__
#define __BLADE_MAT4_H__

#include "Vec4.h"

BLADE_NAMESPACE_BEGIN

//struct FrustumPlanes
//{
//	float left;
//	float right;
//	float bottom;
//	float top;
//	float zNear;
//	float zFar;
//};

// column major. memory layout:
//
//                row no (=vertical)
//               |  0   1   2   3
//            ---+----------------
//            0  | m00 m10 m20 m30
// column no  1  | m01 m11 m21 m31
// (=horiz)   2  | m02 m12 m22 m32
//            3  | m03 m13 m23 m33

template <typename T>
class Mat4T
{
public:
#pragma pack(push, 1)
	union
	{
		struct
		{
			T m00, m10, m20, m30;
			T m01, m11, m21, m31;
			T m02, m12, m22, m32;
			T m03, m13, m23, m33;
		}
		T m[16];
	};

public:
	Mat4T();
	Mat4T(const T* arr);

public:
	T operator () (int row, int column) const;
	Mat4T& operator += (const T f);
	Mat4T& operator += (const Mat4T &rhs);
	Mat4T& operator -= (const T f);
	Mat4T& operator -= (const Mat4T &rhs);
	Mat4T& operator *= (const T f);
	Mat4T& operator *= (const Mat4T &rhs);
	Mat4T& operator /= (const T f);

public:
	bool            isIdentify() const;
	bool            isPerspective() const;
	T               get(int row, int column) const;
	Vec4T<T>        getRow(int row) const;
	Vec4T<T>        getColumn(int col) const;
	void            setRow(int row, const Vec4T<T>& v);
	void            setColumn(int col, const Vec4T<T>& v);
	const T*        ptr() const;
	T*              ptr();

	/*T               getDeterminant() const;*/
	Mat4T&          transpose();
	Mat4T&          inverseGeneral3D();
	Mat4T&          inverseFull();
	Mat4T&          identity();
	Mat4T&          zero();

	Mat4T&          translate(const Vec3T<T>& v);
	Mat4T&          translate(T x, T y, T z);
	Mat4T&          makeTranslate(const Vec3T<T>& v);
	Mat4T&          makeTranslate(T x, T y, T z);

	Mat4T&          scale(const Vec3T<T>& v);
	Mat4T&          scale(T x, T y, T z);
	Mat4T&          makeScale(const Vec3T<T>& v);
	Mat4T&          makeScale(T x, T y, T z);

	Mat4T&          rotate(const Vec3T<T>& axis, T radian);
	Mat4T&          makeRotate(const Vec3T<T>& axis, T radian);

	Vec3T<T>        perspectiveTransform(const Vec3T<T>& v) const;
	Vec4T<T>        perspectiveTransform(const Vec4T<T>& v) const;

	Vec3T<T>        affineTransform(const Vec3T<T>& v) const;
	Vec4T<T>        affineTransform(const Vec4T<T>& v) const;

	/*void			decompose(Vec3T<T>& t, QuatT<T>& r, Vec3T<T>& s) const;
	Vec3T<T>		decomposeTranslation() const;
	Vec3T<T>		decomposeScale() const;
	QuatT<T>		decomposeRotation() const;
	Mat4T<T>		decomposeRotationMatrix() const;
	FrustumPlanes   decomposeProjection() const;*/

	Mat4T&          perspective(T fov, T aspect, T near, T far);
	Mat4T&          ortho(T left, T right, T bottom, T top, T near, T far);

public:
	template <typename T> friend bool     operator == (const Mat4T<T> &a, const Mat4T<T> &b);
	template <typename T> friend bool     operator != (const Mat4T<T> &a, const Mat4T<T> &b);
	template <typename T> friend Mat4T<T> operator + (const Mat4T<T> &a, const T f);
	template <typename T> friend Mat4T<T> operator + (const T f, const Mat4T<T> &a);
	template <typename T> friend Mat4T<T> operator + (const Mat4T<T> &a, const Mat4T<T> &b);
	template <typename T> friend Mat4T<T> operator - (const Mat4T<T> &a, const T f);
	template <typename T> friend Mat4T<T> operator - (const T f, const Mat4T<T> &a);
	template <typename T> friend Mat4T<T> operator - (const Mat4T<T> &a, const Mat4T<T> &b);
	template <typename T> friend Vec4T<T> operator * (const Mat4T<T> &mat, const Vec4T<T> &vec);
	template <typename T> friend Vec3T<T> operator * (const Mat4T<T> &mat, const Vec3T<T> &vec);
	template <typename T> friend Mat4T<T> operator * (const Mat4T<T> &a, const Mat4T<T> &b);
	template <typename T> friend Mat4T<T> operator * (const Mat4T<T> &a, const T f);
	template <typename T> friend Mat4T<T> operator * (const T f, const Mat4T<T> &a);
	template <typename T> friend Mat4T<T> operator / (const Mat4T<T> &mat, const T f);
};

#include "Mat4-inl.h"

BLADE_NAMESPACE_END

#endif
