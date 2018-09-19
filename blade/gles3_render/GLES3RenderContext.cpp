#include "GLES3RenderStd.h"
#include "GLES3RenderContext.h"
#include "GLES3RenderWindow.h"

BLADE_NAMESPACE_BEGIN

RenderContext::RenderContext(RenderWindow* pWindow)
	: m_pWindow(pWindow)
	, m_threadIdx(0)
	, m_pCurrentDSS(NULL)
{

}

RenderContext::~RenderContext()
{

}

bool RenderContext::initialize(const ContextOption& op)
{
	m_bShared = op.bShared;
	m_bBackground = op.bBackground;
	return true;
}

void RenderContext::destroy()
{
	glfwMakeContextCurrent(NULL);
}

bool RenderContext::bind(bool bForce)
{
	glfwMakeContextCurrent(m_pWindow->getGLFWWindow());
	return true;
}

bool RenderContext::unbind()
{
	glfwMakeContextCurrent(NULL);
	return true;
}

bool RenderContext::restore()
{
	glfwMakeContextCurrent(m_pWindow->getGLFWWindow());
	return true;
}

void RenderContext::setDepthStencilState(DepthStencilState* pState)
{
	if (m_pCurrentDSS != pState && pState)
	{
		pState->bind();
	}
	m_pCurrentDSS = pState;
}

BLADE_NAMESPACE_END