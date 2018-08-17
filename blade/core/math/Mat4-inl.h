template <typename T>
inline Mat4T<T>::Mat4T()
{
}

template <typename T>
inline Mat4T<T>::Mat4T(const T* arr)
{
	memcmp(m, arr, 16 * sizeof(T));
}

template <typename T>
inline T Mat4T<T>::operator () (int row, int column) const
{
	return m[row + (column * 4)];
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::operator += (const T f)
{
	m00 += f; m10 += f; m20 += f; m30 += f;
	m01 += f; m11 += f; m21 += f; m31 += f;
	m02 += f; m12 += f; m22 += f; m32 += f;
	m03 += f; m13 += f; m23 += f; m33 += f;
	return *this;
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::operator += (const Mat4T &rhs)
{
	m00 += rhs.m00; m10 += rhs.m10; m20 += rhs.m20; m30 += rhs.m30;
	m01 += rhs.m01; m11 += rhs.m11; m21 += rhs.m21; m31 += rhs.m31;
	m02 += rhs.m02; m12 += rhs.m12; m22 += rhs.m22; m32 += rhs.m32;
	m03 += rhs.m03; m13 += rhs.m13; m23 += rhs.m23; m33 += rhs.m33;
	return *this;
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::operator -= (const T f)
{
	m00 -= f; m10 -= f; m20 -= f; m30 -= f;
	m01 -= f; m11 -= f; m21 -= f; m31 -= f;
	m02 -= f; m12 -= f; m22 -= f; m32 -= f;
	m03 -= f; m13 -= f; m23 -= f; m33 -= f;
	return *this;
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::operator -= (const Mat4T &rhs)
{
	m00 -= rhs.m00; m10 -= rhs.m10; m20 -= rhs.m20; m30 -= rhs.m30;
	m01 -= rhs.m01; m11 -= rhs.m11; m21 -= rhs.m21; m31 -= rhs.m31;
	m02 -= rhs.m02; m12 -= rhs.m12; m22 -= rhs.m22; m32 -= rhs.m32;
	m03 -= rhs.m03; m13 -= rhs.m13; m23 -= rhs.m23; m33 -= rhs.m33;
	return *this;
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::operator *= (const T f)
{
	m00 *= f; m10 *= f; m20 *= f; m30 *= f;
	m01 *= f; m11 *= f; m21 *= f; m31 *= f;
	m02 *= f; m12 *= f; m22 *= f; m32 *= f;
	m03 *= f; m13 *= f; m23 *= f; m33 *= f;
	return *this;
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::operator *= (const Mat4T &rhs)
{
	T t00 = m00, t10 = m10, t20 = m20, t30 = m30;
	T t01 = m01, t11 = m11, t21 = m21, t31 = m31;
	T t02 = m02, t12 = m12, t22 = m22, t32 = m32;
	T t03 = m03, t13 = m13, t23 = m23, t33 = m33;

	m00 = t00 * rhs.m00 + t01 * rhs.m10 + t02 * rhs.m20 + t03 * rhs.m30;
	m01 = t00 * rhs.m01 + t01 * rhs.m11 + t02 * rhs.m21 + t03 * rhs.m31;
	m02 = t00 * rhs.m02 + t01 * rhs.m12 + t02 * rhs.m22 + t03 * rhs.m32;
	m03 = t00 * rhs.m03 + t01 * rhs.m13 + t02 * rhs.m23 + t03 * rhs.m33;

	m10 = t10 * rhs.m00 + t11 * rhs.m10 + t12 * rhs.m20 + t13 * rhs.m30;
	m11 = t10 * rhs.m01 + t11 * rhs.m11 + t12 * rhs.m21 + t13 * rhs.m31;
	m12 = t10 * rhs.m02 + t11 * rhs.m12 + t12 * rhs.m22 + t13 * rhs.m32;
	m13 = t10 * rhs.m03 + t11 * rhs.m13 + t12 * rhs.m23 + t13 * rhs.m33;

	m20 = t20 * rhs.m00 + t21 * rhs.m10 + t22 * rhs.m20 + t23 * rhs.m30;
	m21 = t20 * rhs.m01 + t21 * rhs.m11 + t22 * rhs.m21 + t23 * rhs.m31;
	m22 = t20 * rhs.m02 + t21 * rhs.m12 + t22 * rhs.m22 + t23 * rhs.m32;
	m23 = t20 * rhs.m03 + t21 * rhs.m13 + t22 * rhs.m23 + t23 * rhs.m33;

	m30 = t30 * rhs.m00 + t31 * rhs.m10 + t32 * rhs.m20 + t33 * rhs.m30;
	m31 = t30 * rhs.m01 + t31 * rhs.m11 + t32 * rhs.m21 + t33 * rhs.m31;
	m32 = t30 * rhs.m02 + t31 * rhs.m12 + t32 * rhs.m22 + t33 * rhs.m32;
	m33 = t30 * rhs.m03 + t31 * rhs.m13 + t32 * rhs.m23 + t33 * rhs.m33;

	return *this;
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::operator /= (const T f)
{
	m00 /= f; m10 /= f; m20 /= f; m30 /= f;
	m01 /= f; m11 /= f; m21 /= f; m31 /= f;
	m02 /= f; m12 /= f; m22 /= f; m32 /= f;
	m03 /= f; m13 /= f; m23 /= f; m33 /= f;
	return *this;
}

template <typename T>
inline bool Mat4T<T>::isIdentify() const
{
	return (
		Math::IsEqual(m00, 1) && Math::IsEqual(m10, 0) && Math::IsEqual(m20, 0) && Math::IsEqual(m30, 0) &&
		Math::IsEqual(m01, 0) && Math::IsEqual(m11, 1) && Math::IsEqual(m21, 0) && Math::IsEqual(m31, 0) &&
		Math::IsEqual(m02, 0) && Math::IsEqual(m12, 0) && Math::IsEqual(m22, 1) && Math::IsEqual(m32, 0) &&
		Math::IsEqual(m03, 0) && Math::IsEqual(m13, 0) && Math::IsEqual(m23, 0) && Math::IsEqual(m33, 1)
		)
}

template <typename T>
inline bool Mat4T<T>::isPerspective() const
{
	return (
		Math::IsNotEqual(m30, 0) || Math::IsNotEqual(m31, 0) || Math::IsNotEqual(m32, 0) || Math::IsNotEqual(m33, 1)
		)
}

template <typename T>
inline T Mat4T<T>::get(int row, int column) const
{
	return m[row + (column * 4)];
}

template <typename T>
inline Vec4T<T> Mat4T<T>::getRow(int row) const
{
	return Vec4T<T>(m[row], m[row + 4], m[row + 8], m[row + 12]);
}

template <typename T>
inline Vec4T<T> Mat4T<T>::getColumn(int col) const
{
	col *= 4;
	return Vec4T<T>(m[col], m[col + 1], m[col + 2], m[col + 3]);
}

template <typename T>
inline void Mat4T<T>::setRow(int row, const Vec4T<T>& v)
{
	m[row] = v.x;
	m[row + 4] = v.y; 
	m[row + 8] = v.z;
	m[row + 12] = v.w;
}

template <typename T>
inline void Mat4T<T>::setColumn(int col, const Vec4T<T>& v)
{
	col *= 4;
	m[col] = v.x;
	m[col + 1] = v.y;
	m[col + 2] = v.z;
	m[col + 3] = v.w;
}

template <typename T>
inline const T* Mat4T<T>::ptr() const
{
	return m;
}

template <typename T>
inline T* Mat4T<T>::ptr()
{
	return m;
}

//template <typename T>
//inline T Mat4T<T>::getDeterminant() const
//{
//
//}

template <typename T>
inline Mat4T<T>& Mat4T<T>::transpose()
{
	std::swap(m01, m10);
	std::swap(m02, m20);
	std::swap(m03, m30);
	std::swap(m12, m21);
	std::swap(m13, m31);
	std::swap(m23, m32);
	return *this;
}

// Invert 3D transformation matrix (not perspective). Adapted from graphics gems 2.
//--------------------------------------------------------------------------------
//                      |A 0|    |inverse(A)      0|
// inverse(M) = inverse(|   |) = |                 | (A is the upper-left 3 x 3 submatrix of M)
//  	                |C 1|    |-C * inverse(A) 1|
//---------------------------------------------------------------------------------
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
inline Mat4T<T>& Mat4T<T>::inverseGeneral3D()
{
	T det = 0;

	// Calculate the determinant of upper left 3x3 sub-matrix and
	// determine if the matrix is singular.
	T v0 = m11 * m22;
	T v1 = m21 * m02;
	T v2 = m01 * m12;
	T v3 = m11 * m02;
	T v4 = m01 * m22;
	T v5 = m21 * m12;

	det += m00 * v0;
	det += m10 * v1;
	det += m20 * v2;
	det -= m20 * v3;
	det -= m10 * v4;
	det -= m00 * v5;

	if (det * det < 1e-25)
	{
		zero();
		return *this;
	}
	
	det = (T)1.0 / det;
	T e00 = (v0 - v5) * det;
	T e01 = -(v4 - v1) * det;
	T e02 = (v2 - v3) * det;
	T e10 = -(m10 * m22 - m12 * m20) * det;
	T e11 = (m00 * m22 - m02 * m20) * det;
	T e12 = -(m00 * m12 - m02 * m10) * det;
	T e20 = (m10 * m21 - m11 * m20) * det;
	T e21 = -(m00 * m21 - m01 * m20) * det;
	T e22 = (m00 * m11 - m01 * m10) * det;

	// Do the translation part
	T e03 = -(m03 * e00 + m13 * e01 + m23 * e02);
	T e13 = -(m03 * e10 + m13 * e11 + m23 * e12);
	T e23 = -(m03 * e20 + m13 * e21 + m23 * e22);

	T e30 = 0;
	T e31 = 0;
	T e32 = 0;
	T e33 = 1;

	m00 = e00; m01 = e01; m02 = e02; m03 = e03;
	m10 = e10; m11 = e11; m12 = e12; m13 = e13;
	m20 = e20; m21 = e21; m22 = e22; m23 = e23;
	m30 = e30; m31 = e31; m32 = e32; m33 = e33;

	return *this;
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::inverseFull()
{
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::identity()
{
}
template <typename T>
inline Mat4T<T>& Mat4T<T>::zero()
{
}

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