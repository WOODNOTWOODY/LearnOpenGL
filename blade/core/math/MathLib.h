#ifndef __BLADE_MATHLIB_H__
#define __BLADE_MATHLIB_H__

BLADE_NAMESPACE_BEGIN

namespace Math
{
	extern BLADE_CORE_API const float PI;				//!< 3.14159265358979323846264338327950288419716939937511
	extern BLADE_CORE_API const float PI_2;				//!< Math::PI * 2.0
	extern BLADE_CORE_API const float PI_DIV2;			//!< Math::PI / 2.0
	extern BLADE_CORE_API const float PI_DIV3;			//!< Math::PI / 3.0
	extern BLADE_CORE_API const float PI_DIV4;			//!< Math::PI / 4.0
	extern BLADE_CORE_API const float PI_DIV5;			//!< Math::PI / 5.0
	extern BLADE_CORE_API const float PI_DIV6;			//!< Math::PI / 6.0
	extern BLADE_CORE_API const float PI_DIV8;			//!< Math::PI / 8.0
	extern BLADE_CORE_API const float PI_DIV180;		//!< 180 / Math::PI
	extern BLADE_CORE_API const float MAX_FLOAT;		//!< 3.402823466e+38F

	template <typename T>
	inline bool IsEqual(T lhs, T rhs)
	{
		return (lhs == rhs);
	}

	template <>
	inline bool IsEqual<float>(float lhs, float rhs)
	{
		return (std::abs(lhs - rhs) <= 0.0001f);
	}

	template <>
	inline bool IsEqual<double>(double lhs, double rhs)
	{
		return (std::abs(lhs - rhs) <= 0.0001);
	}

	template <typename T>
	inline bool IsNotEqual(T lhs, T rhs)
	{
		return (lhs != rhs);
	}

	template <>
	inline bool IsNotEqual<float>(float lhs, float rhs)
	{
		return (std::abs(lhs - rhs) > 0.0001f);
	}

	template <>
	inline bool IsNotEqual<double>(double lhs, double rhs)
	{
		return (std::abs(lhs - rhs) > 0.0001f);
	}

	//Read a n*8 bits integer value to memory in native endian.
	inline uint32 IntRead(const void* src, int n)
	{
		switch (n)
		{
		case 1:
			return ((uint8*)src)[0];
		case 2:
			return ((uint16*)src)[0];
		case 3:
			return ((uint32)((uint8*)src)[0]) | ((uint32)((uint8*)src)[1] << 8) | ((uint32)((uint8*)src)[2] << 16);
		case 4:
			return ((uint32*)src)[0];
		}
		return 0; // ?
	}

	// Write a n*8 bits integer value to memory in native endian.
	inline void IntWrite(void *pDest, int n, uint32 value)
	{
		switch (n)
		{
		case 1:
			((uint8*)pDest)[0] = (uint8)value;
			break;
		case 2:
			((uint16*)pDest)[0] = (uint16)value;
			break;
		case 3:
			((uint8*)pDest)[2] = (uint8)((value >> 16) & 0xFF);
			((uint8*)pDest)[1] = (uint8)((value >> 8) & 0xFF);
			((uint8*)pDest)[0] = (uint8)(value & 0xFF);
			break;
		case 4:
			((uint32*)pDest)[0] = (uint32)value;
			break;
		}
	}

	/**
	* Convert floating point color channel value between 0.0 and 1.0 (otherwise clamped)
	* to integer of a certain number of bits. Works for any value of bits between 0 and 31.
	*/
	inline uint32 FloatToFixed(float value, uint32 bits)
	{
		if (value <= 0.0f)
			return 0;
		else if (value >= 1.0f)
			return (1 << bits) - 1;
		else
			return (uint32)(value * (1 << bits));
	}

	// Fixed point to float
	inline float FixedToFloat(uint32 value, uint32 bits)
	{
		return (float)value / (float)((1 << bits) - 1);
	}

	// Converts float in uint32 format to a a half in uint16 format
	inline uint16 FloatToHalfI(uint32 i)
	{
		register int s = (i >> 16) & 0x00008000;
		register int e = ((i >> 23) & 0x000000ff) - (127 - 15);
		register int m = i & 0x007fffff;

		if (e <= 0)
		{
			if (e < -10)
			{
				return 0;
			}
			m = (m | 0x00800000) >> (1 - e);

			return static_cast<uint16>(s | (m >> 13));
		}
		else if (e == 0xff - (127 - 15))
		{
			if (m == 0) // Inf
			{
				return static_cast<uint16>(s | 0x7c00);
			}
			else    // NAN
			{
				m >>= 13;
				return static_cast<uint16>(s | 0x7c00 | m | (m == 0));
			}
		}
		else
		{
			if (e > 30) // Overflow
			{
				return static_cast<uint16>(s | 0x7c00);
			}

			return static_cast<uint16>(s | (e << 10) | (m >> 13));
		}
	}

	// Convert a float32 to a float16 (NV_half_float)
	inline uint16 FloatToHalf(float i)
	{
		union { float f; uint32 i; } v;
		v.f = i;
		return FloatToHalfI(v.i);
	}

	//Converts a half in uint16 format to a float in uint32 format
	inline uint32 HalfToFloatI(uint16 y)
	{
		register int s = (y >> 15) & 0x00000001;
		register int e = (y >> 10) & 0x0000001f;
		register int m = y & 0x000003ff;

		if (e == 0)
		{
			if (m == 0) // Plus or minus zero
			{
				return s << 31;
			}
			else // unnormalized number -- renormalized it
			{
				while (!(m & 0x00000400))
				{
					m <<= 1;
					e -= 1;
				}

				e += 1;
				m &= ~0x00000400;
			}
		}
		else if (e == 31)
		{
			if (m == 0) // Inf
			{
				return (s << 31) | 0x7f800000;
			}
			else // NaN
			{
				return (s << 31) | 0x7f800000 | (m << 13);
			}
		}

		e = e + (127 - 15);
		m = m << 13;

		return (s << 31) | (e << 23) | m;
	}

	// Convert a float16 (NV_half_float) to a float32
	inline float HalfToFloat(uint16 y)
	{
		union { float f; uint32 i; } v;
		v.i = HalfToFloatI(y);
		return v.f;
	}
}

BLADE_NAMESPACE_END

#endif