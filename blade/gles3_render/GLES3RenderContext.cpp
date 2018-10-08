#include "GLES3RenderStd.h"
#include "GLES3Extension.h"
#include "GLES3RenderContext.h"
#include "GLES3RenderWindow.h"
#include "GLES3RenderEngine.h"

BLADE_NAMESPACE_BEGIN

RenderContext::RenderContext(RenderWindow* pWindow)
	: m_pWindow(pWindow)
	, m_threadIdx(0)
	, m_pCurrentRS(NULL)
	, m_pCurrentDSS(NULL)
	, m_pCurrentBS(NULL)
#if (BLADE_PLATFORM == BLADE_PLATFORM_MAC_IOS)
	, m_eaglContext(NULL)
	, m_eaglCurView(NULL)
	, m_eaglCurContext(NULL)
#else
	, m_eglPBuffSurface(EGL_NO_SURFACE)
	, m_bEGLContextCreated(false)
	, m_eglContext(EGL_NO_CONTEXT)
	, m_eglCurSurface(EGL_NO_SURFACE)
	, m_eglCurContext(EGL_NO_CONTEXT)
#endif
{

}

RenderContext::~RenderContext()
{

}

#if (BLADE_PLATFORM != BLADE_PLATFORM_MAC_IOS)
bool RenderContext::initialize(const ContextOption& op)
{
	EGLDisplay eglDisplay = m_pWindow->getEGLDisplay();
	EGLConfig eglConfig = m_pWindow->getEGLConfig();

	EGLint pbuffAttris[] = 
	{
		EGL_WIDTH, 2,
		EGL_HEIGHT, 2,
		EGL_LARGEST_PBUFFER, EGL_TRUE,
		EGL_TEXTURE_FORMAT, EGL_NO_TEXTURE,
		EGL_TEXTURE_TARGET, EGL_NO_TEXTURE,
		EGL_NONE
	};

	if (op.bBackground)
	{
		m_eglPBuffSurface = eglCreatePbufferSurface(eglDisplay, eglConfig, pbuffAttris);
		if (m_eglPBuffSurface == EGL_NO_SURFACE)
		{
			printf("eglCreatePbufferSurface failed\n");
			return false;
		}
	}

	EGLint contextAttribs[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 3,
		EGL_NONE
	};

	if (op.bBackground)
	{
		EGLContext eglSharedContext = m_pWindow->getContext()->getEGLContext();
		m_eglContext = eglCreateContext(eglDisplay, eglConfig, eglSharedContext, contextAttribs);
	}
	else
	{
		m_eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, contextAttribs);
	}

	if (!m_eglContext)
	{
		if (m_eglPBuffSurface != EGL_NO_SURFACE)
		{
			eglDestroySurface(eglDisplay, m_eglPBuffSurface);
			m_eglPBuffSurface = EGL_NO_SURFACE;
		}
		return false;
	}

	m_bBackground = op.bBackground;

	return true;
}

void RenderContext::destroy()
{
	if (m_eglContext != EGL_NO_CONTEXT)
	{
		eglDestroyContext(m_pWindow->getEGLDisplay(), m_eglContext);
		m_eglContext = EGL_NO_CONTEXT;
	}

	if (m_eglPBuffSurface != EGL_NO_SURFACE)
	{
		eglDestroySurface(m_pWindow->getEGLDisplay(), m_eglPBuffSurface);
		m_eglPBuffSurface = EGL_NO_SURFACE;
	}

	eglMakeCurrent(m_pWindow->getEGLDisplay(), EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
}

bool RenderContext::bind(bool bForce)
{
	bool bUpdate;
	m_eglCurSurface = eglGetCurrentSurface(EGL_DRAW);
	m_eglCurContext = eglGetCurrentContext();
	EGLSurface eglSurface = m_bBackground ? m_eglPBuffSurface : m_pWindow->getEGLSurface();


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

void RenderContext::setRasterizerState(RasterizerState* pState)
{
	if (m_pCurrentRS != pState && pState)
	{
		pState->bind();
	}
	m_pCurrentRS = pState;
}

void RenderContext::setDepthStencilState(DepthStencilState* pState)
{
	if (m_pCurrentDSS != pState && pState)
	{
		pState->bind();
	}
	m_pCurrentDSS = pState;
}

void RenderContext::setBlendState(BlendState* pState)
{
	if (m_pCurrentBS != pState && pState)
	{
		pState->bind();
	}
	m_pCurrentBS = pState;
}
#endif

BLADE_NAMESPACE_END