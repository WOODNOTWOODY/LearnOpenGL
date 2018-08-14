#include "GLES3RenderStd.h"
#include "GLES3GPUBuffer.h"
#include "GLES3Mapping.h"
#include "GLES3RenderEngine.h"

BLADE_NAMESPACE_BEGIN

GPUBuffer::GPUBuffer()
	: m_type(GBT_VERTEX)
	, m_usage(0)
	, m_stride(0)
	, m_count(0)
	, m_size(0)
	, m_buffer(NULL)
	, m_glTarget(0)
	, m_glBuffer(0)
{
	glGenBuffers(1, &m_glBuffer);
}

GPUBuffer::~GPUBuffer()
{
	BLADE_SAFE_FREE(m_buffer);
	RenderEngine::Instance()->unbindGLBuffer(m_glTarget, m_glBuffer);
	glDeleteBuffers(1, &m_glBuffer);
}

bool GPUBuffer::initialize(const GPUBufferDesc& desc)
{
	m_type = desc.type;
	m_usage = desc.usage;
	m_stride = desc.stride;
	m_size = desc.size;
	m_count = m_size / m_stride;

	if (desc.bBak && m_size)
	{
		m_buffer = (Byte*)BLADE_MALLOC(m_size);
		if (desc.buffer)
		{
			memcpy(m_buffer, desc.buffer, m_size);
		}
	}

	switch (m_type)
	{
	case GBT_VERTEX: m_glTarget = GL_ARRAY_BUFFER; break;
		case GBT_INDEX: m_glTarget = GL_ELEMENT_ARRAY_BUFFER; break;
		default:
		{
			printf("Unsupported GPUBufferType.\n");
			return false;
		}
	}

	RenderEngine::Instance()->bindGLBuffer(m_glTarget, m_glBuffer);
	glBufferData(m_glTarget, (GLsizeiptr)m_size, desc.buffer, GLES3Mapping::mapGPUBufferUsage(m_usage));
	RenderEngine::Instance()->bindGLBuffer(m_glTarget, 0);
	
	return true;
}

BLADE_NAMESPACE_END