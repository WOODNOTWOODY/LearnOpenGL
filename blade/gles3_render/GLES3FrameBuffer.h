#ifndef __GLES3FRAMEBUFFER_H__
#define __GLES3FRAMEBUFFER_H__

#include "util/Color.h"
#include "GLES3RenderView.h"
#include "GLES3Viewport.h"

BLADE_NAMESPACE_BEGIN

enum ClearMask
{
	CM_COLOR = 1 << 0,
	CM_DEPTH = 1 << 1,
	CM_STENCIL = 1 << 2,
};

class RenderWindow;

class BLADE_GLES3RENDER_API FrameBuffer
{
public:
	FrameBuffer(RenderWindow* pRenderWindow, bool bOffScreen);
	~FrameBuffer();

	static const uint32 MAX_ATTACHMENTS = 8;

public:
	void                         clear(uint32 clearFlags, const Color& color, float depth, uint32 stencil);
	void                         discard();
	void                         onBind();
	void                         blitFromFramebuffer(FrameBuffer* pSrcFBO);
	void                         copyContent(Buffer& buffer, ElementFormat format, uint32 left, uint32 top, uint32 width, uint32 height);

	void                         attachRenderTargetView(uint32 idx, RenderTargetView* pRTV);
	RenderTargetView*            detachRenderTargetView(uint32 idx);
	void                         attachDepthStencilView(DepthStencilView* pDSV);
	DepthStencilView*            detachDepthStencilView();
	bool                         saveRTVToFile(uint32 idx, const std::string& filename, ImageFormat imgFmt = IF_UNKNOWN);
	bool                         saveDSVToFile(const std::string& filename, ImageFormat imgFmt = IF_UNKNOWN);

	void                         setViewport(int left, int top, uint32 width, uint32 height);
	inline void                  setFixedViewport(bool bFixed) { m_bEnableFixedVP = bFixed; }

	inline bool                  isOffScreen() const { return m_bOffScreen; }
	inline bool                  hasColorBuffer(uint32 idx) const { return m_pRTVs[idx]; }
	inline bool                  hasDepthBuffer() const { return (m_pDSV && m_pDSV->hasDepth()); }
	inline bool                  hasStencilBuffer() const { return (m_pDSV && m_pDSV->hasStencil()); }
	inline RenderWindow*         getRenderWindow() const { return m_pRenderWindow; }
	inline RenderTargetView*     getRenderTargetView(uint32 idx) const { assert(idx < MAX_ATTACHMENTS); return m_pRTVs[idx]; }
	inline DepthStencilView*     getDepthStencilView() const { return m_pDSV; }
	inline Viewport*             getViewport() const { return m_pViewport; }
	inline GLuint                getGLFBO() const { return m_glFBO; }

private:
	bool                  m_bOffScreen;
	RenderWindow*         m_pRenderWindow;
	RenderTargetView*     m_pRTVs[MAX_ATTACHMENTS];
	DepthStencilView*     m_pDSV;
	bool                  m_bEnableFixedVP;
	Viewport*             m_pViewport;
	GLuint                m_glFBO;
};

BLADE_NAMESPACE_END

#endif