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

// 4x4 matrix inversion by Gaussian reduction with partial pivoting followed by back/substitution;
template <typename T>
inline Mat4T<T>& Mat4T<T>::inverseFull()
{
#define SWAP_ROWS(a, b) PP_WRAP_CODE(T* _tmp = (a); (a) = (b); (b) = _tmp;)

	T mt[4][8];
	T m0, m1, m2, m3, s;
	T *r0, *r1, *r2, *r3;

	r0 = mt[0], r1 = mt[1], r2 = mt[2], r3 = mt[3];
	r0[0] = m00; r0[1] = m01; r0[2] = m02; r0[3] = m03;
	r0[4] = 1; r0[5] = 0; r0[6] = 0; r0[7] = 0;

	r1[0] = m10; r1[1] = m11; r1[2] = m12; r1[3] = m13;
	r1[4] = 0; r1[5] = 1; r1[6] = 0; r1[7] = 0;

	r2[0] = m20; r2[1] = m21; r2[2] = m22; r2[3] = m23;
	r2[4] = 0; r2[5] = 0; r2[6] = 1; r2[7] = 0;

	r3[0] = m30; r3[1] = m31; r3[2] = m32; r3[3] = m33;
	r3[4] = 0; r3[5] = 0; r3[6] = 0; r3[7] = 1;

	/* choose pivot - or die */
	if (std::abs(r3[0]) > std::abs(r2[0]))
		SWAP_ROWS(r3, r2);
	if (std::abs(r2[0]) > std::abs(r1[0]))
		SWAP_ROWS(r2, r1);
	if (std::abs(r1[0]) > std::abs(r0[0]))
		SWAP_ROWS(r1, r0);
	if (Math::IsEqual(r0[0], 0))
	{
		zero();
		return *this;
	}

	/* eliminate first variable     */
	m1 = r1[0] / r0[0]; m2 = r2[0] / r0[0]; m3 = r3[0] / r0[0];
	s = r0[1]; r1[1] -= m1 * s; r2[1] -= m2 * s; r3[1] -= m3 * s;
	s = r0[2]; r1[2] -= m1 * s; r2[2] -= m2 * s; r3[2] -= m3 * s;
	s = r0[3]; r1[3] -= m1 * s; r2[3] -= m2 * s; r3[3] -= m3 * s;
	s = r0[4];
	if (Math::IsNotEqual(s, 0))
	{
		r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s;
	}
	s = r0[5];
	if (Math::IsNotEqual(s, 0))
	{
		r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s;
	}
	s = r0[6];
	if (Math::IsNotEqual(s, 0))
	{
		r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s;
	}
	s = r0[7];
	if (Math::IsNotEqual(s, 0))
	{
		r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s;
	}

	/* choose pivot - or die */
	if (std::abs(r3[1]) > std::abs(r2[1]))
		SWAP_ROWS(r3, r2);
	if (std::abs(r2[1]) > std::abs(r1[1]))
		SWAP_ROWS(r2, r1);
	if (Math::IsEqual(r1[1], 0))
	{
		zero();
		return *this;
	}

	/* eliminate second variable */
	m2 = r2[1] / r1[1]; m3 = r3[1] / r1[1];
	r2[2] -= m2 * r1[2]; r3[2] -= m3 * r1[2];
	r2[3] -= m2 * r1[3]; r3[3] -= m3 * r1[3];
	s = r1[4]; 
	if (Math::IsNotEqual(s, 0))
	{
		r2[4] -= m2 * s; r3[4] -= m3 * s;
	}
	s = r1[5]; 
	if (Math::IsNotEqual(s, 0))
	{
		r2[5] -= m2 * s; r3[5] -= m3 * s;
	}
	s = r1[6]; 
	if (Math::IsNotEqual(s, 0))
	{
		r2[6] -= m2 * s; r3[6] -= m3 * s;
	}
	s = r1[7]; 
	if (Math::IsNotEqual(s, 0))
	{
		r2[7] -= m2 * s; r3[7] -= m3 * s;
	}

	/* choose pivot - or die */
	if (std::abs(r3[2]) > std::abs(r2[2]))
		SWAP_ROWS(r3, r2);
	if (Math::IsEqual(r2[2], 0))
	{
		zero();
		return *this;
	}

	/* eliminate third variable */
	m3 = r3[2] / r2[2];
	r3[3] -= m3 * r2[3]; r3[4] -= m3 * r2[4];
	r3[5] -= m3 * r2[5]; r3[6] -= m3 * r2[6];
	r3[7] -= m3 * r2[7];

	/* last check */
	if (Math::IsEqual(r3[3], 0))
	{
		zero();
		return *this;
	}

	s = T(1.0) / r3[3];          /* now back substitute row 3 */
	r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;

	m2 = r2[3];                /* now back substitute row 2 */
	s = T(1.0) / r2[2];
	r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2), r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
	m1 = r1[3];
	r1[4] -= r3[4] * m1; r1[5] -= r3[5] * m1, r1[6] -= r3[6] * m1; r1[7] -= r3[7] * m1;
	m0 = r0[3];
	r0[4] -= r3[4] * m0; r0[5] -= r3[5] * m0, r0[6] -= r3[6] * m0; r0[7] -= r3[7] * m0;

	m1 = r1[2];                /* now back substitute row 1 */
	s = T(1.0) / r1[1];
	r1[4] = s * (r1[4] - r2[4] * m1); r1[5] = s * (r1[5] - r2[5] * m1), r1[6] = s * (r1[6] - r2[6] * m1); r1[7] = s * (r1[7] - r2[7] * m1);
	m0 = r0[2];
	r0[4] -= r2[4] * m0; r0[5] -= r2[5] * m0, r0[6] -= r2[6] * m0; r0[7] -= r2[7] * m0;

	m0 = r0[1];                /* now back substitute row 0 */
	s = T(1.0) / r0[0];
	r0[4] = s * (r0[4] - r1[4] * m0); r0[5] = s * (r0[5] - r1[5] * m0), r0[6] = s * (r0[6] - r1[6] * m0); r0[7] = s * (r0[7] - r1[7] * m0);

	m00 = r0[4]; m01 = r0[5], m02 = r0[6]; m03 = r0[7];
	m10 = r1[4]; m11 = r1[5], m12 = r1[6]; m13 = r1[7];
	m20 = r2[4]; m21 = r2[5], m22 = r2[6]; m23 = r2[7];
	m30 = r3[4]; m31 = r3[5], m32 = r3[6]; m33 = r3[7];

#undef SWAP_ROWS
	return *this;
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::identity()
{
	m00 = 1; m01 = 0; m02 = 0; m03 = 0;
	m10 = 0; m11 = 1; m12 = 0; m13 = 0;
	m20 = 0; m21 = 0; m22 = 1; m23 = 0;
	m30 = 0; m31 = 0; m32 = 0; m33 = 1;
	return *this;
}
template <typename T>
inline Mat4T<T>& Mat4T<T>::zero()
{
	memset(m, 0, 16 * sizeof(T));
	return *this;
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::translate(const Vec3T<T>& v)
{
	return translate(v.x, v.y, v.z);
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::translate(T x, T y, T z)
{
	m03 += m00 * x + m01 * y + m02 * z;
	m13 += m10 * x + m11 * y + m12 * z;
	m23 += m20 * x + m21 * y + m22 * z;
	return *this;
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::makeTranslate(const Vec3T<T>& v)
{
	return makeTranslate(v.x, v.y, v.z);
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::makeTranslate(T x, T y, T z)
{
	m00 = 1; m10 = 0; m20 = 0; m30 = 0;
	m01 = 0; m11 = 1; m21 = 0; m31 = 0;
	m02 = 0; m12 = 0; m22 = 1; m32 = 0;
	m03 = x; m13 = y; m23 = z; m33 = 1;
	return *this;
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::scale(const Vec3T<T>& v)
{
	return scale(v.x, v.y, v.z);
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::scale(T x, T y, T z)
{
	m00 *= x; m01 *= y; m02 *= z;
	m10 *= x; m11 *= y; m12 *= z;
	m20 *= x; m21 *= y; m22 *= z;
	return *this;
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::makeScale(const Vec3T<T>& v)
{
	return makeScale(v.x, v.y, v.z);
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::makeScale(T x, T y, T z)
{
	m00 = x; m10 = 0; m20 = 0; m30 = 0;
	m01 = 0; m11 = y; m21 = 0; m31 = 0;
	m02 = 0; m12 = 0; m22 = z; m32 = 0;
	m03 = 0; m13 = 0; m23 = 0; m33 = 1;
	return *this;
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::rotate(const Vec3T<T>& axis, T radian)
{
	T c = std::cos(radian);
	T s = std::sin(radian);
	Vec3T<T> v = Vec3T<T>::Normalize(axis);

	T t = T(1) - c;
	T tx = t * v.x;
	T ty = t * v.y;
	T tz = t * v.z;
	T txy = tx * v.y;
	T txz = tx * v.z;
	T tyz = ty * v.z;
	T sx = s * v.x;
	T sy = s * v.y;
	T sz = s * v.z;

	Mat4T<T> rotate;

	rotate.m00 = c + tx * v.x;
	rotate.m10 = txy + sz;
	rotate.m20 = txz - sy;
	rotate.m30 = 0;

	rotate.m01 = txy - sz;
	rotate.m11 = c + ty * v.y;
	rotate.m21 = tyz + sx;
	rotate.m31 = 0;

	rotate.m02 = txz + sy;
	rotate.m12 = tyz - sx;
	rotate.m22 = c + tz * v.z;
	rotate.m32 = 0;

	rotate.m03 = 0;
	rotate.m13 = 0;
	rotate.m23 = 0;
	rotate.m33 = 1;

	*this = (rotate * (*this));
	return *this;
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::makeRotate(const Vec3T<T>& axis, T radian)
{
	T c = std::cos(radian);
	T s = std::sin(radian);
	Vec3T<T> v = Vec3T<T>::Normalize(axis);

	T t = T(1) - c;
	T tx = t * v.x;
	T ty = t * v.y;
	T tz = t * v.z;
	T txy = tx * v.y;
	T txz = tx * v.z;
	T tyz = ty * v.z;
	T sx = s * v.x;
	T sy = s * v.y;
	T sz = s * v.z;

	m00 = c + tx * v.x;
	m10 = txy + sz;
	m20 = txz - sy;
	m30 = 0;

	m01 = txy - sz;
	m11 = c + ty * v.y;
	m21 = tyz + sx;
	m31 = 0;

	m02 = txz + sy;
	m12 = tyz - sx;
	m22 = c + tz * v.z;
	m32 = 0;

	m03 = 0;
	m13 = 0;
	m23 = 0;
	m33 = 1;

	return *this;
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::perspective(T fov, T aspect, T near, T far)
{
	T tanHalfFov = std::tan(fov / (T)2);
	T cotanHalfFov = T(1) / tanHalfFov;
	T deltaZ = near - far;

	m00 = cotanHalfFov / aspect; m01 = 0; m02 = 0; m03 = 0;
	m10 = 0; m11 = cotanHalfFov; m12 = 0; m13 = 0;
	m20 = 0; m21 = 0; m22 = (near + far) / deltaZ; m23 = (T)2 * near * far / deltaZ;
	m30 = 0; m31 = 0; m32 = -1; m33 = 0;

	return *this;
}

template <typename T>
inline Mat4T<T>& Mat4T<T>::ortho(T left, T right, T bottom, T top, T near, T far)
{
	T dx = T(1) / (right - left);
	T dy = T(1) / (top - bottom);
	T dz = T(1) / (far - near);

	m00 = dx + dx; m01 = 0; m02 = 0; m03 = -(left + right) * dx;
	m10 = 0; m11 = dy + dy; m12 = 0; m13 = -(top + bottom) * dy;
	m20 = 0; m21 = 0; m22 = dz + dz; m23 = (near + far) * dz;
	m30 = 0; m31 = 0; m32 = 0; m33 = 1;
	return *this;
}

template <typename T>
inline Vec3T<T> Mat4T<T>::perspectiveTransform(const Vec3T<T>& v) const
{
	Vec3T<T> res;
	res.x = m00 * v.x + m01 * v.y + m02 * v.z + m03;
	res.y = m10 * v.x + m11 * v.y + m12 * v.z + m13;
	res.z = m20 * v.x + m21 * v.y + m22 * v.z + m23;
	T w = m30 * v.x + m31 * v.y + m32 * v.z + m33;
	if (std::abs(w) > 1.0e-7f)
	{
		T invW = T(1.0) / w;
		res.x *= invW;
		res.y *= invW;
		res.z *= invW;
	}
	else
	{
		res.x = T(0);
		res.y = T(0);
		res.z = T(0);
	}
	return res;
}

template <typename T>
inline Vec4T<T> Mat4T<T>::perspectiveTransform(const Vec4T<T>& v) const
{
	Vec4T<T> outVec;
	outVec.x = v.x * m00 + v.y * m01 + v.z * m02 + v.w * m03;
	outVec.y = v.x * m10 + v.y * m11 + v.z * m12 + v.w * m13;
	outVec.z = v.x * m20 + v.y * m21 + v.z * m22 + v.w * m23;
	outVec.w = v.x * m30 + v.y * m31 + v.z * m32 + v.w * m33;
	return outVec;
}

template <typename T>
inline Vec3T<T> Mat4T<T>::affineTransform(const Vec3T<T>& v) const
{
	Vec3T<T> outVec;
	outVec.x = v.x * m00 + v.y * m01 + v.z * m02 + m03;
	outVec.y = v.x * m10 + v.y * m11 + v.z * m12 + m13;
	outVec.z = v.x * m20 + v.y * m21 + v.z * m22 + m23;
	return outVec;
}

template <typename T>
inline Vec4T<T> Mat4T<T>::affineTransform(const Vec4T<T>& v) const
{
	Vec4T<T> outVec;
	outVec.x = v.x * m00 + v.y * m01 + v.z * m02 + m03 * v.w;
	outVec.y = v.x * m10 + v.y * m11 + v.z * m12 + m13 * v.w;
	outVec.z = v.x * m20 + v.y * m21 + v.z * m22 + m23 * v.w;
	outVec.w = v.w;
	return outVec;
}

template <typename T> 
inline bool operator == (const Mat4T<T> &a, const Mat4T<T> &b)
{
	// true if all vectors equal to each other
	return (Math::IsEqual(a.m00, b.m00) && Math::IsEqual(a.m01, b.m01) && Math::IsEqual(a.m02, b.m02) && Math::IsEqual(a.m03, b.m03) &&
		Math::IsEqual(a.m10, b.m10) && Math::IsEqual(a.m11, b.m11) && Math::IsEqual(a.m12, b.m12) && Math::IsEqual(a.m13, b.m13) &&
		Math::IsEqual(a.m20, b.m20) && Math::IsEqual(a.m21, b.m21) && Math::IsEqual(a.m22, b.m22) && Math::IsEqual(a.m23, b.m23) &&
		Math::IsEqual(a.m30, b.m30) && Math::IsEqual(a.m31, b.m31) && Math::IsEqual(a.m32, b.m32) && Math::IsEqual(a.m33, b.m33));
}

template <typename T>
inline bool operator != (const Mat4T<T> &a, const Mat4T<T> &b)
{
	// true if any one vector not-equal
	return (Math::IsNotEqual(a.m00, b.m00) || Math::IsNotEqual(a.m01, b.m01) || Math::IsNotEqual(a.m02, b.m02) || Math::IsNotEqual(a.m03, b.m03) ||
		Math::IsNotEqual(a.m10, b.m10) || Math::IsNotEqual(a.m11, b.m11) || Math::IsNotEqual(a.m12, b.m12) || Math::IsNotEqual(a.m13, b.m13) ||
		Math::IsNotEqual(a.m20, b.m20) || Math::IsNotEqual(a.m21, b.m21) || Math::IsNotEqual(a.m22, b.m22) || Math::IsNotEqual(a.m23, b.m23) ||
		Math::IsNotEqual(a.m30, b.m30) || Math::IsNotEqual(a.m31, b.m31) || Math::IsNotEqual(a.m32, b.m32) || Math::IsNotEqual(a.m33, b.m33));
}

template <typename T> 
inline Mat4T<T> operator + (const Mat4T<T> &a, const T f)
{
	Mat4T<T> result = a;
	result += f;
	return result;
}

template <typename T> 
inline Mat4T<T> operator + (const T f, const Mat4T<T> &a)
{
	Mat4T<T> result = a;
	result += f;
	return result;
}

template <typename T> 
inline Mat4T<T> operator + (const Mat4T<T> &a, const Mat4T<T> &b)
{
	Mat4T<T> result;

	result.m00 = a.m00 + b.m00;
	result.m01 = a.m01 + b.m01;
	result.m02 = a.m02 + b.m02;
	result.m03 = a.m03 + b.m03;

	result.m10 = a.m10 + b.m10;
	result.m11 = a.m11 + b.m11;
	result.m12 = a.m12 + b.m12;
	result.m13 = a.m13 + b.m13;

	result.m20 = a.m20 + b.m20;
	result.m21 = a.m21 + b.m21;
	result.m22 = a.m22 + b.m22;
	result.m23 = a.m23 + b.m23;

	result.m30 = a.m30 + b.m30;
	result.m31 = a.m31 + b.m31;
	result.m32 = a.m32 + b.m32;
	result.m33 = a.m33 + b.m33;

	return result;
}

template <typename T> 
inline Mat4T<T> operator - (const Mat4T<T> &a, const T f)
{
	Mat4T<T> result = a;
	result -= f;
	return result;
}

template <typename T> 
inline Mat4T<T> operator - (const T f, const Mat4T<T> &a)
{
	Mat4T<T> result = a;
	result -= f;
	return result;
}

template <typename T> 
inline Mat4T<T> operator - (const Mat4T<T> &a, const Mat4T<T> &b)
{
	Mat4T<T> result;

	result.m00 = a.m00 - b.m00;
	result.m01 = a.m01 - b.m01;
	result.m02 = a.m02 - b.m02;
	result.m03 = a.m03 - b.m03;

	result.m10 = a.m10 - b.m10;
	result.m11 = a.m11 - b.m11;
	result.m12 = a.m12 - b.m12;
	result.m13 = a.m13 - b.m13;

	result.m20 = a.m20 - b.m20;
	result.m21 = a.m21 - b.m21;
	result.m22 = a.m22 - b.m22;
	result.m23 = a.m23 - b.m23;

	result.m30 = a.m30 - b.m30;
	result.m31 = a.m31 - b.m31;
	result.m32 = a.m32 - b.m32;
	result.m33 = a.m33 - b.m33;

	return result;
}

template <typename T> 
inline Vec4T<T> operator * (const Mat4T<T> &m, const Vec4T<T> &v)
{
	return m.perspectiveTransform(v);
}

template <typename T> 
inline Vec3T<T> operator * (const Mat4T<T> &m, const Vec3T<T> &v)
{
	return m.perspectiveTransform(v);
}

template <typename T> 
inline Mat4T<T> operator * (const Mat4T<T> &a, const Mat4T<T> &b)
{
	Mat4T<T> result;

	result.m00 = a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20 + a.m03 * b.m30;
	result.m01 = a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21 + a.m03 * b.m31;
	result.m02 = a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22 + a.m03 * b.m32;
	result.m03 = a.m00 * b.m03 + a.m01 * b.m13 + a.m02 * b.m23 + a.m03 * b.m33;

	result.m10 = a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20 + a.m13 * b.m30;
	result.m11 = a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31;
	result.m12 = a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32;
	result.m13 = a.m10 * b.m03 + a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33;

	result.m20 = a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20 + a.m23 * b.m30;
	result.m21 = a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31;
	result.m22 = a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32;
	result.m23 = a.m20 * b.m03 + a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33;

	result.m30 = a.m30 * b.m00 + a.m31 * b.m10 + a.m32 * b.m20 + a.m33 * b.m30;
	result.m31 = a.m30 * b.m01 + a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31;
	result.m32 = a.m30 * b.m02 + a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32;
	result.m33 = a.m30 * b.m03 + a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33;

	return result;
}

template <typename T> 
inline Mat4T<T> operator * (const Mat4T<T> &a, const T f)
{
	Mat4T<T> result;

	result.m00 = a.m00 * f;
	result.m01 = a.m01 * f;
	result.m02 = a.m02 * f;
	result.m03 = a.m03 * f;

	result.m10 = a.m10 * f;
	result.m11 = a.m11 * f;
	result.m12 = a.m12 * f;
	result.m13 = a.m13 * f;

	result.m20 = a.m20 * f;
	result.m21 = a.m21 * f;
	result.m22 = a.m22 * f;
	result.m23 = a.m23 * f;

	result.m30 = a.m30 * f;
	result.m31 = a.m31 * f;
	result.m32 = a.m32 * f;
	result.m33 = a.m33 * f;

	return result;
}

template <typename T> 
inline Mat4T<T> operator * (const T f, const Mat4T<T> &a)
{
	Mat4T<T> result;

	result.m00 = f * a.m00;
	result.m01 = f * a.m01;
	result.m02 = f * a.m02;
	result.m03 = f * a.m03;

	result.m10 = f * a.m10;
	result.m11 = f * a.m11;
	result.m12 = f * a.m12;
	result.m13 = f * a.m13;

	result.m20 = f * a.m20;
	result.m21 = f * a.m21;
	result.m22 = f * a.m22;
	result.m23 = f * a.m23;

	result.m30 = f * a.m30;
	result.m31 = f * a.m31;
	result.m32 = f * a.m32;
	result.m33 = f * a.m33;

	return result;
}

template <typename T> 
inline Mat4T<T> operator / (const Mat4T<T> &a, const T f)
{
	Mat4T<T> result;

	T fInv = 1.0f / f;

	result.m00 = a.m00 * fInv;
	result.m01 = a.m01 * fInv;
	result.m02 = a.m02 * fInv;
	result.m03 = a.m03 * fInv;

	result.m10 = a.m10 * fInv;
	result.m11 = a.m11 * fInv;
	result.m12 = a.m12 * fInv;
	result.m13 = a.m13 * fInv;

	result.m20 = a.m20 * fInv;
	result.m21 = a.m21 * fInv;
	result.m22 = a.m22 * fInv;
	result.m23 = a.m23 * fInv;

	result.m30 = a.m30 * fInv;
	result.m31 = a.m31 * fInv;
	result.m32 = a.m32 * fInv;
	result.m33 = a.m33 * fInv;

	return result;
}
