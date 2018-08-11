#include "GLES3RenderStd.h"
#include "GLES3RenderEngine.h"

BLADE_NAMESPACE_BEGIN

RenderEngine::RenderEngine()
	: m_curRenderWindow(NULL)
	, m_curGLProgram(0)
	, m_curGLVAO(0)
{
}

RenderEngine::~RenderEngine()
{
}

bool RenderEngine::initialize(const WindowSetting& setting)
{
	m_curRenderWindow = BLADE_NEW(RenderWindow);
	if (!m_curRenderWindow->initialize(setting))
	{
		destroy();
		return false;
	}

	bindGLBuffer(GL_ARRAY_BUFFER, 0);
	bindGLBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	bindGLProgram(0);
	bindGLVAO(0);

	return true;
}

void RenderEngine::destroy()
{
	m_curRenderWindow->destroy();
	BLADE_SAFE_DELETE(m_curRenderWindow);

	m_curGLProgram = 0;
	m_curGLVAO = 0;
}

void RenderEngine::render(RenderLayout* layout)
{
	layout->bind();

	GPUBuffer* indexBuffer = layout->getIndexBuffer();
	if (indexBuffer)
	{
		Byte* offset = 0;
		offset += layout->getStartIndex() * layout->getIndexStride();
		glDrawElements(layout->getGLPrimitiveMode(), layout->getIndexCount(), layout->getGLIndexType(), offset);
	}
	else
	{
		glDrawArrays(layout->getGLPrimitiveMode(), layout->getStartVertexIndex(), layout->getVertexCount());
	}

	layout->unbind();
}

void RenderEngine::bindGLVAO(GLuint hVAO)
{
	if (m_curGLVAO != hVAO)
	{
		glBindVertexArray(hVAO);
		m_curGLVAO = hVAO;
	}
}

void RenderEngine::bindGLProgram(GLuint hProgram)
{
	if (m_curGLProgram != hProgram)
	{
		glUseProgram(hProgram);
		m_curGLProgram = hProgram;
	}
}

void RenderEngine::bindGLBuffer(GLenum glTarget, GLuint hVBO)
{
	BindBufferMap::iterator it = m_bindBufferMap.find(glTarget);
	if (it == m_bindBufferMap.end() || it->second != hVBO)
	{
		glBindBuffer(glTarget, hVBO);
		m_bindBufferMap[glTarget] = hVBO;
	}
}

void RenderEngine::setViewport(int left, int top, uint32 width, uint32 height)
{
	glViewport(left, top, width, height);
}
void RenderEngine::clearGLColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}
void RenderEngine::clear(uint32 flags)
{
	GLbitfield mask = 0;
	if (flags & CM_COLOR)
	{
		mask |= GL_COLOR_BUFFER_BIT;
	}

	if (flags & CM_DEPTH)
	{
		mask |= GL_DEPTH_BUFFER_BIT;
	}

	if (flags & CM_STENCIL)
	{
		mask |= GL_STENCIL_BUFFER_BIT;
	}

	if (mask != 0)
	{
		glClear(mask);
	}
}

BLADE_NAMESPACE_END