#ifndef __BLADE_COLOR_H__
#define __BLADE_COLOR_H__

#include "math/MathLib.h"

BLADE_NAMESPACE_BEGIN

template <typename T>
class ColorT
{
public:	
#pragma pack(push, 1)
	union
	{
		struct 
		{
			T r, g, b, a;
		};
		T m[4];
	};
#pragma pack(pop)

public:
	ColorT() {}
	ColorT(const T *);
	ColorT(T r, T g, T b, T a = 1);

public:
	// casting
	operator uint32 () const;

	operator T* ();
	operator const T* () const;

	operator ColorT* ();
	operator const ColorT* () const;
	
	ColorT& operator += (const ColorT &color);
	ColorT& operator -= (const ColorT &color);
	ColorT& operator *= (const ColorT &color);
	ColorT& operator *= (T f);
	ColorT& operator /= (T f);
	ColorT operator + () const;
	ColorT operator - () const;
	ColorT operator + (const ColorT &color) const;
	ColorT operator - (const ColorT &color) const;
	ColorT operator * (const ColorT &color) const;
	ColorT operator * (T f) const;
	ColorT operator / (T f) const;
	T& operator [] (int index);
	const T& operator [] (int index) const;

	bool operator == (const ColorT &color) const;
	bool operator != (const ColorT &color) const;

public:
	void		set(T fr, T fg, T fb, T fa = 1);
	void		setARGB(uint32 argb);
	void		setABGR(uint32 abgr);
	void		setRGBA(uint32 rgba);
	uint32		getARGB() const;
	uint32		getABGR() const;
	uint32		getRGBA() const;
	uint32		getBGRA() const;
	ColorT&		saturate();
	ColorT&		pow(T exponent);
};

template <typename T> ColorT<T> operator * (T f, const ColorT<T> &color);

#include "Color-inl.h"

typedef ColorT<float>		Color;
typedef ColorT<Byte>		Colorb;
typedef ColorT<int>			Colori;
typedef ColorT<float>		Colorf;
typedef ColorT<double>		Colord;

extern BLADE_CORE_API const Colorf COLORF_ZERO;
extern BLADE_CORE_API const Colorf COLORF_RED;
extern BLADE_CORE_API const Colorf COLORF_GREEN;
extern BLADE_CORE_API const Colorf COLORF_BLUE;
extern BLADE_CORE_API const Colorf COLORF_BLACK;
extern BLADE_CORE_API const Colorf COLORF_WHITE;
extern BLADE_CORE_API const Colorf COLORF_YELLOW;
extern BLADE_CORE_API const Colorf COLORF_CYAN;
extern BLADE_CORE_API const Colorf COLORF_PURPLE;
extern BLADE_CORE_API const Colorf COLORF_DEFAULT;

extern BLADE_CORE_API const Colord COLORD_ZERO;
extern BLADE_CORE_API const Colord COLORD_RED;
extern BLADE_CORE_API const Colord COLORD_GREEN;
extern BLADE_CORE_API const Colord COLORD_BLUE;
extern BLADE_CORE_API const Colord COLORD_BLACK;
extern BLADE_CORE_API const Colord COLORD_WHITE;
extern BLADE_CORE_API const Colord COLORD_YELLOW;
extern BLADE_CORE_API const Colord COLORD_CYAN;
extern BLADE_CORE_API const Colord COLORD_PURPLE;

#define COLOR_ZERO		COLORF_ZERO
#define COLOR_RED		COLORF_RED
#define COLOR_GREEN		COLORF_GREEN
#define COLOR_BLUE		COLORF_BLUE
#define COLOR_BLACK		COLORF_BLACK
#define COLOR_WHITE		COLORF_WHITE
#define COLOR_YELLOW	COLORF_YELLOW
#define COLOR_CYAN		COLORF_CYAN
#define COLOR_PURPLE	COLORF_PURPLE
#define COLOR_DEFAULT	COLORF_DEFAULT
#define COLOR_INVALID	COLORF_INVALID

BLADE_NAMESPACE_END

#endif
