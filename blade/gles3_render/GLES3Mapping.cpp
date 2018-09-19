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
		case GL_SAMPLER_2D:         return PT_SAMPLER2D;
		case GL_SAMPLER_3D:         return PT_SAMPLER3D;
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

GLenum GLES3Mapping::mapTextureType(TextureType type)
{
	switch (type)
	{
		case TT_1D:			return GL_TEXTURE_2D;
		case TT_2D:			return GL_TEXTURE_2D;
		case TT_3D:			return GL_TEXTURE_3D;
		default:
		{
			return GL_TEXTURE_2D;
		}
	}
}

GLenum GLES3Mapping::mapFormat(ElementFormat format)
{
	switch (format)
	{
		case EF_R8:
		case EF_R8_SNORM:			return GL_RED;
		case EF_R8_UINT:
		case EF_R8_SINT:			return GL_RED_INTEGER;

		case EF_A8:					return GL_ALPHA;

		case EF_RG8:
		case EF_RG8_SNORM:			return GL_RG;
		case EF_RG8_UINT:
		case EF_RG8_SINT:			return GL_RG_INTEGER;

		case EF_RGB8:
		case EF_RGB8_SNORM:			return GL_RGB;
		case EF_RGB8_UINT:
		case EF_RGB8_SINT:			return GL_RGB_INTEGER;

		case EF_RGBA8:
		case EF_RGBA8_SNORM:		return GL_RGBA;
		case EF_RGBA8_UINT:
		case EF_RGBA8_SINT:			return GL_RGBA_INTEGER;

		case EF_RGBA4:
		case EF_RGB5A1:
		case EF_RGB10A2:			return GL_RGBA;
		case EF_RGB10A2_UINT:		return GL_RGBA_INTEGER;

		case EF_R16:
		case EF_R16_SNORM:
		case EF_R16_FLOAT:			return GL_RED;
		case EF_R16_UINT:
		case EF_R16_SINT:			return GL_RED_INTEGER;

		case EF_RG16:
		case EF_RG16_SNORM:
		case EF_RG16_FLOAT:			return GL_RG;
		case EF_RG16_UINT:
		case EF_RG16_SINT:			return GL_RG_INTEGER;

		case EF_RGB16:
		case EF_RGB16_SNORM:
		case EF_RGB16_FLOAT:		return GL_RGB;
		case EF_RGB16_UINT:
		case EF_RGB16_SINT:			return GL_RGB_INTEGER;

		case EF_R5G6B5:				return GL_RGB;

		case EF_RGBA16:
		case EF_RGBA16_SNORM:
		case EF_RGBA16_FLOAT:		return GL_RGBA;
		case EF_RGBA16_UINT:
		case EF_RGBA16_SINT:		return GL_RGBA_INTEGER;

		case EF_R32_FLOAT:			return GL_RED;
		case EF_R32_UINT:
		case EF_R32_SINT:			return GL_RED_INTEGER;

		case EF_RG32_FLOAT:			return GL_RG;
		case EF_RG32_UINT:
		case EF_RG32_SINT:			return GL_RG_INTEGER;

		case EF_RGB32_FLOAT:		return GL_RGB;
		case EF_RGB32_UINT:
		case EF_RGB32_SINT:			return GL_RGB_INTEGER;

		case EF_RGBA32_FLOAT:		return GL_RGBA;
		case EF_RGBA32_UINT:
		case EF_RGBA32_SINT:		return GL_RGBA_INTEGER;

		case EF_D16:				return GL_DEPTH_COMPONENT;
		case EF_D24:				return GL_DEPTH_COMPONENT;
		case EF_D24S8:				return GL_DEPTH_STENCIL;
		case EF_D32_FLOAT:			return GL_DEPTH_COMPONENT;

		default:
		{
			return GL_BYTE;
		}
	}
}

GLenum GLES3Mapping::mapInternalFormat(ElementFormat format)
{
	switch (format)
	{
		case EF_R8:					return GL_R8;
		case EF_R8_SNORM:			return GL_R8_SNORM;
		case EF_R8_UINT:			return GL_R8UI;
		case EF_R8_SINT:			return GL_R8I;

		case EF_A8:					return GL_ALPHA;

		case EF_RG8:				return GL_RG8;
		case EF_RG8_SNORM:			return GL_RG8_SNORM;
		case EF_RG8_UINT:			return GL_RG8UI;
		case EF_RG8_SINT:			return GL_RG8I;

		case EF_RGB8:				return GL_RGB8;
		case EF_RGB8_SNORM:			return GL_RGB8_SNORM;
		case EF_RGB8_UINT:			return GL_RGB8UI;
		case EF_RGB8_SINT:			return GL_RGB8I;

		case EF_RGBA8:				return GL_RGBA8;
		case EF_RGBA8_SNORM:		return GL_RGBA8_SNORM;
		case EF_RGBA8_UINT:			return GL_RGBA8UI;
		case EF_RGBA8_SINT:			return GL_RGBA8I;

		case EF_BGRA8:				return GL_RGBA8;

		case EF_R16_UINT:			return GL_R16UI;
		case EF_R16_SINT:			return GL_R16I;
		case EF_R16_FLOAT:			return GL_R16F;

		case EF_RG16_UINT:			return GL_RG16UI;
		case EF_RG16_SINT:			return GL_RG16I;
		case EF_RG16_FLOAT:			return GL_RG16F;

		case EF_RGB16_UINT:			return GL_RGB16UI;
		case EF_RGB16_SINT:			return GL_RGB16I;
		case EF_RGB16_FLOAT:		return GL_RGB16F;

		case EF_RGBA16_UINT:		return GL_RGBA16UI;
		case EF_RGBA16_SINT:		return GL_RGBA16I;
		case EF_RGBA16_FLOAT:		return GL_RGBA16F;

		case EF_R32_UINT:			return GL_R32UI;
		case EF_R32_SINT:			return GL_R32I;
		case EF_R32_FLOAT:			return GL_R32F;

		case EF_RG32_UINT:			return GL_RG32UI;
		case EF_RG32_SINT:			return GL_RG32I;
		case EF_RG32_FLOAT:			return GL_RG32F;

		case EF_RGB32_UINT:			return GL_RGB32UI;
		case EF_RGB32_SINT:			return GL_RGB32I;
		case EF_RGB32_FLOAT:		return GL_RGB32F;

		case EF_RGBA32_UINT:		return GL_RGBA32UI;
		case EF_RGBA32_SINT:		return GL_RGBA32I;
		case EF_RGBA32_FLOAT:		return GL_RGBA32F;

		case EF_R5G6B5:				return GL_RGB565;
		case EF_RGBA4:				return GL_RGBA4;
		case EF_RGB5A1:				return GL_RGB5_A1;
		case EF_RGB10A2:			return GL_RGB10_A2;
		case EF_RGB10A2_UINT:		return GL_RGB10_A2UI;

		case EF_D16:				return GL_DEPTH_COMPONENT16;
		case EF_D24:				return GL_DEPTH_COMPONENT24;
		case EF_D24S8:				return GL_DEPTH24_STENCIL8;
		case EF_D32_FLOAT:			return GL_DEPTH_COMPONENT32F;

		default:
		{
			return GL_BYTE;
		}
	}
}

GLint GLES3Mapping::mapAddressMode(AddressMode mode)
{
	switch (mode)
	{
		case AM_WRAP:		return GL_REPEAT;
		case AM_MIRROR:		return GL_MIRRORED_REPEAT;
		case AM_CLAMP:		return GL_CLAMP_TO_EDGE;
		case AM_BORDER:		return GL_CLAMP_TO_EDGE;
		default:
		{
			return GL_REPEAT;
		}
	}
}

void GLES3Mapping::mapTextureFilter(GLenum& glMin, GLenum& glMag, FilterOption min, FilterOption mag, FilterOption mip)
{
	switch (min)
	{
		case FO_ANISOTROPIC:
		case FO_LINEAR:
		{
			switch (mip)
			{
				case FO_ANISOTROPIC:
				case FO_LINEAR:
				{
					// linear min, linear mip
					glMin = GL_LINEAR_MIPMAP_LINEAR;
				} break;
				case FO_POINT:
				{
					// linear min, point mip
					glMin = GL_LINEAR_MIPMAP_NEAREST;
				} break;
				case FO_NONE:
				{
					// linear min, no mip
					glMin = GL_LINEAR;
				} break;
			}
		} break;
		case FO_POINT:
		case FO_NONE:
		{
			switch (mip)
			{
				case FO_ANISOTROPIC:
				case FO_LINEAR:
				{
					// nearest min, linear mip
					glMin = GL_NEAREST_MIPMAP_LINEAR;
				} break;
				case FO_POINT:
				{
					// nearest min, point mip
					glMin = GL_NEAREST_MIPMAP_NEAREST;
				} break;
				case FO_NONE:
				{
					// nearest min, no mip
					glMin = GL_NEAREST;
				} break;
			}
		} break;
	}

	switch (mag)
	{
		case FO_ANISOTROPIC: // GL treats linear and aniso the same
		case FO_LINEAR:
		{
			glMag = GL_LINEAR;
		} break;
		case FO_POINT:
		case FO_NONE:
		{
			glMag = GL_NEAREST;
		} break;
	}
}

GLenum GLES3Mapping::mapComparisonFunc(ComparisonFunc func)
{
	switch (func)
	{
	case CF_ALWAYS:        return GL_ALWAYS;
	case CF_NEVER:         return GL_NEVER;
	case CF_LESS:          return GL_LESS;
	case CF_LESS_EQUAL:    return GL_LEQUAL;
	case CF_EQUAL:         return GL_EQUAL;
	case CF_NOT_EQUAL:     return GL_NOTEQUAL;
	case CF_GREATER_EQUAL: return GL_GEQUAL;
	case CF_GREATER:       return GL_GREATER;
	default:
		{
			assert(false);
			return GL_EQUAL;
		}
	}
}

GLenum GLES3Mapping::mapStencilOperation(StencilOperation op)
{
	switch (op)
	{
	case SOP_KEEP:        return GL_KEEP;
	case SOP_ZERO:        return GL_ZERO;
	case SOP_REPLACE:     return GL_REPLACE;
	case SOP_INCR:        return GL_INCR;
	case SOP_INCR_WRAP:   return GL_INCR_WRAP;
	case SOP_DECR:        return GL_DECR;
	case SOP_DECR_WRAP:   return GL_DECR_WRAP;
	case SOP_INVERT:      return GL_INVERT;
	default:
		{
			assert(false);
			return GL_KEEP;
		}
	}
}

GLenum GLES3Mapping::mapBlendOperation(BlendOperation op)
{
	switch (op)
	{
	case BOP_ADD:     return GL_FUNC_ADD;
	case BOP_SUB:     return GL_FUNC_SUBTRACT;
	case BOP_REV_SUB: return GL_FUNC_REVERSE_SUBTRACT;
	default:
		{
			assert(false);
			return GL_FUNC_ADD;
		}
	}
}

GLenum GLES3Mapping::mapBlendFactor(BlendFactor factor)
{
	switch (factor)
	{
	case BF_ZERO:                return GL_ZERO;
	case BF_ONE:                 return GL_ONE;
	case BF_SRC_ALPHA:           return GL_SRC_ALPHA;
	case BF_DST_ALPHA:           return GL_DST_ALPHA;
	case BF_ONE_MINUS_SRC_ALPHA: return GL_ONE_MINUS_SRC_ALPHA;
	case BF_ONE_MINUS_DST_ALPHA: return GL_ONE_MINUS_DST_ALPHA;
	case BF_SRC_COLOR:           return GL_SRC_COLOR;
	case BF_DST_COLOR:           return GL_DST_COLOR;
	case BF_ONE_MINUS_SRC_COLOR: return GL_ONE_MINUS_SRC_COLOR;
	case BF_ONE_MINUS_DST_COLOR: return GL_ONE_MINUS_DST_COLOR;
	case BF_SRC_ALPHA_SAT:       return GL_SRC_ALPHA_SATURATE;
	default:
		{
			assert(false);
			return GL_FUNC_ADD;
		}
	}
}


BLADE_NAMESPACE_END