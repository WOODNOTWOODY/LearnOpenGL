#ifndef __BLADE_GLES3TEXTURE_H__
#define __BLADE_GLES3TEXTURE_H__

#include "util/Buffer.h"
#include "util/Element.h"
#include "image/Image.h"

BLADE_NAMESPACE_BEGIN

enum TextureType
{
	TT_1D,
	TT_2D,
	TT_3D,
	TT_COUNT
};

enum TextureUsage
{
	TU_STATIC = 0x1,
	TU_DYNAMIC = 0x2,
	TU_IMMUTABLE = 0x4,
	TU_STAGING = 0x8,
	TU_GPU_MIPMAP = 0x10,

	TU_DEFAULT = TU_STATIC | TU_IMMUTABLE,
	TU_DYNAMIC_IMMUTABLE = TU_DYNAMIC | TU_IMMUTABLE,
};

class SamplerStateDesc;
class SamplerState;

class BLADE_GLES3RENDER_API Texture
{
public:
	Texture(TextureType type, ElementFormat format, uint32 usage, uint32 width, uint32 height, uint32 depth,
		uint32 mipmapNum, SamplerStateDesc& samplerStateDesc, const Buffer& buffer);
	~Texture();

public:
	bool                        updateData(void* data);
	void                        resizeTex1D(uint32 width, void* data);
	void                        resizeTex2D(uint32 width, uint32 height, void* data);
	void                        resizeTex3D(uint32 width, uint32 height, uint32 depth, void* data);
	void                        updateSubTex1D(uint32 level, uint32 xOffset, uint32 width, void* data);
	void                        updateSubTex2D(uint32 level, uint32 xOffset, uint32 yOffset, uint32 width, uint32 height, void* data);
	void                        updateSubTex3D(uint32 level, uint32 xOffset, uint32 yOffset, uint32 zOffset, uint32 width, uint32 height, uint32 depth, void* data);
	void                        generateMipmap();
	//void*                       map2D(uint32 level);
	//void                        unmap2D();

	inline TextureType          getType() const { return m_type; }
	inline uint64               getFormat() const { return m_format; }
	inline uint32               getWidth() const { return m_width; }
	inline uint32               getHeight() const { return m_height; }
	inline uint32               getDepth() const { return m_depth; }
	inline uint32               getMipmapNum() const { return m_mipmapNum; }
	inline uint32               getSampleCount() const { return m_sampleCount; }
	inline uint32               getSize() const { return m_size; }
	inline Byte*                getBuffer() const { return m_buffer; }
	inline SamplerState*        getSamplerState() const { return m_samplerState; }
	inline GLuint               getTextureHandle() const { return m_hTexture; }
	inline GLenum		        getGLTarget() const { return m_glTarget; }

private:
	TextureType      m_type;
	uint64           m_format;
	uint32           m_usage;
	uint32           m_size;
	uint32           m_width;
	uint32           m_height;
	uint32           m_depth;
	uint32           m_mipmapNum;
	uint32           m_sampleCount;
	Byte*            m_buffer;
	SamplerState*    m_samplerState;

	bool             m_bMapping;
	uint32           m_lastLevel;
	uint32           m_lastOffset;
	void*            m_mappedData;

	GLuint           m_hTexture;
	GLenum           m_glTarget;
	GLenum           m_glInternelFmt;
	GLenum           m_glFormat;
	GLenum           m_glType;
};

BLADE_NAMESPACE_END

#endif
