#ifndef __BLADE_GLES3MAPPING_H__
#define __BLADE_GLES3MAPPING_H__

#include "util/Element.h"
#include "GLES3RenderLayout.h"

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
};

BLADE_NAMESPACE_END

#endif
