#ifndef __BLADE_GLES3MAPPING_H__
#define __BLADE_GLES3MAPPING_H__

#include "util/Element.h"
#include "GLES3RenderLayout.h"
#include "GLES3Texture.h"
#include "GLES3RenderStateObject.h"

BLADE_NAMESPACE_BEGIN

class BLADE_GLES3RENDER_API GLES3Mapping
{
public:
	static GLenum			mapDataType(ElementFormat format);
	static GLenum           mapPrimitiveMode(PrimitiveMode mode);
	static GLenum           mapParamType(ParamType type);
	static ParamType        unmapParamType(GLenum glType);
	static GLenum			mapGPUBufferUsage(uint32 usage);
	static uint32           getComponentCount(GLenum glType);
	static GLenum           mapTextureType(TextureType type);
	static GLenum           mapFormat(ElementFormat format);
	static GLenum           mapInternalFormat(ElementFormat format);
	static GLint            mapAddressMode(AddressMode mode);
	static void             mapTextureFilter(GLenum& glMin, GLenum& glMag, FilterOption min, FilterOption mag, FilterOption mip);
	static GLenum           mapComparisonFunc(ComparisonFunc func);
	static GLenum           mapStencilOperation(StencilOperation op);
	static GLenum           mapBlendOperation(BlendOperation op);
	static GLenum           mapBlendFactor(BlendFactor factor);
};

BLADE_NAMESPACE_END

#endif
