#include "CoreStd.h"
#include "Element.h"

BLADE_NAMESPACE_BEGIN

#define TOSTR(s) #s

std::string ElementUtil::GetFormatName(ElementFormat format)
{
	switch (format)
	{
	case EF_UNKNOWN:		return TOSTR(EF_UNKNOWN);

	case EF_R8:				return TOSTR(EF_R8);
	case EF_R8_SNORM:		return TOSTR(EF_R8_SNORM);
	case EF_R8_UINT:		return TOSTR(EF_R8_UINT);
	case EF_R8_SINT:		return TOSTR(EF_R8_SINT);

	case EF_A8:				return TOSTR(EF_A8);

	case EF_RG8:			return TOSTR(EF_RG8);
	case EF_RG8_SNORM:		return TOSTR(EF_RG8_SNORM);
	case EF_RG8_UINT:		return TOSTR(EF_RG8_UINT);
	case EF_RG8_SINT:		return TOSTR(EF_RG8_SINT);

	case EF_RGB8:			return TOSTR(EF_RGB8);
	case EF_RGB8_SNORM:		return TOSTR(EF_RGB8_SNORM);
	case EF_RGB8_UINT:		return TOSTR(EF_RGB8_UINT);
	case EF_RGB8_SINT:		return TOSTR(EF_RGB8_SINT);

	case EF_BGR8:			return TOSTR(EF_BGR8);

	case EF_RGBA8:			return TOSTR(EF_RGBA8);
	case EF_RGBA8_SNORM:	return TOSTR(EF_RGBA8_SNORM);
	case EF_RGBA8_UINT:		return TOSTR(EF_RGBA8_UINT);
	case EF_RGBA8_SINT:		return TOSTR(EF_RGBA8_SINT);

	case EF_BGRA8:			return TOSTR(EF_BGRA8);

	case EF_R16:			return TOSTR(EF_R16);
	case EF_R16_SNORM:		return TOSTR(EF_R16_SNORM);
	case EF_R16_UINT:		return TOSTR(EF_R16_UINT);
	case EF_R16_SINT:		return TOSTR(EF_R16_SINT);
	case EF_R16_FLOAT:		return TOSTR(EF_R16_FLOAT);

	case EF_RG16:			return TOSTR(EF_RG16);
	case EF_RG16_SNORM:		return TOSTR(EF_RG16_SNORM);
	case EF_RG16_UINT:		return TOSTR(EF_RG16_UINT);
	case EF_RG16_SINT:		return TOSTR(EF_RG16_SINT);
	case EF_RG16_FLOAT:		return TOSTR(EF_RG16_FLOAT);

	case EF_RGB16:			return TOSTR(EF_RGB16);
	case EF_RGB16_SNORM:	return TOSTR(EF_RGB16_SNORM);
	case EF_RGB16_UINT:		return TOSTR(EF_RGB16_UINT);
	case EF_RGB16_SINT:		return TOSTR(EF_RGB16_SINT);
	case EF_RGB16_FLOAT:	return TOSTR(EF_RGB16_FLOAT);

	case EF_RGBA16:			return TOSTR(EF_RGBA16);
	case EF_RGBA16_SNORM:	return TOSTR(EF_RGBA16_SNORM);
	case EF_RGBA16_UINT:	return TOSTR(EF_RGBA16_UINT);
	case EF_RGBA16_SINT:	return TOSTR(EF_RGBA16_SINT);
	case EF_RGBA16_FLOAT:	return TOSTR(EF_RGBA16_FLOAT);

	case EF_R32_UINT:		return TOSTR(EF_R32_UINT);
	case EF_R32_SINT:		return TOSTR(EF_R32_SINT);
	case EF_R32_FLOAT:		return TOSTR(EF_R32_FLOAT);

	case EF_RG32_UINT:		return TOSTR(EF_RG32_UINT);
	case EF_RG32_SINT:		return TOSTR(EF_RG32_SINT);
	case EF_RG32_FLOAT:		return TOSTR(EF_RG32_FLOAT);

	case EF_RGB32_UINT:		return TOSTR(EF_RGB32_UINT);
	case EF_RGB32_SINT:		return TOSTR(EF_RGB32_SINT);
	case EF_RGB32_FLOAT:	return TOSTR(EF_RGB32_FLOAT);

	case EF_RGBA32_UINT:	return TOSTR(EF_RGBA32_UINT);
	case EF_RGBA32_SINT:	return TOSTR(EF_RGBA32_SINT);
	case EF_RGBA32_FLOAT:	return TOSTR(EF_RGBA32_FLOAT);

	case EF_R5G6B5:			return TOSTR(EF_R5G6B5);
	case EF_RGBA4:			return TOSTR(EF_RGBA4);
	case EF_RGB5A1:			return TOSTR(EF_RGB5A1);
	case EF_RGB10A2:		return TOSTR(EF_RGB10A2);
	case EF_RGB10A2_UINT:	return TOSTR(EF_RGB10A2_UINT);

	case EF_D16:			return TOSTR(EF_D16);
	case EF_D24:			return TOSTR(EF_D24);
	case EF_D24S8:			return TOSTR(EF_D24S8);
	case EF_D32_FLOAT:		return TOSTR(EF_D32_FLOAT);

	default:
	{
		return TOSTR(EF_UNKNOWN);
	}
	}
}

ElementFormat ElementUtil::GetFormat(const std::string& fmtName)
{
	if (fmtName == "UNKNOWN") return EF_UNKNOWN;
	else if (fmtName == "R8") return EF_R8;
	else if (fmtName == "R8_SNORM") return EF_R8_SNORM;
	else if (fmtName == "R8_UINT") return EF_R8_UINT;
	else if (fmtName == "R8_SINT") return EF_R8_SINT;

	else if (fmtName == "A8") return EF_A8;

	else if (fmtName == "RG8") return EF_RG8;
	else if (fmtName == "RG8_SNORM") return EF_RG8_SNORM;
	else if (fmtName == "RG8_UINT") return EF_RG8_UINT;
	else if (fmtName == "RG8_SINT") return EF_RG8_SINT;

	else if (fmtName == "EF_RGB8") return EF_RGB8;

	else if (fmtName == "RGB8") return EF_RGB8;
	else if (fmtName == "RGB8_SNORM") return EF_RGB8_SNORM;
	else if (fmtName == "RGB8_UINT") return EF_RGB8_UINT;
	else if (fmtName == "RGB8_SINT") return EF_RGB8_SINT;

	else if (fmtName == "BGR8") return EF_BGR8;

	else if (fmtName == "RGBA8") return EF_RGBA8;
	else if (fmtName == "RGBA8_SNORM") return EF_RGBA8_SNORM;
	else if (fmtName == "RGBA8_UINT") return EF_RGBA8_UINT;
	else if (fmtName == "RGBA8_SINT") return EF_RGBA8_SINT;

	else if (fmtName == "BGRA8") return EF_BGRA8;

	else if (fmtName == "R16") return EF_R16;
	else if (fmtName == "R16_SNORM") return EF_R16_SNORM;
	else if (fmtName == "R16_UINT") return EF_R16_UINT;
	else if (fmtName == "R16_SINT") return EF_R16_SINT;
	else if (fmtName == "R16_FLOAT") return EF_R16_FLOAT;

	else if (fmtName == "RG16") return EF_RG16;
	else if (fmtName == "RG16_SNORM") return EF_RG16_SNORM;
	else if (fmtName == "RG16_UINT") return EF_RG16_UINT;
	else if (fmtName == "RG16_SINT") return EF_RG16_SINT;
	else if (fmtName == "RG16_FLOAT") return EF_RG16_FLOAT;

	else if (fmtName == "RGB16") return EF_RGB16;
	else if (fmtName == "RGB16_SNORM") return EF_RGB16_SNORM;
	else if (fmtName == "RGB16_UINT") return EF_RGB16_UINT;
	else if (fmtName == "RGB16_SINT") return EF_RGB16_SINT;
	else if (fmtName == "RGB16_FLOAT") return EF_RGB16_FLOAT;

	else if (fmtName == "RGBA16") return EF_RGBA16;
	else if (fmtName == "RGBA16_SNORM") return EF_RGBA16_SNORM;
	else if (fmtName == "RGBA16_UINT") return EF_RGBA16_UINT;
	else if (fmtName == "RGBA16_SINT") return EF_RGBA16_SINT;
	else if (fmtName == "RGBA16_FLOAT") return EF_RGBA16_FLOAT;

	else if (fmtName == "R32_UINT") return EF_R32_UINT;
	else if (fmtName == "R32_SINT") return EF_R32_SINT;
	else if (fmtName == "R32_FLOAT") return EF_R32_FLOAT;

	else if (fmtName == "RG32_UINT") return EF_RG32_UINT;
	else if (fmtName == "RG32_SINT") return EF_RG32_SINT;
	else if (fmtName == "RG32_FLOAT") return EF_RG32_FLOAT;

	else if (fmtName == "RGB32_UINT") return EF_RGB32_UINT;
	else if (fmtName == "RGB32_SINT") return EF_RGB32_SINT;
	else if (fmtName == "RGB32_FLOAT") return EF_RGB32_FLOAT;

	else if (fmtName == "RGBA32_UINT") return EF_RGBA32_UINT;
	else if (fmtName == "RGBA32_SINT") return EF_RGBA32_SINT;
	else if (fmtName == "RGBA32_FLOAT") return EF_RGBA32_FLOAT;

	else if (fmtName == "R5G6B5") return EF_R5G6B5;
	else if (fmtName == "RGBA4") return EF_RGBA4;
	else if (fmtName == "RGB5A1") return EF_RGB5A1;
	else if (fmtName == "RGB10A2") return EF_RGB10A2;
	else if (fmtName == "RGB10A2_UINT") return EF_RGB10A2_UINT;

	else if (fmtName == "D16") return EF_D16;
	else if (fmtName == "D24") return EF_D24;
	else if (fmtName == "D24S8") return EF_D24S8;
	else if (fmtName == "D32_FLOAT") return EF_D32_FLOAT;

	else return EF_UNKNOWN;
}

uint32 ElementUtil::GetMemorySize(uint32 width, uint32 height, uint32 depth, ElementFormat format)
{
	return (width * height * depth * ELEMENT_BITS(format) / 8);
}

ElementFormat ElementUtil::GetElement4Format(uint64 c0, uint64 c1, uint64 c2, uint64 c3, uint64 s0, uint64 s1, uint64 s2, uint64 s3, uint64 t0, uint64 t1, uint64 t2, uint64 t3, uint64 tag)
{
	uint64 flag = 0;
	flag |= (s0 == 8 || s1 == 8 || s2 == 8 || s3 == 8 ? EFF_NATIVE : 0);
	flag |= (c0 == EC_A || c1 == EC_A || c2 == EC_A || c3 == EC_A ? EFF_ALPHA : 0);
	flag |= (tag != 0 ? EFF_COMPRESSED : 0);
	flag |= (t0 == ET_FLOAT || t1 == ET_FLOAT || t2 == ET_FLOAT || t3 == ET_FLOAT ||
		(t0 == ET_UFLOAT || t1 == ET_UFLOAT || t2 == ET_UFLOAT || t3 == ET_UFLOAT) ? EFF_FLOAT : 0);
	flag |= (c0 == EC_D || c1 == EC_D || c2 == EC_D || c3 == EC_D ? EFF_DEPTH : 0);
	flag |= (c0 == EC_S || c1 == EC_S || c2 == EC_S || c3 == EC_S ? EFF_STENCIL : 0);

	return	(c0 << 0) | (c1 << 3) | (c2 << 6) | (c3 << 9) |
		(s0 << 12) | (s1 << 18) | (s2 << 24) | (s3 << 30) |
		(t0 << 36) | (t1 << 39) | (t2 << 42) | (t3 << 45) |
		(flag << 48) | (tag << 56);
}

uint32 ElementUtil::CalcSurfaceSize(uint32 width, uint32 height, uint32 depth, uint32 mipmaps, ElementFormat format)
{
	uint32 memSize = 0;
	for (uint32 i = 0; i < mipmaps; ++i)
	{
		memSize += GetMemorySize(width, height, depth, format);
		width = std::max((uint32)width >> 1, 1U);
		height = std::max((uint32)height >> 1, 1U);
		depth = std::max((uint32)depth >> 1, 1U);
	}

	return memSize;
}

void ElementUtil::UnpackColor(Color &color, ElementFormat format, const void *pSrc)
{
	UnpackColor(color.r, color.g, color.b, color.a, format, pSrc);
}

void ElementUtil::UnpackColor(float &r, float &g, float &b, float &a, ElementFormat format, const void *src)
{
	if (ELEMENT_IS_NATIVE_ENDIAN(format))
	{
		// Shortcut for integer formats unpacking
		const uint32 value = Math::IntRead(src, ELEMENT_CHANNEL_COUNT(format));

		uint32 bitShift = 0;
		if (ELEMENT_HAS_ALPHA(format))
		{
			uint32 ch3Bits = ELEMENT_CHANNEL_BITS(format, EC_A);
			uint32 ch3Mask = (1 << ch3Bits) - 1;
			a = Math::FixedToFloat(value & ch3Mask, ch3Bits);

			bitShift = ch3Bits;
		}
		else
		{
			a = 1.0f; // No alpha, default a component to full
		}

		uint32 ch2Bits = ELEMENT_CHANNEL_BITS(format, EC_B);
		uint32 ch2Mask = (1 << ch2Bits) - 1;
		b = Math::FixedToFloat((value >> bitShift) & ch2Mask, ch2Bits);
		bitShift += ch2Bits;

		uint32 ch1Bits = ELEMENT_CHANNEL_BITS(format, EC_G);
		uint32 ch1Mask = (1 << ch1Bits) - 1;
		g = Math::FixedToFloat((value >> bitShift) & ch1Mask, ch1Bits);
		bitShift += ch1Bits;

		uint32 ch0Bits = ELEMENT_CHANNEL_BITS(format, EC_R);
		uint32 ch0Mask = (1 << ch0Bits) - 1;
		r = Math::FixedToFloat((value >> bitShift) & ch0Mask, ch0Bits);
	}
	else
	{
		switch (format)
		{
		case EF_R32_FLOAT:
		{
			r = g = b = ((float*)src)[0];
			a = 1.0f;
		} break;
		case EF_RG32_FLOAT:
		{
			r = ((float*)src)[0];
			g = b = ((float*)src)[1];
			a = 1.0f;
		} break;
		case EF_RGB32_FLOAT:
		{
			r = ((float*)src)[0];
			g = ((float*)src)[1];
			b = ((float*)src)[2];
			a = 1.0f;
		} break;
		case EF_RGBA32_FLOAT:
		{
			r = ((float*)src)[0];
			g = ((float*)src)[1];
			b = ((float*)src)[2];
			a = ((float*)src)[3];
		} break;
		case EF_R16_FLOAT:
		{
			r = g = b = Math::HalfToFloat(((uint16*)src)[0]);
			a = 1.0f;
		} break;
		case EF_RG16_FLOAT:
		{
			g = Math::HalfToFloat(((uint16*)src)[0]);
			r = b = Math::HalfToFloat(((uint16*)src)[1]);
			a = 1.0f;
		} break;
		case EF_RGB16_FLOAT:
		{
			r = Math::HalfToFloat(((uint16*)src)[0]);
			g = Math::HalfToFloat(((uint16*)src)[1]);
			b = Math::HalfToFloat(((uint16*)src)[2]);
			a = 1.0f;
		} break;
		case EF_RGBA16_FLOAT:
		{
			r = Math::HalfToFloat(((uint16*)src)[0]);
			g = Math::HalfToFloat(((uint16*)src)[1]);
			b = Math::HalfToFloat(((uint16*)src)[2]);
			a = Math::HalfToFloat(((uint16*)src)[3]);
		} break;
		case EF_RGB32_UINT:
		{
			r = (float)(((uint32*)src)[0]);
			g = (float)(((uint32*)src)[1]);
			b = (float)(((uint32*)src)[2]);
			a = 1.0f;
		} break;
		case EF_RGB32_SINT:
		{
			r = (float)(((int32*)src)[0]);
			g = (float)(((int32*)src)[1]);
			b = (float)(((int32*)src)[2]);
			a = 1.0f;
		} break;
		case EF_RGBA32_UINT:
		{
			r = (float)(((uint32*)src)[0]);
			g = (float)(((uint32*)src)[1]);
			b = (float)(((uint32*)src)[2]);
			a = (float)(((uint32*)src)[3]);
		} break;
		case EF_RGBA32_SINT:
		{
			r = (float)(((int32*)src)[0]);
			g = (float)(((int32*)src)[1]);
			b = (float)(((int32*)src)[2]);
			a = (float)(((int32*)src)[3]);
		} break;
		case EF_RGB16:
		{
			r = Math::FixedToFloat(((uint16*)src)[0], 16);
			g = Math::FixedToFloat(((uint16*)src)[1], 16);
			b = Math::FixedToFloat(((uint16*)src)[2], 16);
			a = 1.0f;
		} break;
		case EF_RGB16_SNORM:
		{
			r = Math::FixedToFloat(((int16*)src)[0], 16);
			g = Math::FixedToFloat(((int16*)src)[1], 16);
			b = Math::FixedToFloat(((int16*)src)[2], 16);
			a = 1.0f;
		} break;
		case EF_RGB16_UINT:
		{
			r = (float)(((uint16*)src)[0]);
			g = (float)(((uint16*)src)[1]);
			b = (float)(((uint16*)src)[2]);
			a = 1.0f;
		} break;
		case EF_RGB16_SINT:
		{
			r = (float)(((int16*)src)[0]);
			g = (float)(((int16*)src)[1]);
			b = (float)(((int16*)src)[2]);
			a = 1.0f;
		} break;
		case EF_RGBA16:
		{
			r = Math::FixedToFloat(((uint16*)src)[0], 16);
			g = Math::FixedToFloat(((uint16*)src)[1], 16);
			b = Math::FixedToFloat(((uint16*)src)[2], 16);
			a = Math::FixedToFloat(((uint16*)src)[3], 16);
		} break;
		case EF_RGBA16_SNORM:
		{
			r = Math::FixedToFloat(((int16*)src)[0], 16);
			g = Math::FixedToFloat(((int16*)src)[1], 16);
			b = Math::FixedToFloat(((int16*)src)[2], 16);
			a = Math::FixedToFloat(((int16*)src)[3], 16);
		} break;
		case EF_RGBA16_UINT:
		{
			r = (float)(((uint16*)src)[0]);
			g = (float)(((uint16*)src)[1]);
			b = (float)(((uint16*)src)[2]);
			a = (float)(((uint16*)src)[3]);
		} break;
		case EF_RGBA16_SINT:
		{
			r = (float)(((int16*)src)[0]);
			g = (float)(((int16*)src)[1]);
			b = (float)(((int16*)src)[2]);
			a = (float)(((int16*)src)[3]);
		} break;
		default:
		{
			// Not yet supported
			printf("unpack from PixelFormat [%s] not implemented\n", ElementUtil::GetFormatName(format).c_str());
		} break;
		}
	}
}

void ElementUtil::PackColor(const Color &color, ElementFormat format, void *dst)
{
	PackColor((float)color.r, (float)color.g, (float)color.b, (float)color.a, format, dst);
}

void ElementUtil::PackColor(float r, float g, float b, float a, ElementFormat format, void *dst)
{
	if (ELEMENT_IS_NATIVE_ENDIAN(format))
	{
		// Do the packing
		uint32 ch3Bits = ELEMENT_CHANNEL_BITS(format, EC_R);
		uint32 ch3Mask = (1 << ch3Bits) - 1;
		uint32 value = ((Math::FloatToFixed(r, ch3Bits) & ch3Mask));
		uint32 bitShift = ch3Bits;

		uint32 ch2Bits = ELEMENT_CHANNEL_BITS(format, EC_G);
		uint32 ch2Mask = (1 << ch2Bits) - 1;
		value |= ((Math::FloatToFixed(g, ch2Bits) & ch2Mask) << bitShift);
		bitShift += ch2Bits;

		uint32 ch1Bits = ELEMENT_CHANNEL_BITS(format, EC_B);
		uint32 ch1Mask = (1 << ch1Bits) - 1;
		value |= ((Math::FloatToFixed(b, ch1Bits) & ch1Mask) << bitShift);
		bitShift += ch1Bits;

		uint32 ch0Bits = ELEMENT_CHANNEL_BITS(format, EC_A);
		uint32 ch0Mask = (1 << ch0Bits) - 1;
		value |= ((Math::FloatToFixed(a, ch0Bits) & ch0Mask) << bitShift);

		// And write to memory
		Math::IntWrite(dst, ELEMENT_SIZE(format), value);
	}
	else
	{
		switch (format)
		{
		case EF_R32_FLOAT:
		{
			((float*)dst)[0] = r;
		} break;
		case EF_RG32_FLOAT:
		{
			((float*)dst)[0] = g;
			((float*)dst)[1] = r;
		} break;
		case EF_RGB32_FLOAT:
		{
			((float*)dst)[0] = r;
			((float*)dst)[1] = g;
			((float*)dst)[2] = b;
		} break;
		case EF_RGBA32_FLOAT:
		{
			((float*)dst)[0] = r;
			((float*)dst)[1] = g;
			((float*)dst)[2] = b;
			((float*)dst)[3] = a;
		} break;
		case EF_R16_FLOAT:
		{
			((uint16*)dst)[0] = Math::FloatToHalf(r);
		} break;
		case EF_RG16_FLOAT:
		{
			((uint16*)dst)[0] = Math::FloatToHalf(g);
			((uint16*)dst)[1] = Math::FloatToHalf(r);
		} break;
		case EF_RGB16_FLOAT:
		{
			((uint16*)dst)[0] = Math::FloatToHalf(r);
			((uint16*)dst)[1] = Math::FloatToHalf(g);
			((uint16*)dst)[2] = Math::FloatToHalf(b);
		} break;
		case EF_RGBA16_FLOAT:
		{
			((uint16*)dst)[0] = Math::FloatToHalf(r);
			((uint16*)dst)[1] = Math::FloatToHalf(g);
			((uint16*)dst)[2] = Math::FloatToHalf(b);
			((uint16*)dst)[3] = Math::FloatToHalf(a);
		} break;
		case EF_RGB32_UINT:
		{
			((uint32*)dst)[0] = (uint32)r;
			((uint32*)dst)[1] = (uint32)g;
			((uint32*)dst)[2] = (uint32)b;
		} break;
		case EF_RGB32_SINT:
		{
			((int32*)dst)[0] = (int32)r;
			((int32*)dst)[1] = (int32)g;
			((int32*)dst)[2] = (int32)b;
		} break;
		case EF_RGBA32_UINT:
		{
			((uint32*)dst)[0] = (uint32)r;
			((uint32*)dst)[1] = (uint32)g;
			((uint32*)dst)[2] = (uint32)b;
			((uint32*)dst)[3] = (uint32)a;
		} break;
		case EF_RGBA32_SINT:
		{
			((int32*)dst)[0] = (int32)r;
			((int32*)dst)[1] = (int32)g;
			((int32*)dst)[2] = (int32)b;
			((int32*)dst)[3] = (int32)a;
		} break;
		case EF_RGB16:
		{
			((uint16*)dst)[0] = (uint16)Math::FloatToFixed(r, 16);
			((uint16*)dst)[1] = (uint16)Math::FloatToFixed(g, 16);
			((uint16*)dst)[2] = (uint16)Math::FloatToFixed(b, 16);
		} break;
		case EF_RGB16_SNORM:
		{
			((uint16*)dst)[0] = (uint16)Math::FloatToFixed(r, 16);
			((uint16*)dst)[1] = (uint16)Math::FloatToFixed(g, 16);
			((uint16*)dst)[2] = (uint16)Math::FloatToFixed(b, 16);
		} break;
		case EF_RGB16_UINT:
		{
			((uint16*)dst)[0] = (uint16)r;
			((uint16*)dst)[1] = (uint16)g;
			((uint16*)dst)[2] = (uint16)b;
		} break;
		case EF_RGB16_SINT:
		{
			((int16*)dst)[0] = (int16)r;
			((int16*)dst)[1] = (int16)g;
			((int16*)dst)[2] = (int16)b;
		} break;
		case EF_RGBA16:
		{
			((uint16*)dst)[0] = (uint16)Math::FloatToFixed(r, 16);
			((uint16*)dst)[1] = (uint16)Math::FloatToFixed(g, 16);
			((uint16*)dst)[2] = (uint16)Math::FloatToFixed(b, 16);
			((uint16*)dst)[3] = (uint16)Math::FloatToFixed(a, 16);
		} break;
		case EF_RGBA16_SNORM:
		{
			((int16*)dst)[0] = (int16)Math::FloatToFixed(r, 16);
			((int16*)dst)[1] = (int16)Math::FloatToFixed(g, 16);
			((int16*)dst)[2] = (int16)Math::FloatToFixed(b, 16);
			((int16*)dst)[3] = (int16)Math::FloatToFixed(a, 16);
		} break;
		case EF_RGBA16_UINT:
		{
			((uint16*)dst)[0] = (uint16)r;
			((uint16*)dst)[1] = (uint16)g;
			((uint16*)dst)[2] = (uint16)b;
			((uint16*)dst)[3] = (uint16)a;
		} break;
		case EF_RGBA16_SINT:
		{
			((int16*)dst)[0] = (int16)r;
			((int16*)dst)[1] = (int16)g;
			((int16*)dst)[2] = (int16)b;
			((int16*)dst)[3] = (int16)a;
		} break;
		default:
			// Not yet supported
			printf("unpack from PixelFormat [%s] not implemented\n", GetFormatName(format).c_str());
			break;
		}
	}
}

BLADE_NAMESPACE_END