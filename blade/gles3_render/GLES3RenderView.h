#ifndef __GLES3RENDERVIEW_H__
#define __GLES3RENDERVIEW_H__

#include "util/Element.h"
#include "GLES3Texture.h"

BLADE_NAMESPACE_BEGIN

enum RenderViewType
{
	RVT_NONE,
	RVT_RENDERTARGET,
	RVT_DEPTHSTENCIL,
};

class FrameBuffer;

class BLADE_GLES3RENDER_API RenderView
{
public:
	RenderView(RenderViewType type, ElementFormat format, uint32 width, uint32 height, uint32 sampleCount, bool bOffScreen);
	RenderView(RenderViewType type, Texture* pTexture, uint32 layer, uint32 level);
	virtual ~RenderView();

public:
	void                        resize(uint32 width, uint32 height);
	virtual void                onAttached(FrameBuffer* pFrameBuffer, uint32 idx = 0) = 0;
	virtual void                onDetached(FrameBuffer* pFrameBuffer) = 0;

	inline RenderViewType       getType() const { return m_type; }
	inline ElementFormat        getFormat() const { return m_format; }
	inline uint32               getWidth() const { return m_width; }
	inline uint32               getHeight() const { return m_height; }
	inline int                  getAttachmentIndex() const { return m_attachmentIdx; }
	inline Texture*             getTexture() const { return m_pTexture; }
	inline GLuint               getGLRBO() const { return m_glRBO; }
	inline uint32               getLayer() const { return m_layer; }
	inline uint32               getLevel() const { return m_level; }
	inline uint32               getSampleCount() const { return m_sampleCount; }

protected:
	RenderViewType    m_type;
	ElementFormat     m_format;
	uint32            m_width;
	uint32            m_height;
	int               m_attachmentIdx;
	uint32            m_level;
	uint32            m_layer;
	uint32            m_sampleCount;
	Texture*          m_pTexture;
	GLuint            m_glRBO;
};

class BLADE_GLES3RENDER_API RenderTargetView : public RenderView
{
public:
	RenderTargetView(ElementFormat format, uint32 width, uint32 height, uint32 sampleCount, bool bOffScreen);
	RenderTargetView(Texture* pTexture, uint32 layer, uint32 level);
	~RenderTargetView() {}

public:
	void                onAttached(FrameBuffer* pFrameBuffer, uint32 idx = 0);
	void                onDetached(FrameBuffer* pFrameBuffer);
};

class BLADE_GLES3RENDER_API DepthStencilView : public RenderView
{
public:
	DepthStencilView(ElementFormat format, uint32 width, uint32 height, uint32 sampleCount, bool bOffScreen);
	DepthStencilView(Texture* pTexture, uint32 layer, uint32 level);
	~DepthStencilView() {}

public:
	inline bool         hasDepth() const { return ELEMENT_HAS_DEPTH(m_format); }
	inline bool         hasStencil() const { return ELEMENT_HAS_STENCIL(m_format); }

	void                onAttached(FrameBuffer* pFrameBuffer, uint32 idx = 0);
	void                onDetached(FrameBuffer* pFrameBuffer);
};

BLADE_NAMESPACE_END

#endif
