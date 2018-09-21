#include "GLES3RenderStd.h"
#include "GLES3RenderView.h"
#include "GLES3Mapping.h"
#include "GLES3FrameBuffer.h"
#include "GLES3RenderEngine.h"

BLADE_NAMESPACE_BEGIN

RenderView::RenderView(RenderViewType type, ElementFormat format, uint32 width, uint32 height, uint32 sampleCount, bool bOffScreen)
	: m_type(type)
	, m_format(format)
	, m_width(width)
	, m_height(height)
	, m_attachmentIdx(-1)
	, m_pTexture(NULL)
	, m_glRBO(0)
	, m_layer(0)
	, m_level(0)
	, m_sampleCount(sampleCount)
{
	if (bOffScreen)
	{
		glGenRenderbuffers(1, &m_glRBO);
		glBindRenderbuffer(GL_RENDERBUFFER, m_glRBO);

		if (m_sampleCount <= 1)
		{
			glRenderbufferStorage(GL_RENDERBUFFER, GLES3Mapping::mapInternalFormat(m_format), m_width, m_height);
		}
		else
		{
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_sampleCount, GLES3Mapping::mapInternalFormat(m_format), m_width, m_height);
		}

		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
}

RenderView::RenderView(RenderViewType type, Texture* pTexture, uint32 layer, uint32 level)
	: m_type(type)
	, m_attachmentIdx(-1)
	, m_pTexture(pTexture)
	, m_layer(layer)
	, m_level(level)
{
	m_format = pTexture->getFormat();
	m_width = pTexture->getWidth();
	m_height = pTexture->getHeight();
	m_sampleCount = pTexture->getSampleCount();
}

RenderView::~RenderView()
{
	if(m_glRBO)
	{
		glDeleteRenderbuffers(1, &m_glRBO);
	}
}

void RenderView::resize(uint32 width, uint32 height)
{
	if (m_width != width || m_height != height)
	{
		m_width = width;
		m_height = height;

		if (!m_pTexture && m_glRBO)
		{
			glBindRenderbuffer(GL_RENDERBUFFER, m_glRBO);

			if (m_sampleCount <= 1)
			{
				glRenderbufferStorage(GL_RENDERBUFFER, GLES3Mapping::mapInternalFormat(m_format), m_width, m_height);
			}
			else
			{
				glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_sampleCount, GLES3Mapping::mapInternalFormat(m_format), m_width, m_height);
			}

			glBindRenderbuffer(GL_RENDERBUFFER, 0);
		}
	}
}

RenderTargetView::RenderTargetView(ElementFormat format, uint32 width, uint32 height, uint32 sampleCount, bool bOffScreen)
	: RenderView(RVT_RENDERTARGET, format, width, height, sampleCount, bOffScreen)
{
}

RenderTargetView::RenderTargetView(Texture* pTexture, uint32 layer, uint32 level)
	: RenderView(RVT_RENDERTARGET, pTexture, layer, level)
{
}

void RenderTargetView::onAttached(FrameBuffer* pFrameBuffer, uint32 idx)
{
	assert(idx < 16);
	m_attachmentIdx = idx;

	GLuint glFBO = pFrameBuffer->getGLFBO();
	if (glFBO)
	{
		GLuint curGLFBO = RenderEngine::Instance()->getCurrentGLFBO();
		RenderEngine::Instance()->bindGLFBO(glFBO);

		if (m_pTexture)
		{
			switch (m_pTexture->getType())
			{
			case TT_1D:
			case TT_2D:
				{
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_attachmentIdx, m_pTexture->getGLTarget(), m_pTexture->getTextureHandle(), m_level);
				} break;
			case TT_3D:
				{
					glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_attachmentIdx, m_pTexture->getTextureHandle(), m_level, m_layer);
				} break;
			default: break;
			}
		}
		else
		{
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_attachmentIdx, GL_RENDERBUFFER, m_glRBO);
		}

		RenderEngine::Instance()->bindGLFBO(curGLFBO);
	}
}

void RenderTargetView::onDetached(FrameBuffer* pFrameBuffer)
{
	GLuint glFBO = pFrameBuffer->getGLFBO();
	if (glFBO)
	{
		GLuint curGLFBO = RenderEngine::Instance()->getCurrentGLFBO();
		RenderEngine::Instance()->bindGLFBO(glFBO);

		if (m_pTexture)
		{
			switch (m_pTexture->getType())
			{
			case TT_1D:
			case TT_2D:
			{
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_attachmentIdx, m_pTexture->getGLTarget(), 0, m_level);
			} break;
			case TT_3D:
			{
				glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_attachmentIdx, 0, m_level, m_layer);
			} break;
			default: break;
			}
		}
		else
		{
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_attachmentIdx, GL_RENDERBUFFER, 0);
		}

		RenderEngine::Instance()->bindGLFBO(curGLFBO);
	}

	m_attachmentIdx = -1;
}

DepthStencilView::DepthStencilView(ElementFormat format, uint32 width, uint32 height, uint32 sampleCount, bool bOffScreen)
	: RenderView(RVT_DEPTHSTENCIL, format, width, height, sampleCount, bOffScreen)
{
}

DepthStencilView::DepthStencilView(Texture* pTexture, uint32 layer, uint32 level)
	: RenderView(RVT_DEPTHSTENCIL, pTexture, layer, level)
{
}

void DepthStencilView::onAttached(FrameBuffer* pFrameBuffer, uint32 idx)
{
	GLuint glFBO = pFrameBuffer->getGLFBO();
	if (glFBO)
	{
		GLuint curGLFBO = RenderEngine::Instance()->getCurrentGLFBO();
		RenderEngine::Instance()->bindGLFBO(glFBO);
	
		bool bHasDepth = ELEMENT_HAS_DEPTH(m_format);
		bool bHasStencil = ELEMENT_HAS_STENCIL(m_format);
		if (m_pTexture)
		{
			switch (m_pTexture->getType())
			{
			case TT_1D:
			case TT_2D:
			{
				if (bHasDepth && bHasStencil)
				{
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, m_pTexture->getGLTarget(), m_pTexture->getTextureHandle(), m_level);
				}
				else if (bHasDepth)
				{
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_pTexture->getGLTarget(), m_pTexture->getTextureHandle(), m_level);
				}
				else if (bHasStencil)
				{
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, m_pTexture->getGLTarget(), m_pTexture->getTextureHandle(), m_level);
				}
			} break;
			case TT_3D:
			{
				if (bHasDepth && bHasStencil)
				{
					glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, m_pTexture->getTextureHandle(), m_level, m_layer);
				}
				else if (bHasDepth)
				{
					glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_pTexture->getTextureHandle(), m_level, m_layer);
				}
				else if (bHasStencil)
				{
					glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, m_pTexture->getTextureHandle(), m_level, m_layer);
				}
			} break;
			default: break;
			}
		}
		else
		{
			if (bHasDepth && bHasStencil)
			{
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_glRBO);
			}
			else if (bHasDepth)
			{
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_glRBO);
			}
			else if (bHasStencil)
			{
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_glRBO);
			}
		}

		RenderEngine::Instance()->bindGLFBO(curGLFBO);
	}
}

void DepthStencilView::onDetached(FrameBuffer* pFrameBuffer)
{
	GLuint glFBO = pFrameBuffer->getGLFBO();
	if (glFBO)
	{
		GLuint curGLFBO = RenderEngine::Instance()->getCurrentGLFBO();
		RenderEngine::Instance()->bindGLFBO(glFBO);

		bool bHasDepth = ELEMENT_HAS_DEPTH(m_format);
		bool bHasStencil = ELEMENT_HAS_STENCIL(m_format);
		if (m_pTexture)
		{
			switch (m_pTexture->getType())
			{
			case TT_1D:
			case TT_2D:
			{
				if (bHasDepth && bHasStencil)
				{
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, m_pTexture->getGLTarget(), 0, m_level);
				}
				else if (bHasDepth)
				{
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_pTexture->getGLTarget(), 0, m_level);
				}
				else if (bHasStencil)
				{
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, m_pTexture->getGLTarget(), 0, m_level);
				}
			} break;
			case TT_3D:
			{
				if (bHasDepth && bHasStencil)
				{
					glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, 0, m_level, m_layer);
				}
				else if (bHasDepth)
				{
					glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, 0, m_level, m_layer);
				}
				else if (bHasStencil)
				{
					glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, 0, m_level, m_layer);
				}
			} break;
			default: break;
			}
		}
		else
		{
			if (bHasDepth && bHasStencil)
			{
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, 0);
			}
			else if (bHasDepth)
			{
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);
			}
			else if (bHasStencil)
			{
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, 0);
			}
		}

		RenderEngine::Instance()->bindGLFBO(curGLFBO);
	}
}

BLADE_NAMESPACE_END