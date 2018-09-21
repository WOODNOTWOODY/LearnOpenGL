#include "GLES3RenderStd.h"
#include "GLES3RenderEngine.h"

BLADE_NAMESPACE_BEGIN

RenderEngine::RenderEngine()
	: m_curRenderWindow(NULL)
	, m_curGLProgram(0)
	, m_curGLVAO(0)
	, m_curGLFBO(0)
	, m_glActiveTexUnit(0)
{
	for (uint32 i = 0; i < MAX_TEXTURE_UNIT_NUM; ++i)
	{
		for (uint32 j = 0; j < TT_COUNT; ++j)
		{
			m_texUnits[i][j] = (GLuint)(-1);
		}
	}
}

RenderEngine::~RenderEngine()
{
}

bool RenderEngine::initialize(const WindowSetting& setting)
{
	m_pDefaultDSS = BLADE_NEW(DepthStencilState);
	m_pCurrentDSS = m_pDefaultDSS;
	m_pDefaultBS = BLADE_NEW(BlendState);
	m_pCurrentBS = m_pDefaultBS;
	m_pDefaultRS = BLADE_NEW(RasterizerState);
	m_pCurrentRS = m_pDefaultRS;

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

void RenderEngine::bindGLFBO(GLuint hFBO)
{
	if (m_curGLFBO != hFBO)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, hFBO);
		m_curGLFBO = hFBO;
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

void RenderEngine::unbindGLBuffer(GLenum glTarget, GLuint hVBO)
{
	BindBufferMap::iterator it = m_bindBufferMap.find(glTarget);
	if (it != m_bindBufferMap.end() && it->second == hVBO)
	{
		glBindBuffer(glTarget, 0);
		m_bindBufferMap.erase(it);
	}
}

void RenderEngine::setViewport(int left, int top, uint32 width, uint32 height)
{
	glViewport(left, top, width, height);
}

void RenderEngine::clearGLColor(const Color& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void RenderEngine::clearGLDepth(float depth)
{
	glClearDepthf(depth);
}
void RenderEngine::clearGLStencil(uint32 stencil)
{
	glClearStencil((GLint)stencil);
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

void RenderEngine::activeGLTextureUnit(GLenum texUnit)
{
	if (m_glActiveTexUnit != texUnit)
	{
		glActiveTexture(GL_TEXTURE0 + texUnit);
		m_glActiveTexUnit = texUnit;
	}
}

void RenderEngine::bindGLTexture(TextureType type, GLenum glTarget, GLuint hTexture)
{
	uint32& handle = m_texUnits[m_glActiveTexUnit][type];
	if (hTexture != handle)
	{
		glBindTexture(glTarget, hTexture);
		handle = hTexture;
	}
}

void RenderEngine::unbindGLTexture(TextureType type, GLenum glTarget, GLuint hTexture)
{
	for (uint32 i = 0; i < MAX_TEXTURE_UNIT_NUM; ++i)
	{
		uint32& handle = m_texUnits[i][type];
		if (handle == hTexture)
		{
			glBindTexture(glTarget, 0);
			handle = 0;
		}
	}
}

void RenderEngine::notifyBlendStateReleased(BlendState* pState)
{
	if (m_pCurrentBS == pState)
	{
		m_pCurrentBS = NULL;
	}

	RenderContext* pContext = m_curRenderWindow->getContext();
	if (pState == pContext->getBlendState())
	{
		pContext->setBlendState(NULL);
	}
}

void RenderEngine::notifyRasterizerStateReleased(RasterizerState* pState)
{
	if (m_pCurrentRS == pState)
	{
		m_pCurrentRS = NULL;
	}

	RenderContext* pContext = m_curRenderWindow->getContext();
	if (pState == pContext->getRasterizerState())
	{
		pContext->setRasterizerState(NULL);
	}
}
void RenderEngine::notifyDepthStencilStateReleased(DepthStencilState* pState)
{
	if (m_pCurrentDSS == pState)
	{
		m_pCurrentDSS = NULL;
	}

	RenderContext* pContext = m_curRenderWindow->getContext();
	if (pState == pContext->getDepthStencilState())
	{
		pContext->setDepthStencilState(NULL);
	}
}

BLADE_NAMESPACE_END
