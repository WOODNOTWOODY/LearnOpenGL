#include "GLES3RenderStd.h"
#include "GLES3RenderLayout.h"
#include "GLES3RenderEngine.h"
#include "GLES3Mapping.h"

BLADE_NAMESPACE_BEGIN

RenderLayout::RenderLayout()
	: m_program(NULL)
	, m_primitiveMode(PM_TRIANGLES)
	, m_startVertIndex(0)
	, m_vertCount(0)
	, m_indexBuffer(NULL)
	, m_startIndex(0)
	, m_indexCount(0)
	, m_indexStride(0)
	, m_glProgram(0)
	, m_glVAO(0)
	, m_glIndexType(GL_UNSIGNED_SHORT)
{
	memset(m_vertBuffers, 0, sizeof(m_vertBuffers));
	m_glPrimitiveMode = GLES3Mapping::mapPrimitiveMode(m_primitiveMode);
	glGenVertexArrays(1, &m_glVAO);
}

RenderLayout::~RenderLayout()
{
	if (m_glVAO)
	{
		glDeleteVertexArrays(1, &m_glVAO);
	}
}

bool RenderLayout::initialize(const VertexElementList& vertElements, ShaderProgram* program)
{
	m_vertElements = vertElements;
	m_program = program;
	m_glProgram = program->getProgramHandle();
	return true;
}

void RenderLayout::destroy()
{
	m_program = NULL;
	m_vertElements.clear();
	m_primitiveMode = PM_TRIANGLES;
	m_startVertIndex = 0;
	memset(m_vertBuffers, 0, sizeof(m_vertBuffers));
	m_vertCount = 0;
	m_indexBuffer = NULL;
	m_startIndex = 0;
	m_indexCount = 0;
	m_indexStride = 0;
}

void RenderLayout::setPrimitiveMode(PrimitiveMode mode)
{
	m_primitiveMode = mode;
	m_glPrimitiveMode = GLES3Mapping::mapPrimitiveMode(m_primitiveMode);
}

void RenderLayout::bindGPUBuffers()
{
	RenderEngine::Instance()->bindGLBuffer(GL_ARRAY_BUFFER, 0);
	RenderEngine::Instance()->bindGLBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	RenderEngine::Instance()->bindGLVAO(m_glVAO);
	for (size_t i = 0; i < m_vertElements.size(); ++i)
	{
		VertexElement& vertElement = m_vertElements[i];
		Attribute* attr = m_program->getAttribute(vertElement.name);
		if (attr)
		{
			GPUBuffer* vertBuffer = m_vertBuffers[vertElement.streamIdx];
			if (vertBuffer)
			{
				RenderEngine::Instance()->bindGLBuffer(GL_ARRAY_BUFFER, vertBuffer->getGLBuffer());
				if (attr->getGLLocation() >= 0)
				{
					uint32 count = ELEMENT_CHANNEL_COUNT(vertElement.format);
					uint32 size = ELEMENT_SIZE(vertElement.format);
					GLenum type = GLES3Mapping::mapDataType(vertElement.format);
					uint32 componentCount = GLES3Mapping::getComponentCount(attr->getGLType());
					for (uint32 j = 0; j < componentCount; ++j)
					{
						GLuint loc = attr->getGLLocation() + j;
						uint32 offset = vertElement.offset + size * j;
						glEnableVertexAttribArray(loc);
						glVertexAttribPointer(loc, count, type, vertElement.bNormalized, (GLsizei)vertBuffer->getStride(), (GLvoid*)offset);
					}
				}
			}
		}
	}

	if (m_indexBuffer)
	{
		RenderEngine::Instance()->bindGLBuffer(GL_ARRAY_BUFFER, 0);
		m_indexStride = m_indexBuffer->getStride();
		m_indexCount = m_indexBuffer->getCount();

		switch (m_indexStride)
		{
			case 1: m_glIndexType = GL_UNSIGNED_BYTE; break;
			case 2: m_glIndexType = GL_UNSIGNED_SHORT; break;
			case 4: m_glIndexType = GL_UNSIGNED_INT; break;
		}

		RenderEngine::Instance()->bindGLBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer->getGLBuffer());
		RenderEngine::Instance()->bindGLVAO(0);
		RenderEngine::Instance()->bindGLBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	else
	{
		m_indexStride = 0;
		m_indexCount = 0;
		RenderEngine::Instance()->bindGLBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		RenderEngine::Instance()->bindGLVAO(0);
		RenderEngine::Instance()->bindGLBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void RenderLayout::bind()
{
	RenderEngine::Instance()->bindGLVAO(m_glVAO);
}

void RenderLayout::unbind()
{
	RenderEngine::Instance()->bindGLVAO(0);
}

BLADE_NAMESPACE_END