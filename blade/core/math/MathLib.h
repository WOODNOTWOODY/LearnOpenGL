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
}

BLADE_NAMESPACE_END

#endif