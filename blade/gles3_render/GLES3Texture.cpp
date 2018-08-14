#include "GLES3RenderStd.h"
#include "GLES3Mapping.h"
#include "GLES3Texture.h"
#include "GLES3RenderEngine.h"
#include "GLES3RenderStateObject.h"

BLADE_NAMESPACE_BEGIN

Texture::Texture(TextureType type, ElementFormat format, uint32 usage, uint32 width, uint32 height, uint32 depth,
	uint32 mipmapNum, SamplerStateDesc& samplerStateDesc, const Buffer& buffer)
	: m_type(type)
	, m_format(format)
	, m_usage(usage)
	, m_size(0)
	, m_width(width)
	, m_height(height)
	, m_depth(depth)
	, m_mipmapNum(mipmapNum)
	, m_buffer(NULL)
	, m_bMapping(false)
	, m_lastLevel(0)
	, m_lastOffset(0)
	, m_mappedData(NULL)
	, m_hTexture(0)
{
	// sampler state
	m_samplerState = BLADE_NEW(SamplerState(samplerStateDesc));

	// if using TU_GPU_MIPMAP, set mipmap num to 1
	if (m_usage & TU_GPU_MIPMAP)
	{
		m_mipmapNum = 1;
	}

	m_size = ElementUtil::CalcSurfaceSize(m_width, m_height, m_depth, m_mipmapNum, m_format);

	/*m_buffer = (Byte*)BLADE_MALLOC(m_size);
	if (buffer.data())
	{
		uint32 memSize = std::min(m_size, buffer.size());
		memcpy(m_buffer, buffer.data(), memSize);
	}
	else
	{
		memset(m_buffer, 0, m_size);
	}*/


	m_glTarget = GLES3Mapping::mapTextureType(m_type);
	m_glFormat = GLES3Mapping::mapFormat(m_format);
	m_glType = GLES3Mapping::mapDataType(m_format);
	m_glInternelFmt = GLES3Mapping::mapInternalFormat(m_format);

	glGenTextures(1, &m_hTexture);
	RenderEngine::Instance()->bindGLTexture(m_type, m_glTarget, m_hTexture);

	if (!(m_usage & TU_GPU_MIPMAP))
	{
		glTexParameteri(m_glTarget, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(m_glTarget, GL_TEXTURE_MAX_LEVEL, m_mipmapNum - 1);
	}

	switch (m_type)
	{
		case TT_1D: resizeTex1D(m_width, buffer.data()); break;
		case TT_2D: resizeTex2D(m_width, m_height, buffer.data()); break;
		case TT_3D: resizeTex3D(m_width, m_height, m_depth, buffer.data()); break;
		default: break;
	};

	if (m_usage & TU_GPU_MIPMAP)
	{
		generateMipmap();
	}

	RenderEngine::Instance()->bindGLTexture(m_type, m_glTarget, 0);
}

Texture::~Texture()
{
	BLADE_SAFE_DELETE(m_samplerState);
	BLADE_SAFE_FREE(m_buffer);

	if (m_hTexture)
	{
		RenderEngine::Instance()->unbindGLTexture(m_type, m_glTarget, m_hTexture);
		glDeleteTextures(1, &m_hTexture);
		m_hTexture = 0;
	}
}

bool Texture::updateData(void* data)
{
	/*if (data)
	{
		memcpy(m_buffer, data, m_size);
	}*/
	return true;
}

void Texture::resizeTex1D(uint32 width, void* data)
{
	m_width = width;

	uint32 w = m_width;
	Byte* dstData = (Byte*)data;
	for (uint32 i = 0; i < m_mipmapNum; ++i)
	{
		GLsizei memSize = (GLsizei)ElementUtil::GetMemorySize(w, 1, 1, m_format);
		glTexImage2D(GL_TEXTURE_2D, i, m_glInternelFmt, w, 1, 0, m_glFormat, m_glType, dstData);
		dstData += memSize;
		w = std::max(1U, w >> 1);
	}

	if (data)
	{
		updateData(data);
	}
}

void Texture::resizeTex2D(uint32 width, uint32 height, void* data)
{
	m_width = width;
	m_height = height;

	uint32 w = m_width;
	uint32 h = m_height;
	Byte* dstData = (Byte*)data;
	for (uint32 i = 0; i < m_mipmapNum; ++i)
	{
		GLsizei memSize = (GLsizei)ElementUtil::GetMemorySize(w, h, 1, m_format);
		glTexImage2D(GL_TEXTURE_2D, i, m_glInternelFmt, w, h, 0, m_glFormat, m_glType, dstData);
		dstData += memSize;
		w = std::max(1U, w >> 1);
		h = std::max(1U, h >> 1);
	}

	if (data)
	{
		updateData(data);
	}
}

void Texture::resizeTex3D(uint32 width, uint32 height, uint32 depth, void* data)
{
	m_width = width;
	m_height = height;
	m_depth = depth;

	uint32 w = m_width;
	uint32 h = m_height;
	uint32 d = m_depth;
	Byte* dstData = (Byte*)data;
	for (uint32 i = 0; i < m_mipmapNum; ++i)
	{
		GLsizei memSize = (GLsizei)ElementUtil::GetMemorySize(w, h, d, m_format);
		glTexImage3D(GL_TEXTURE_3D, i, m_glInternelFmt, w, h, d, 0, m_glFormat, m_glType, dstData);
		dstData += memSize;
		w = std::max(1U, w >> 1);
		h = std::max(1U, h >> 1);
		d = std::max(1U, d >> 1);
	}

	if (data)
	{
		updateData(data);
	}
}

//void Texture::updateSubTex1D(uint32 level, uint32 xOffset, uint32 width, void* data)
//{
//
//}
//
//void Texture::updateSubTex2D(uint32 level, uint32 xOffset, uint32 yOffset, uint32 width, uint32 height, void* data)
//{
//
//}

void Texture::generateMipmap()
{
	RenderEngine::Instance()->bindGLTexture(m_type, m_glTarget, m_hTexture);
	glGenerateMipmap(m_glTarget);
	RenderEngine::Instance()->bindGLTexture(m_type, m_glTarget, 0);
}

//void* Texture::map2D(uint32 level)
//{
//	m_bMapping = true;
//	m_lastLevel = level;
//	m_lastOffset = 0;
//
//	if (level > 0)
//	{
//		uint32 lastLevel = level - 1;
//		uint32 w = std::max(1U, (m_width >> lastLevel));
//		uint32 h = std::max(1U, (m_height >> lastLevel));
//		m_lastOffset = ElementUtil::CalcSurfaceSize(w, h, 1, lastLevel, m_format);
//	}
//	m_mappedData = (m_buff + m_lastOffset);
//	return m_mappedData;
//}
//
//void Texture::unmap2D()
//{
//
//}


BLADE_NAMESPACE_END