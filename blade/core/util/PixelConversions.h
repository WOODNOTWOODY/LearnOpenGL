#ifndef __BLADE_PIXELCONVERSIONS_H__
#define __BLADE_PIXELCONVERSIONS_H__

BLADE_NAMESPACE_BEGIN

//////////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

template <ElementFormat PIX_FMT> struct PixelType {};

template <> struct PixelType<EF_R8> { uint8 r; };
template <> struct PixelType<EF_R8_SNORM> { int8 r; };
template <> struct PixelType<EF_R8_UINT> { uint8 r; };
template <> struct PixelType<EF_R8_SINT> { int8 r; };

template <> struct PixelType<EF_RG8> { uint8 r, g; };
template <> struct PixelType<EF_RG8_SNORM> { int8 r, g; };
template <> struct PixelType<EF_RG8_UINT> { uint8 r, g; };
template <> struct PixelType<EF_RG8_SINT> { int8 r, g; };

template <> struct PixelType<EF_RGB8> { uint8 r, g, b; };
template <> struct PixelType<EF_RGB8_SNORM> { int8 r, g, b; };
template <> struct PixelType<EF_RGB8_UINT> { uint8 r, g, b; };
template <> struct PixelType<EF_RGB8_SINT> { int8 r, g, b; };

template <> struct PixelType<EF_BGR8> { uint8 b, g, r; };

template <> struct PixelType<EF_RGBA8> { uint8 r, g, b, a; };
template <> struct PixelType<EF_RGBA8_SNORM> { int8 r, g, b, a; };
template <> struct PixelType<EF_RGBA8_UINT> { uint8 r, g, b, a; };
template <> struct PixelType<EF_RGBA8_SINT> { int8 r, g, b, a; };

template <> struct PixelType<EF_BGRA8> { uint8 b, g, r, a; };

template <> struct PixelType<EF_R16> { uint16 r; };
template <> struct PixelType<EF_R16_SNORM> { int16 r; };
template <> struct PixelType<EF_R16_UINT> { uint16 r; };
template <> struct PixelType<EF_R16_SINT> { int16 r; };

template <> struct PixelType<EF_RG16> { uint16 r, g; };
template <> struct PixelType<EF_RG16_SNORM> { int16 r, g; };
template <> struct PixelType<EF_RG16_UINT> { uint16 r, g; };
template <> struct PixelType<EF_RG16_SINT> { int16 r, g; };

template <> struct PixelType<EF_RGB16> { uint16 r, g, b; };
template <> struct PixelType<EF_RGB16_SNORM> { int16 r, g, b; };
template <> struct PixelType<EF_RGB16_UINT> { uint16 r, g, b; };
template <> struct PixelType<EF_RGB16_SINT> { int16 r, g, b; };

template <> struct PixelType<EF_RGBA16> { uint16 r, g, b, a; };
template <> struct PixelType<EF_RGBA16_SNORM> { int16 r, g, b, a; };
template <> struct PixelType<EF_RGBA16_UINT> { uint16 r, g, b, a; };
template <> struct PixelType<EF_RGBA16_SINT> { int16 r, g, b, a; };

template <> struct PixelType<EF_R32_UINT> { uint32 r; };
template <> struct PixelType<EF_R32_SINT> { int32 r; };
template <> struct PixelType<EF_R32_FLOAT> { float r; };

template <> struct PixelType<EF_RG32_UINT> { uint32 r, g; };
template <> struct PixelType<EF_RG32_SINT> { int32 r, g; };
template <> struct PixelType<EF_RG32_FLOAT> { float r, g; };

template <> struct PixelType<EF_RGB32_UINT> { uint32 r, g, b; };
template <> struct PixelType<EF_RGB32_SINT> { int32 r, g, b; };
template <> struct PixelType<EF_RGB32_FLOAT> { float r, g, b; };

template <> struct PixelType<EF_RGBA32_UINT> { uint32 r, g, b, a; };
template <> struct PixelType<EF_RGBA32_SINT> { int32 r, g, b, a; };
template <> struct PixelType<EF_RGBA32_FLOAT> { float r, g, b, a; };

template <> struct PixelType<EF_RGBA4> { uint16 r; };

template <> struct PixelType<EF_D16> { uint16 r; };
template <> struct PixelType<EF_D24> { uint32 r; };
template <> struct PixelType<EF_D24S8> { uint32 r; };
template <> struct PixelType<EF_D32_FLOAT> { uint32 r; };

#pragma pack(pop)

//////////////////////////////////////////////////////////////////////////

#define FMTCONVERTERID(from, to) (static_cast<uint>( (((from >> 52) & 255) << 8) | ((to >> 52) & 255) ))

/**
 * Convert a box of pixel from one type to another. Who needs automatic code 
 * generation when we have C++ templates and the policy design pattern.
 * 
 * @param   U       Policy class to facilitate pixel-to-pixel conversion. This class
 *    has at least two typedefs: SrcType and DstType. SrcType is the source element type,
 *    dstType is the destination element type. It also has a static method, pixelConvert, that
 *    converts a srcType into a dstType.
 */
template <class U> 
struct PixelBoxConverter 
{
	static void Conversion(const PixelBox &src, const PixelBox &dst)
	{
		typename U::SrcType *srcptr = static_cast<typename U::SrcType*>(src.data) + (src.left + src.top * src.rowPitch + src.front * src.slicePitch);
		typename U::DstType *dstptr = static_cast<typename U::DstType*>(dst.data) + (dst.left + dst.top * dst.rowPitch + dst.front * dst.slicePitch);

		const uint32 srcSliceSkip = src.getSliceSkip();
		const uint32 dstSliceSkip = dst.getSliceSkip();
		const uint32 k = src.right - src.left;

		for(uint32 z=src.front; z<src.back; ++z) 
		{
			for(uint32 y = src.top; y < src.bottom; ++y)
			{
				for(uint32 x = 0; x < k; x++)
				{
					U::PixelConvert(srcptr[x], dstptr[x]);
				}

				srcptr += src.rowPitch;
				dstptr += dst.rowPitch;
			}

			srcptr += srcSliceSkip;
			dstptr += dstSliceSkip;
		}
	}
};

template <ElementFormat src, ElementFormat dst> 
struct PixelConverter
{
	typedef PixelType<src>		SrcType;
	typedef PixelType<dst>		DstType;
};

struct RGBA8_TO_BGRA8: public PixelConverter <EF_RGBA8, EF_BGRA8>
{
	inline static void PixelConvert(const SrcType &src, DstType &dst)
	{
		dst.r = src.r;
		dst.g = src.g;
		dst.b = src.b;
		dst.a = src.a;
	}
};

struct BGRA8_TO_RGBA8: public PixelConverter <EF_BGRA8, EF_RGBA8>
{
	inline static void PixelConvert(const SrcType &src, DstType &dst)
	{
		dst.r = src.r;
		dst.g = src.g;
		dst.b = src.b;
		dst.a = src.a;
	}
};

struct BGRA8_TO_R8: public PixelConverter <EF_BGRA8, EF_R8>
{
	inline static void PixelConvert(const SrcType &src, DstType &dst)
	{
		dst.r = src.r;
	}
};

struct R8_TO_BGRA8: public PixelConverter <EF_R8, EF_BGRA8>
{
	inline static void PixelConvert(const SrcType &src, DstType &dst)
	{
		dst.r = src.r;
		dst.g = dst.b = 0x00;
		dst.a = 0xff;
	}
};

struct R8_TO_RGBA8: public PixelConverter <EF_R8, EF_RGBA8>
{
	inline static void PixelConvert(const SrcType &src, DstType &dst)
	{
		dst.r = src.r;
		dst.g = dst.b = 0x00;
		dst.a = 0xff;
	}
};

struct R8_TO_R16: public PixelConverter <EF_R8, EF_R16>
{
	inline static void PixelConvert(const SrcType &src, DstType &dst)
	{
		dst.r = (uint16)src.r;
	}
};

struct R16_TO_R8: public PixelConverter <EF_R16, EF_R8>
{
	inline static void PixelConvert(const SrcType &src, DstType &dst)
	{
		dst.r = (uint8)src.r;
	}
};

struct RGB8_TO_BGR8: public PixelConverter <EF_RGB8, EF_BGR8>
{
	inline static void PixelConvert(const SrcType &src, DstType &dst)
	{
		dst.b = src.b;
		dst.g = src.g;
		dst.r = src.r;
	}
};

struct RGB8_TO_RGBA8: public PixelConverter <EF_RGB8, EF_RGBA8>
{
	inline static void PixelConvert(const SrcType &src, DstType &dst)
	{
		dst.r = src.r;
		dst.g = src.g;
		dst.b = src.b;
		dst.a = 0xff;
	}
};

struct RGB8_TO_BGRA8: public PixelConverter <EF_RGB8, EF_BGRA8>
{
	inline static void PixelConvert(const SrcType &src, DstType &dst)
	{
		dst.b = src.b;
		dst.g = src.g;
		dst.r = src.r;
		dst.a = 0xff;
	}
};

struct BGR8_TO_RGB8: public PixelConverter <EF_BGR8, EF_RGB8>
{
	inline static void PixelConvert(const SrcType &src, DstType &dst)
	{
		dst.r = src.r;
		dst.g = src.g;
		dst.b = src.b;
	}
};

struct BGR8_TO_BGRA8: public PixelConverter <EF_BGR8, EF_BGRA8>
{
	inline static void PixelConvert(const SrcType &src, DstType &dst)
	{
		dst.b = src.b;
		dst.g = src.g;
		dst.r = src.r;
		dst.a = 0xff;
	}
};

struct BGR8_TO_RGBA8: public PixelConverter <EF_BGR8, EF_RGBA8>
{
	inline static void PixelConvert(const SrcType &src, DstType &dst)
	{
		dst.r = src.r;
		dst.g = src.g;
		dst.b = src.b;
		dst.a = 0xff;
	}
};

struct RGBA4_TO_RGBA8 : public PixelConverter <EF_RGBA4, EF_RGBA8>
{
	inline static void PixelConvert(const SrcType &src, DstType &dst)
	{
		dst.r = src.r & 0xf;
		dst.g = (src.r >> 4) & 0xf;
		dst.b = (src.r >> 8) & 0xf;
		dst.a = (src.r >> 12) & 0xf;
	}
};

struct D16_TO_RGBA8 : public PixelConverter <EF_D16, EF_RGBA8>
{
	inline static void PixelConvert(const SrcType &src, DstType &dst)
	{
		dst.g = dst.b = dst.r = (uint8)((float)src.r / (float)Math::MAX_UI16 * 256.0f);
		dst.a = 0xff;
	}
};

struct D24_TO_RGBA8 : public PixelConverter <EF_D24, EF_RGBA8>
{
	inline static void PixelConvert(const SrcType &src, DstType &dst)
	{
		dst.g = dst.b = dst.r = (uint8)((float)src.r / (float)Math::MAX_UI32 * 256.0f);
		dst.a = 0xff;
	}
};

struct D24S8_TO_RGBA8 : public PixelConverter <EF_D24S8, EF_RGBA8>
{
	inline static void PixelConvert(const SrcType &src, DstType &dst)
	{
		dst.g = dst.b = dst.r = (uint8)((float)src.r / (float)Math::MAX_UI32 * 256.0f);
		dst.a = 0xff;
	}
};

struct D32F_TO_RGBA8 : public PixelConverter <EF_D32_FLOAT, EF_RGBA8>
{
	inline static void PixelConvert(const SrcType &src, DstType &dst)
	{
		dst.g = dst.b = dst.r = (uint8)((float)src.r / (float)Math::MAX_UI32 * 256.0f);
		dst.a = 0xff;
	}
};

inline bool DoOptimizedConversion(const PixelBox &src, const PixelBox &dst)
{
	if(src.format == EF_RGBA8 && dst.format == EF_BGRA8) { PixelBoxConverter<RGBA8_TO_BGRA8>::Conversion(src, dst); return true; }
	else if(src.format == EF_BGRA8 && dst.format == EF_RGBA8) { PixelBoxConverter<BGRA8_TO_RGBA8>::Conversion(src, dst); return true; }
	else if(src.format == EF_BGRA8 && dst.format == EF_R8) { PixelBoxConverter<BGRA8_TO_R8>::Conversion(src, dst); return true; }
	else if(src.format == EF_R8 && dst.format == EF_BGRA8) { PixelBoxConverter<R8_TO_BGRA8>::Conversion(src, dst); return true; }
	else if(src.format == EF_R8 && dst.format == EF_RGBA8) { PixelBoxConverter<R8_TO_RGBA8>::Conversion(src, dst); return true; }
	else if(src.format == EF_R8 && dst.format == EF_R16) { PixelBoxConverter<R8_TO_R16>::Conversion(src, dst); return true; }
	else if(src.format == EF_R16 && dst.format == EF_R8) { PixelBoxConverter<R16_TO_R8>::Conversion(src, dst); return true; }
	else if(src.format == EF_RGB8 && dst.format == EF_BGR8) { PixelBoxConverter<RGB8_TO_BGR8>::Conversion(src, dst); return true; }
	else if(src.format == EF_RGB8 && dst.format == EF_RGBA8) { PixelBoxConverter<RGB8_TO_RGBA8>::Conversion(src, dst); return true; }
	else if(src.format == EF_BGR8 && dst.format == EF_RGB8) { PixelBoxConverter<BGR8_TO_RGB8>::Conversion(src, dst); return true; }
	else if (src.format == EF_BGR8 && dst.format == EF_BGRA8) { PixelBoxConverter<BGR8_TO_BGRA8>::Conversion(src, dst); return true; }
	else if (src.format == EF_RGBA4 && dst.format == EF_RGBA8) { PixelBoxConverter<RGBA4_TO_RGBA8>::Conversion(src, dst); return true; }
	else if (src.format == EF_D16 && dst.format == EF_RGBA8) { PixelBoxConverter<D16_TO_RGBA8>::Conversion(src, dst); return true; }
	else if (src.format == EF_D24 && dst.format == EF_RGBA8) { PixelBoxConverter<D24_TO_RGBA8>::Conversion(src, dst); return true; }
	else if (src.format == EF_D24S8 && dst.format == EF_RGBA8) { PixelBoxConverter<D24S8_TO_RGBA8>::Conversion(src, dst); return true; }
	else if (src.format == EF_D32_FLOAT && dst.format == EF_RGBA8) { PixelBoxConverter<D32F_TO_RGBA8>::Conversion(src, dst); return true; }
	else return false;
}

BLADE_NAMESPACE_END

#endif