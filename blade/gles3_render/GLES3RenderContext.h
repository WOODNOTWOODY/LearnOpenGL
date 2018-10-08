#ifndef __BLADE_GLES3RENDERCONTEXT_H__
#define __BLADE_GLES3RENDERCONTEXT_H__

#include "GLES3RenderStateObject.h"

BLADE_NAMESPACE_BEGIN

class RenderWindow;

struct ContextOption
{
	bool        bBackground;
	uint32      threadIdx;

	ContextOption() : bBackground(false), threadIdx(0) {}
};

class BLADE_GLES3RENDER_API RenderContext
{
public:
	RenderContext(RenderWindow* pWindow);
	~RenderContext();

public:
	bool                      initialize(const ContextOption& op);
	void                      destroy();
	bool                      bind(bool bForce = false);
	bool                      unbind();
	bool                      restore();

	void                      setDepthStencilState(DepthStencilState* pState);
	inline DepthStencilState* getDepthStencilState() const { return m_pCurrentDSS; }

	void                      setRasterizerState(RasterizerState* pState);
	inline RasterizerState*   getRasterizerState() const { return m_pCurrentRS; }

	void                      setBlendState(BlendState* pState);
	inline BlendState*        getBlendState() const { return m_pCurrentBS; }

	inline RenderWindow*      getWindow() const { return m_pWindow; }
	inline bool               isShared() const { return m_bShared; }
	inline bool               isBackground() const { return m_bBackground; }
	inline ulong              getThreadId() const { return m_threadIdx; }

#if (BLADE_PLATFORM == BLADE_PLATFORM_MAC_IOS)
	inline                    getEAGLContext() const { return m_egalContext; }
#else
	inline EGLSurface         getEGLPBufferSurface() const { return m_eglPBuffSurface; }
	inline EGLContext         getEGLContext() const { return m_eglContext; }
#endif

private:
	RenderWindow*      m_pWindow;
	bool               m_bBackground;
	ulong              m_threadIdx;
	RasterizerState*   m_pCurrentRS;
	DepthStencilState* m_pCurrentDSS;
	BlendState*        m_pCurrentBS;

#if (BLADE_PLATFORM == BLADE_PLATFORM_MAC_IOS)
	intptr             m_eaglContext;
	intptr             m_eaglCurView;
	intptr             m_eaglCurContext;
#else
	EGLSurface         m_eglPBuffSurface;
	EGLContext         m_eglContext;
	EGLSurface         m_eglCurSurface;
	EGLContext         m_eglCurContext;
#endif
};

BLADE_NAMESPACE_END

#endif
