#ifndef __BLADE_ELEMENT_H__
#define __BLADE_ELEMENT_H__

#include "Color.h"

BLADE_NAMESPACE_BEGIN

/**
* Flags defining some on/off properties of element formats
*/
enum ElementFormatFlag
{
	// Format is in native endian. Generally true for the 16, 24 and 32 bits
	// formats which can be represented as machine integers.
	EFF_NATIVE = 0x00000001,
	// This format has an alpha channel
	EFF_ALPHA = 0x00000002,
	// This format is compressed. This invalidates the values in elemBytes,
	// elemBits and the bit counts as these might not be fixed in a compressed format.
	EFF_COMPRESSED = 0x00000004,
	// This is a floating point format
	EFF_FLOAT = 0x00000008,
	// This is a depth format (for depth textures)
	EFF_DEPTH = 0x00000010,
	// This is a stencil format
	EFF_STENCIL = 0x00000020,
	// Standard RGB (gamma = 2.2)
	EFF_SRGB = 0x00000040,
};

enum ElementChannel
{
	EC_NONE = 0,
	EC_R = 1,		// red
	EC_G = 2,		// green
	EC_B = 3,		// blue
	EC_A = 4,		// alpha
	EC_D = 5,		// depth
	EC_S = 6,		// stencil
};

enum ElementType
{
	ET_NONE,
	ET_UNORM,
	ET_SNORM,
	ET_UINT,
	ET_SINT,
	ET_UFLOAT,
	ET_FLOAT,
};

//////////////////////////////////////////////////////////////////////////
/*
64       56       48  45  42  39  36     30     24     18     12  9   6   3   0
|00000000|00000000|000|000|000|000|000000|000000|000000|000000|000|000|000|000|
|   tag  |  flag  | t3| t2| t1| t0|  s3  |  s2  |  s1  |  s0  | c3| c2| c1| c0|
*/

template <uint64 c0, uint64 c1, uint64 c2, uint64 c3,
	uint64 s0, uint64 s1, uint64 s2, uint64 s3,
	uint64 t0, uint64 t1, uint64 t2, uint64 t3,
	uint64 flag, uint64 tag>
struct _ELEMENT4
{
	static uint64 const FORMAT = (c0 << 0) | (c1 << 3) | (c2 << 6) | (c3 << 9) |
		(s0 << 12) | (s1 << 18) | (s2 << 24) | (s3 << 30) |
		(t0 << 36) | (t1 << 39) | (t2 << 42) | (t3 << 45) |
		(flag << 48) | (tag << 56);
};

template<uint64 c0, uint64 c1, uint64 c2, uint64 s0, uint64 s1, uint64 s2, uint64 t0, uint64 t1, uint64 t2, uint64 flag, uint64 tag>
struct _ELEMENT3 { static uint64 const FORMAT = _ELEMENT4<c0, c1, c2, 0, s0, s1, s2, 0, t0, t1, t2, 0, flag, tag>::FORMAT; };

template<uint64 c0, uint64 c1, uint64 s0, uint64 s1, uint64 t0, uint64 t1, uint64 flag, uint64 tag>
struct _ELEMENT2 { static uint64 const FORMAT = _ELEMENT3<c0, c1, 0, s0, s1, 0, t0, t1, 0, flag, tag>::FORMAT; };

template<uint64 c0, uint64 s0, uint64 t0, uint64 flag, uint64 tag>
struct _ELEMENT1 { static uint64 const FORMAT = _ELEMENT2<c0, 0, s0, 0, t0, 0, flag, tag>::FORMAT; };

typedef uint64 ElementFormat;

//////////////////////////////////////////////////////////////////////////
// Unknown format.
const ElementFormat EF_UNKNOWN = _ELEMENT1<EC_NONE, 0, ET_NONE, 0, 0>::FORMAT;

// 8-bit per channel format

// 8-bit format, all bits red.
const ElementFormat EF_R8 = _ELEMENT1<EC_R, 8, ET_UNORM, EFF_NATIVE, 0>::FORMAT;
const ElementFormat EF_R8_SNORM = _ELEMENT1<EC_R, 8, ET_SNORM, EFF_NATIVE, 0>::FORMAT;
const ElementFormat EF_R8_UINT = _ELEMENT1<EC_R, 8, ET_UINT, EFF_NATIVE, 0>::FORMAT;
const ElementFormat EF_R8_SINT = _ELEMENT1<EC_R, 8, ET_SINT, EFF_NATIVE, 0>::FORMAT;

// 8-bit pixel format, all bits alpha
const ElementFormat  EF_A8 = _ELEMENT1<EC_A, 8, ET_SINT, EFF_NATIVE | EFF_ALPHA, 0>::FORMAT;

// 16-bit, 2-channel floating point format, 8-bit red, 8-bit green
const ElementFormat  EF_RG8 = _ELEMENT2<EC_R, EC_G, 8, 8, ET_UNORM, ET_UNORM, EFF_NATIVE, 0>::FORMAT;
const ElementFormat  EF_RG8_SNORM = _ELEMENT2<EC_R, EC_G, 8, 8, ET_SNORM, ET_SNORM, EFF_NATIVE, 0>::FORMAT;
const ElementFormat  EF_RG8_UINT = _ELEMENT2<EC_R, EC_G, 8, 8, ET_UINT, ET_UINT, EFF_NATIVE, 0>::FORMAT;
const ElementFormat  EF_RG8_SINT = _ELEMENT2<EC_R, EC_G, 8, 8, ET_SINT, ET_SINT, EFF_NATIVE, 0>::FORMAT;

// 24-bit format, 8 bits for red, green and blue.
const ElementFormat  EF_RGB8 = _ELEMENT3<EC_R, EC_G, EC_B, 8, 8, 8, ET_UNORM, ET_UNORM, ET_UNORM, EFF_NATIVE, 0>::FORMAT;
const ElementFormat  EF_RGB8_SNORM = _ELEMENT3<EC_R, EC_G, EC_B, 8, 8, 8, ET_SNORM, ET_SNORM, ET_SNORM, EFF_NATIVE, 0>::FORMAT;
const ElementFormat  EF_RGB8_UINT = _ELEMENT3<EC_R, EC_G, EC_B, 8, 8, 8, ET_UINT, ET_UINT, ET_UINT, EFF_NATIVE, 0>::FORMAT;
const ElementFormat  EF_RGB8_SINT = _ELEMENT3<EC_R, EC_G, EC_B, 8, 8, 8, ET_SINT, ET_SINT, ET_SINT, EFF_NATIVE, 0>::FORMAT;

// 24-bit format, 8 bits for blue, green and red.
const ElementFormat  EF_BGR8 = _ELEMENT3<EC_B, EC_G, EC_R, 8, 8, 8, ET_UNORM, ET_UNORM, ET_UNORM, EFF_NATIVE, 0>::FORMAT;

// 32-bit format, 8 bits for red, green, blue and alpha.
const ElementFormat  EF_RGBA8 = _ELEMENT4<EC_R, EC_G, EC_B, EC_A, 8, 8, 8, 8, ET_UNORM, ET_UNORM, ET_UNORM, ET_UNORM, EFF_NATIVE | EFF_ALPHA, 0>::FORMAT;
const ElementFormat  EF_RGBA8_SNORM = _ELEMENT4<EC_R, EC_G, EC_B, EC_A, 8, 8, 8, 8, ET_SNORM, ET_SNORM, ET_SNORM, ET_SNORM, EFF_NATIVE | EFF_ALPHA, 0>::FORMAT;
const ElementFormat  EF_RGBA8_UINT = _ELEMENT4<EC_R, EC_G, EC_B, EC_A, 8, 8, 8, 8, ET_UINT, ET_UINT, ET_UINT, ET_UINT, EFF_NATIVE | EFF_ALPHA, 0>::FORMAT;
const ElementFormat  EF_RGBA8_SINT = _ELEMENT4<EC_R, EC_G, EC_B, EC_A, 8, 8, 8, 8, ET_SINT, ET_SINT, ET_SINT, ET_SINT, EFF_NATIVE | EFF_ALPHA, 0>::FORMAT;

// 32-bit format, 8 bits for blue, green and red.
const ElementFormat  EF_BGRA8 = _ELEMENT4<EC_B, EC_G, EC_R, EC_A, 8, 8, 8, 8, ET_UNORM, ET_UNORM, ET_UNORM, ET_UNORM, EFF_NATIVE | EFF_ALPHA, 0>::FORMAT;

//////////////////////////////////////////////////////////////////////////
// 16-bit per channel format

// 16-bit format, all bits red.
const ElementFormat  EF_R16 = _ELEMENT1<EC_R, 16, ET_UNORM, 0, 0>::FORMAT;
const ElementFormat  EF_R16_SNORM = _ELEMENT1<EC_R, 16, ET_SNORM, 0, 0>::FORMAT;
const ElementFormat  EF_R16_UINT = _ELEMENT1<EC_R, 16, ET_UINT, 0, 0>::FORMAT;
const ElementFormat  EF_R16_SINT = _ELEMENT1<EC_R, 16, ET_SINT, 0, 0>::FORMAT;
const ElementFormat  EF_R16_FLOAT = _ELEMENT1<EC_R, 16, ET_FLOAT, EFF_FLOAT, 0>::FORMAT;

// 32-bit, 2-channel floating point format, 16-bit red, 16-bit green
const ElementFormat  EF_RG16 = _ELEMENT2<EC_R, EC_G, 16, 16, ET_UNORM, ET_UNORM, 0, 0>::FORMAT;
const ElementFormat  EF_RG16_SNORM = _ELEMENT2<EC_R, EC_G, 16, 16, ET_SNORM, ET_SNORM, 0, 0>::FORMAT;
const ElementFormat  EF_RG16_UINT = _ELEMENT2<EC_R, EC_G, 16, 16, ET_UINT, ET_UINT, 0, 0>::FORMAT;
const ElementFormat  EF_RG16_SINT = _ELEMENT2<EC_R, EC_G, 16, 16, ET_SINT, ET_SINT, 0, 0>::FORMAT;
const ElementFormat  EF_RG16_FLOAT = _ELEMENT2<EC_R, EC_G, 16, 16, ET_FLOAT, ET_FLOAT, EFF_FLOAT, 0>::FORMAT;

// 48-bit format, 16 bits for red, green and blue.
const ElementFormat  EF_RGB16 = _ELEMENT3<EC_R, EC_G, EC_B, 16, 16, 16, ET_UNORM, ET_UNORM, ET_UNORM, 0, 0>::FORMAT;
const ElementFormat  EF_RGB16_SNORM = _ELEMENT3<EC_R, EC_G, EC_B, 16, 16, 16, ET_SNORM, ET_SNORM, ET_SNORM, 0, 0>::FORMAT;
const ElementFormat  EF_RGB16_UINT = _ELEMENT3<EC_R, EC_G, EC_B, 16, 16, 16, ET_UINT, ET_UINT, ET_UINT, 0, 0>::FORMAT;
const ElementFormat  EF_RGB16_SINT = _ELEMENT3<EC_R, EC_G, EC_B, 16, 16, 16, ET_SINT, ET_SINT, ET_SINT, 0, 0>::FORMAT;
const ElementFormat  EF_RGB16_FLOAT = _ELEMENT3<EC_R, EC_G, EC_B, 16, 16, 16, ET_FLOAT, ET_FLOAT, ET_FLOAT, EFF_FLOAT, 0>::FORMAT;

// 64-bit format, 16 bits for red, green, blue and alpha.
const ElementFormat  EF_RGBA16 = _ELEMENT4<EC_R, EC_G, EC_B, EC_A, 16, 16, 16, 16, ET_UNORM, ET_UNORM, ET_UNORM, ET_UNORM, EFF_ALPHA, 0>::FORMAT;
const ElementFormat  EF_RGBA16_SNORM = _ELEMENT4<EC_R, EC_G, EC_B, EC_A, 16, 16, 16, 16, ET_SNORM, ET_SNORM, ET_SNORM, ET_SNORM, EFF_ALPHA, 0>::FORMAT;
const ElementFormat  EF_RGBA16_UINT = _ELEMENT4<EC_R, EC_G, EC_B, EC_A, 16, 16, 16, 16, ET_UINT, ET_UINT, ET_UINT, ET_UINT, EFF_ALPHA, 0>::FORMAT;
const ElementFormat  EF_RGBA16_SINT = _ELEMENT4<EC_R, EC_G, EC_B, EC_A, 16, 16, 16, 16, ET_SINT, ET_SINT, ET_SINT, ET_SINT, EFF_ALPHA, 0>::FORMAT;
const ElementFormat  EF_RGBA16_FLOAT = _ELEMENT4<EC_R, EC_G, EC_B, EC_A, 16, 16, 16, 16, ET_FLOAT, ET_FLOAT, ET_FLOAT, ET_FLOAT, EFF_FLOAT | EFF_ALPHA, 0>::FORMAT;

//////////////////////////////////////////////////////////////////////////
// 32-bit per channel format

// 32-bit format, all bits red.
const ElementFormat  EF_R32_UINT = _ELEMENT1<EC_R, 32, ET_UINT, 0, 0>::FORMAT;
const ElementFormat  EF_R32_SINT = _ELEMENT1<EC_R, 32, ET_SINT, 0, 0>::FORMAT;
const ElementFormat  EF_R32_FLOAT = _ELEMENT1<EC_R, 32, ET_FLOAT, EFF_FLOAT, 0>::FORMAT;

// 64-bit, 2-channel floating point format, 32-bit red, 32-bit green
const ElementFormat  EF_RG32_UINT = _ELEMENT2<EC_R, EC_G, 32, 32, ET_UINT, ET_UINT, 0, 0>::FORMAT;
const ElementFormat  EF_RG32_SINT = _ELEMENT2<EC_R, EC_G, 32, 32, ET_SINT, ET_SINT, 0, 0>::FORMAT;
const ElementFormat  EF_RG32_FLOAT = _ELEMENT2<EC_R, EC_G, 32, 32, ET_FLOAT, ET_FLOAT, EFF_FLOAT, 0>::FORMAT;

// 96-bit format, 32 bits for red, green and blue.
const ElementFormat  EF_RGB32_UINT = _ELEMENT3<EC_R, EC_G, EC_B, 32, 32, 32, ET_UINT, ET_UINT, ET_UINT, 0, 0>::FORMAT;
const ElementFormat  EF_RGB32_SINT = _ELEMENT3<EC_R, EC_G, EC_B, 32, 32, 32, ET_SINT, ET_SINT, ET_SINT, 0, 0>::FORMAT;
const ElementFormat  EF_RGB32_FLOAT = _ELEMENT3<EC_R, EC_G, EC_B, 32, 32, 32, ET_FLOAT, ET_FLOAT, ET_FLOAT, EFF_FLOAT, 0>::FORMAT;

// 128-bit format, 32 bits for red, green, blue and alpha.
const ElementFormat  EF_RGBA32_UINT = _ELEMENT4<EC_R, EC_G, EC_B, EC_A, 32, 32, 32, 32, ET_UINT, ET_UINT, ET_UINT, ET_UINT, EFF_ALPHA, 0>::FORMAT;
const ElementFormat  EF_RGBA32_SINT = _ELEMENT4<EC_R, EC_G, EC_B, EC_A, 32, 32, 32, 32, ET_SINT, ET_SINT, ET_SINT, ET_SINT, EFF_ALPHA, 0>::FORMAT;
const ElementFormat  EF_RGBA32_FLOAT = _ELEMENT4<EC_R, EC_G, EC_B, EC_A, 32, 32, 32, 32, ET_FLOAT, ET_FLOAT, ET_FLOAT, ET_FLOAT, EFF_FLOAT | EFF_ALPHA, 0>::FORMAT;

//////////////////////////////////////////////////////////////////////////
// special format

// 16-bit format, 5 bits for red, 6 bits for green, 5 bits for blue.
const ElementFormat  EF_R5G6B5 = _ELEMENT3<EC_R, EC_G, EC_B, 5, 6, 5, ET_UNORM, ET_UNORM, ET_UNORM, EFF_NATIVE, 0>::FORMAT;

// 16-bit format, 4 bits for red, green, blue and alpha.
const ElementFormat  EF_RGBA4 = _ELEMENT4<EC_R, EC_G, EC_B, EC_A, 4, 4, 4, 4, ET_UNORM, ET_UNORM, ET_UNORM, ET_UNORM, EFF_NATIVE | EFF_ALPHA, 0>::FORMAT;

// 16-bit format 5 bits for red, green, blue, 1 bit for alpha.
const ElementFormat  EF_RGB5A1 = _ELEMENT4<EC_R, EC_G, EC_B, EC_A, 5, 5, 5, 1, ET_UNORM, ET_UNORM, ET_UNORM, ET_UNORM, EFF_NATIVE | EFF_ALPHA, 0>::FORMAT;

// 32-bit format 5 bits for red, green, blue, 2 bit for alpha.
const ElementFormat  EF_RGB10A2 = _ELEMENT4<EC_R, EC_G, EC_B, EC_A, 10, 10, 10, 2, ET_SINT, ET_SINT, ET_SINT, ET_SINT, EFF_NATIVE | EFF_ALPHA, 0>::FORMAT;
const ElementFormat  EF_RGB10A2_UINT = _ELEMENT4<EC_R, EC_G, EC_B, EC_A, 10, 10, 10, 2, ET_UINT, ET_UINT, ET_UINT, ET_UINT, EFF_NATIVE | EFF_ALPHA, 0>::FORMAT;

// Depth-stencil format.
const ElementFormat  EF_D16 = _ELEMENT1<EC_D, 16, ET_UINT, EFF_DEPTH, 0>::FORMAT;
const ElementFormat  EF_D24 = _ELEMENT1<EC_D, 24, ET_UINT, EFF_DEPTH, 0>::FORMAT;
const ElementFormat  EF_D24S8 = _ELEMENT2<EC_D, EC_S, 24, 8, ET_UNORM, ET_UINT, EFF_DEPTH | EFF_STENCIL, 0>::FORMAT;
const ElementFormat  EF_D32_FLOAT = _ELEMENT1<EC_D, 32, ET_UNORM, EFF_FLOAT | EFF_DEPTH, 0>::FORMAT;

#define ELEMENT_ID(format)					((format >> 56) & 0xFF)
#define ELEMENT_CHANNEL_COUNT(format)		(static_cast<Byte>(4 - !(format & 7) - !((format >> 3) & 7) - !((format >> 6) & 7) - !((format >> 9) & 7)))
#define ELEMENT_CHANNEL_SIZE(format, ch)	(ELEMENT_CHANNEL_BITS(format, ch) >> 3)
#define ELEMENT_CHANNEL_BITS(format, ch)	(static_cast<Byte>((format>>(6 * (ch >= EC_D? (ch - EC_D) : (ch - 1)) + 12)) & 0x3F))
#define ELEMENT_CHANNEL_TYPE(format, ch)	(static_cast<ElementType>((format >> (3 * (ch >= EC_D? (ch - EC_D) : (ch - 1)) + 36)) & 7))
#define ELEMENT_BITS(format)				(static_cast<Byte>(((format >> 12) & 0x3F) + ((format >> 18) & 0x3F) + ((format >> 24) & 0x3F)+((format >> 30) & 0x3F)))
#define ELEMENT_SIZE(format)				(ELEMENT_BITS(format) >> 3)
#define ELEMENT_FLAGS(format)				((format >> 48) & 0xFF)
#define ELEMENT_IS_NATIVE_ENDIAN(format)	((ELEMENT_FLAGS(format) & EFF_NATIVE) > 0)
#define ELEMENT_IS_COMPRESSED(format)		((ELEMENT_FLAGS(format) & EFF_COMPRESSED) > 0)
#define ELEMENT_IS_FLOATING(format)			((ELEMENT_FLAGS(format) & EFF_FLOAT) > 0)
#define ELEMENT_IS_SRGB(format)				((ELEMENT_FLAGS(format) & EFF_SRGB) > 0)
#define ELEMENT_HAS_ALPHA(format)			((ELEMENT_FLAGS(format) & EFF_ALPHA) > 0)
#define ELEMENT_HAS_DEPTH(format)			((ELEMENT_FLAGS(format) & EFF_DEPTH) > 0)
#define ELEMENT_HAS_STENCIL(format)			((ELEMENT_FLAGS(format) & EFF_STENCIL) > 0)

class BLADE_CORE_API ElementUtil
{
public:
	static std::string			GetFormatName(ElementFormat format);
	static ElementFormat		GetFormat(const std::string& fmtName);
	static uint32				GetMemorySize(uint32 width, uint32 height, uint32 depth, ElementFormat format);

	inline static ElementFormat	GetElement1Format(uint64 c0, uint64 s0, uint64 t0, uint64 tag = 0) { return GetElement2Format(c0, 0, s0, 0, t0, 0, tag); }
	inline static ElementFormat	GetElement2Format(uint64 c0, uint64 c1, uint64 s0, uint64 s1, uint64 t0, uint64 t1, uint64 tag = 0) { return GetElement3Format(c0, c1, 0, s0, s1, 0, t0, t1, 0, tag); }
	inline static ElementFormat	GetElement3Format(uint64 c0, uint64 c1, uint64 c2, uint64 s0, uint64 s1, uint64 s2, uint64 t0, uint64 t1, uint64 t2, uint64 tag = 0) { return GetElement4Format(c0, c1, c2, 0, s0, s1, s2, 0, t0, t1, t2, 0, tag); }
	static ElementFormat		GetElement4Format(uint64 c0, uint64 c1, uint64 c2, uint64 c3, uint64 s0, uint64 s1, uint64 s2, uint64 s3, uint64 t0, uint64 t1, uint64 t2, uint64 t3, uint64 tag = 0);

	static uint32				CalcSurfaceSize(uint32 width, uint32 height, uint32 depth, uint32 mipmaps, ElementFormat format);
	
};

BLADE_NAMESPACE_END

#endif
