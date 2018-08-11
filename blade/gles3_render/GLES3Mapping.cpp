#include "GLES3RenderStd.h"
#include "GLES3Mapping.h"

BLADE_NAMESPACE_BEGIN

GLenum GLES3Mapping::mapDataType(ElementFormat format)
{
	switch (format)
	{
		case EF_R8:					return GL_UNSIGNED_BYTE;
		case EF_R8_SNORM:			return GL_BYTE;
		case EF_R8_UINT:			return GL_UNSIGNED_BYTE;
		case EF_R8_SINT:			return GL_BYTE;

		case EF_A8:					return GL_UNSIGNED_BYTE;

		case EF_RG8:				return GL_UNSIGNED_BYTE;
		case EF_RG8_SNORM:			return GL_BYTE;
		case EF_RG8_UINT:			return GL_UNSIGNED_BYTE;
		case EF_RG8_SINT:			return GL_BYTE;

		case EF_RGB8:				return GL_UNSIGNED_BYTE;
		case EF_RGB8_SNORM:			return GL_BYTE;
		case EF_RGB8_UINT:			return GL_UNSIGNED_BYTE;
		case EF_RGB8_SINT:			return GL_BYTE;

		case EF_BGR8:				return GL_UNSIGNED_BYTE;

		case EF_RGBA8:				return GL_UNSIGNED_BYTE;
		case EF_RGBA8_SNORM:		return GL_BYTE;
		case EF_RGBA8_UINT:			return GL_UNSIGNED_BYTE;
		case EF_RGBA8_SINT:			return GL_BYTE;

		case EF_BGRA8:				return GL_UNSIGNED_BYTE;

		case EF_R16:				return GL_UNSIGNED_SHORT;
		case EF_R16_SNORM:			return GL_SHORT;
		case EF_R16_UINT:			return GL_UNSIGNED_SHORT;
		case EF_R16_SINT:			return GL_SHORT;
		case EF_R16_FLOAT:			return GL_HALF_FLOAT;

		case EF_RG16:				return GL_UNSIGNED_SHORT;
		case EF_RG16_SNORM:			return GL_SHORT;
		case EF_RG16_UINT:			return GL_UNSIGNED_SHORT;
		case EF_RG16_SINT:			return GL_SHORT;
		case EF_RG16_FLOAT:			return GL_HALF_FLOAT;

		case EF_RGB16:				return GL_UNSIGNED_SHORT;
		case EF_RGB16_SNORM:		return GL_SHORT;
		case EF_RGB16_UINT:			return GL_UNSIGNED_SHORT;
		case EF_RGB16_SINT:			return GL_SHORT;
		case EF_RGB16_FLOAT:		return GL_HALF_FLOAT;

		case EF_RGBA16:				return GL_UNSIGNED_SHORT;
		case EF_RGBA16_SNORM:		return GL_SHORT;
		case EF_RGBA16_UINT:		return GL_UNSIGNED_SHORT;
		case EF_RGBA16_SINT:		return GL_SHORT;
		case EF_RGBA16_FLOAT:		return GL_HALF_FLOAT;

		case EF_R32_UINT:			return GL_UNSIGNED_INT;
		case EF_R32_SINT:			return GL_INT;
		case EF_R32_FLOAT:			return GL_FLOAT;

		case EF_RG32_UINT:			return GL_UNSIGNED_INT;
		case EF_RG32_SINT:			return GL_INT;
		case EF_RG32_FLOAT:			return GL_FLOAT;

		case EF_RGB32_UINT:			return GL_UNSIGNED_INT;
		case EF_RGB32_SINT:			return GL_INT;
		case EF_RGB32_FLOAT:		return GL_FLOAT;

		case EF_RGBA32_UINT:		return GL_UNSIGNED_INT;
		case EF_RGBA32_SINT:		return GL_INT;
		case EF_RGBA32_FLOAT:		return GL_FLOAT;

		case EF_R5G6B5:				return GL_UNSIGNED_SHORT_5_6_5;
		case EF_RGBA4:				return GL_UNSIGNED_SHORT_4_4_4_4;
		case EF_RGB5A1:				return GL_UNSIGNED_SHORT_5_5_5_1;
		case EF_RGB10A2:			return GL_UNSIGNED_INT_2_10_10_10_REV;
		case EF_RGB10A2_UINT:		return GL_UNSIGNED_INT_2_10_10_10_REV;

		case EF_D16:				return GL_UNSIGNED_INT;
		case EF_D24:				return GL_UNSIGNED_INT;
		case EF_D24S8:				return GL_UNSIGNED_INT_24_8;
		case EF_D32_FLOAT:			return GL_FLOAT;

		default:
		{
			return GL_BYTE;
		}
	}
}

GLenum GLES3Mapping::mapPrimitiveMode(PrimitiveMode mode)
{
	switch (mode)
	{
		case PM_POINTS:		 return GL_POINTS;
		case PM_LINES:		 return GL_LINES;
		case PM_LINE_STRIPE: return GL_LINE_STRIP;
		case PM_TRIANGLES:	 return GL_TRIANGLES;
		case PM_TRIANGLE_STRIPE:	return GL_TRIANGLE_STRIP;
		default:
		{
			return GL_TRIANGLES;
		}
	}
}

GLenum GLES3Mapping::mapParamType(ParamType type)
{
	return 1;
}

ParamType GLES3Mapping::unmapParamType(GLenum glType)
{
	switch (glType)
	{
		case GL_BOOL:				return PT_1BV;
		case GL_BOOL_VEC2:			return PT_2BV;
		case GL_BOOL_VEC3:			return PT_3BV;
		case GL_BOOL_VEC4:			return PT_4BV;
		case GL_INT:				return PT_1IV;
		case GL_INT_VEC2:			return PT_2IV;
		case GL_INT_VEC3:			return PT_3IV;
		case GL_INT_VEC4:			return PT_4IV;
		case GL_UNSIGNED_INT:		return PT_1UIV;
		case GL_UNSIGNED_INT_VEC2:	return PT_2UIV;
		case GL_UNSIGNED_INT_VEC3:	return PT_3UIV;
		case GL_UNSIGNED_INT_VEC4:	return PT_4UIV;
		case GL_FLOAT:				return PT_1FV;
		case GL_FLOAT_VEC2:			return PT_2FV;
		case GL_FLOAT_VEC3:			return PT_3FV;
		case GL_FLOAT_VEC4:			return PT_4FV;
		case GL_FLOAT_MAT2:			return PT_MAT2X2FV;
		case GL_FLOAT_MAT2x3:		return PT_MAT2X3FV;
		case GL_FLOAT_MAT2x4:		return PT_MAT2X4FV;
		case GL_FLOAT_MAT3x2:		return PT_MAT3X2FV;
		case GL_FLOAT_MAT3:			return PT_MAT3X3FV;
		case GL_FLOAT_MAT3x4:		return PT_MAT3X4FV;
		case GL_FLOAT_MAT4x2:		return PT_MAT4X2FV;
		case GL_FLOAT_MAT4x3:		return PT_MAT4X3FV;
		case GL_FLOAT_MAT4:			return PT_MAT4X4FV;
		default:
		{
			return PT_UNKNOWN;
		}
	}
}

GLenum GLES3Mapping::mapGPUBufferUsage(uint32 usage)
{
	if (usage & GBU_STATIC_DRAW)
	{
		return GL_STATIC_DRAW;
	}
	else if (usage & GBU_DYNAMIC_DRAW)
	{
		return GL_DYNAMIC_DRAW;
	}
	else if (usage & GBU_STREAM_DRAW)
	{
		return GL_STREAM_DRAW;
	}
	else
	{
		return GL_STATIC_DRAW;
	}
}

uint32 GLES3Mapping::getComponentCount(GLenum glType)
{
	switch (glType)
	{
		case GL_BOOL:
		case GL_BOOL_VEC2:
		case GL_BOOL_VEC3:
		case GL_BOOL_VEC4:
		case GL_INT:
		case GL_INT_VEC2:
		case GL_INT_VEC3:
		case GL_INT_VEC4:
		case GL_UNSIGNED_INT:
		case GL_UNSIGNED_INT_VEC2:
		case GL_UNSIGNED_INT_VEC3:
		case GL_UNSIGNED_INT_VEC4:
		case GL_FLOAT:
		case GL_FLOAT_VEC2:
		case GL_FLOAT_VEC3:
		case GL_FLOAT_VEC4:
		case GL_SAMPLER_2D:
		case GL_SAMPLER_3D:
		case GL_SAMPLER_CUBE:		return 1;

		case GL_FLOAT_MAT2:
		case GL_FLOAT_MAT2x3:
		case GL_FLOAT_MAT2x4:		return 2;

		case GL_FLOAT_MAT3x2:
		case GL_FLOAT_MAT3:
		case GL_FLOAT_MAT3x4:		return 3;

		case GL_FLOAT_MAT4x2:
		case GL_FLOAT_MAT4x3:
		case GL_FLOAT_MAT4:			return 4;
		default:
		{
			return 1;
		}
	}
}

BLADE_NAMESPACE_END