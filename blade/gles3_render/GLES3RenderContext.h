#ifndef __BLADE_GLES3RENDERCONTEXT_H__
#define __BLADE_GLES3RENDERCONTEXT_H__

#include "GLES3RenderStateObject.h"

BLADE_NAMESPACE_BEGIN

class RenderWindow;

struct ContextOption
{
	bool        bShared;
	bool        bBackground;
	uint32      threadIdx;
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

	inline RenderWindow*      getWindow() const { return m_pWindow; }
	inline bool               isShared() const { return m_bShared; }
	inline bool               isBackground() const { return m_bBackground; }
	inline ulong              getThreadId() const { return m_threadIdx; }

private:
	RenderWindow*      m_pWindow;
	bool               m_bShared;
	bool               m_bBackground;
	ulong              m_threadIdx;
	DepthStencilState* m_pCurrentDSS;
};

BLADE_NAMESPACE_END

#endif
