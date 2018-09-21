#include "GLES3RenderStd.h"
#include "GLES3FrameBuffer.h"
#include "GLES3RenderWindow.h"
#include "GLES3RenderEngine.h"
#include "GLES3Mapping.h"
#include "image/Image.h"

BLADE_NAMESPACE_BEGIN

FrameBuffer::FrameBuffer(RenderWindow* pRenderWindow, bool bOffScreen)
	: m_pRenderWindow(pRenderWindow)
	, m_bOffScreen(bOffScreen)
	, m_pDSV(NULL)
	, m_bEnableFixedVP(false)
	, m_glFBO(0)
{
	for (uint32 i = 0; i < MAX_ATTACHMENTS; ++i)
	{
		m_pRTVs[i] = NULL;
	}

	m_pViewport = BLADE_NEW(Viewport(this));
	m_pViewport->setWidth(pRenderWindow->getWidth());
	m_pViewport->setHeight(pRenderWindow->getHeight());

	if (m_bOffScreen)
	{
		glGenFramebuffers(1, &m_glFBO);
	}
}

FrameBuffer::~FrameBuffer()
{
	BLADE_SAFE_DELETE(m_pViewport);

	if (m_glFBO)
	{
		glDeleteFramebuffers(1, &m_glFBO);
	}
}

void FrameBuffer::clear(uint32 clearFlags, const Color& color, float depth, uint32 stencil)
{
	RenderContext* pRenderContext = RenderEngine::Instance()->getCurrentRenderWindow()->getContext();
	BlendState* pCurBS = pRenderContext->getBlendState();
	DepthStencilState* pCurDSS = pRenderContext->getDepthStencilState();

	bool bRestoreColorMask = false;
	bool bRestoreDepthMask = false;
	bool bRestoreFrontStencilMask = false;
	bool bRestoreBackStencilMask = false;

	GLbitfield mask = 0;
	if ((clearFlags & CM_COLOR) && m_pRTVs[0])
	{
		if (!pCurBS)
		{
			glColorMask(true, true, true, true);
		}
		else if (!pCurBS->getDesc().targets[0].colorWriteMask)
		{
			bRestoreColorMask = true;
			glColorMask(true, true, true, true);
		}

		RenderEngine::Instance()->clearGLColor(color);
		mask |= GL_COLOR_BUFFER_BIT;
	}

	if (m_pDSV)
	{
		if ((clearFlags & CM_DEPTH) && m_pDSV->hasDepth())
		{
			if (!pCurDSS)
			{
				glDepthMask(GL_TRUE);
			}
			else if (!pCurDSS->getDesc().bWriteDepth)
			{
				glDepthMask(GL_TRUE);
			}

			RenderEngine::Instance()->clearGLDepth(depth);
			mask |= GL_DEPTH_BUFFER_BIT;
		}

		if ((clearFlags & CM_STENCIL) && m_pDSV->hasStencil())
		{
			if (!pCurDSS)
			{
				glStencilMaskSeparate(GL_FRONT, 0xff);
				glStencilMaskSeparate(GL_BACK, 0xff);
			}
			else if (!pCurDSS->getDesc().frontStencilWriteMask)
			{
				bRestoreFrontStencilMask = true;
				glStencilMaskSeparate(GL_FRONT, 0xff);
			}
			else if (!pCurDSS->getDesc().backStencilWriteMask)
			{
				bRestoreBackStencilMask = true;
				glStencilMaskSeparate(GL_BACK, 0xff);
			}

			RenderEngine::Instance()->clearGLStencil(stencil);
			mask |= GL_STENCIL_BUFFER_BIT;
		}
	}

	if (mask != 0)
	{
		glClear(mask);

		if (bRestoreColorMask)
		{
			pCurBS->colorMaskGL();
		}

		if (bRestoreFrontStencilMask)
		{
			glStencilMaskSeparate(GL_FRONT, pCurDSS->getDesc().frontStencilWriteMask);
		}

		if (bRestoreBackStencilMask)
		{
			glStencilMaskSeparate(GL_BACK, pCurDSS->getDesc().backStencilWriteMask);
		}
	}
}

void FrameBuffer::discard()
{
	uint32 attachmentsNum = 0;
	GLenum attachments[MAX_ATTACHMENTS];

	if (!m_bOffScreen)
	{
		attachments[attachmentsNum++] = GL_COLOR;

		if (m_pDSV)
		{
			if (m_pDSV->hasDepth())
			{
				attachments[attachmentsNum++] = GL_DEPTH;
			}

			if (m_pDSV->hasStencil())
			{
				attachments[attachmentsNum++] = GL_STENCIL;
			}
		}
	}
	else
	{
		for (uint32 i = 0; i < MAX_ATTACHMENTS; ++i)
		{
			if (m_pRTVs[i])
			{
				attachments[attachmentsNum++] = GL_COLOR_ATTACHMENT0 + i;
			}
			else
			{
				break;
			}
		}

		if (m_pDSV)
		{
			if (m_pDSV->hasDepth())
			{
				attachments[attachmentsNum++] = GL_DEPTH_ATTACHMENT;
			}

			if (m_pDSV->hasStencil())
			{
				attachments[attachmentsNum++] = GL_STENCIL_ATTACHMENT;
			}
		}
	}

	GLuint curGLFBO = RenderEngine::Instance()->getCurrentGLFBO();
	RenderEngine::Instance()->bindGLFBO(m_glFBO);
	glInvalidateFramebuffer(GL_FRAMEBUFFER, attachmentsNum, attachments);
	RenderEngine::Instance()->bindGLFBO(curGLFBO);
}

void FrameBuffer::onBind()
{
	m_pRenderWindow->setCurrentFrameBuffer(this);
}

void FrameBuffer::blitFromFramebuffer(FrameBuffer* pSrcFBO)
{
	uint32 width = 0;
	uint32 height = 0;
	GLbitfield mask = 0;

	RenderTargetView* pRTV = pSrcFBO->getRenderTargetView(0);
	if (pRTV)
	{
		width = pRTV->getWidth();
		height = pRTV->getHeight();
		mask |= GL_COLOR_BUFFER_BIT;
	}
	else
	{
		DepthStencilView* pDSV = pSrcFBO->getDepthStencilView();
		if (pDSV)
		{
			if (pDSV->hasDepth())
			{
				width = pDSV->getWidth();
				height = pDSV->getHeight();
				mask |= GL_DEPTH_BUFFER_BIT;
			}

			if (pDSV->hasStencil())
			{
				width = pDSV->getWidth();
				height = pDSV->getHeight();
				mask |= GL_STENCIL_BUFFER_BIT;
			}
		}
	}

	if (width > 0 && height > 0)
	{
		GLuint curGLFBO = RenderEngine::Instance()->getCurrentGLFBO();
		RenderEngine::Instance()->bindGLFBO(m_glFBO);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, pSrcFBO->getGLFBO());
		glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, mask, GL_NEAREST);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		RenderEngine::Instance()->bindGLFBO(curGLFBO);
	}
}

void FrameBuffer::copyContent(Buffer& buffer, ElementFormat format, uint32 left, uint32 top, uint32 width, uint32 height)
{
	GLuint curGLFBO = RenderEngine::Instance()->getCurrentGLFBO();
	RenderEngine::Instance()->bindGLFBO(m_glFBO);
	RenderEngine::Instance()->setViewport(left, top, width, height);

	uint32 size;
	GLenum glType;
	GLenum glFmt;

	if (format == EF_D24)
	{
		//There is no 24 bit variable, so we'll have to settle for 32 bit
		size = width * height * sizeof(uint32);
		glType = GL_UNSIGNED_INT;
		glFmt = GL_DEPTH_COMPONENT;
	}
	else if (format == EF_D24S8)
	{
		//There is no 24 bit variable, so we'll have to settle for 32 bit
		size = width * height * sizeof(uint32);
		glType = GL_UNSIGNED_INT_24_8;
		glFmt = GL_DEPTH_STENCIL;
	}
	else if (format == EF_D32_FLOAT)
	{
		// The depth format is a normalized integer format, use GL_UNSIGNED_INT to prevent the driver to use the CPU 
		// to convert the normalized integer data into floating-point values. This is slow.
		size = width * height * sizeof(uint32);
		glType = GL_UNSIGNED_INT;
		glFmt = GL_DEPTH_COMPONENT;
	}
	else
	{
		size = width * height * ELEMENT_SIZE(format);
		glFmt = GLES3Mapping::mapFormat(format);
		glType = GLES3Mapping::mapDataType(format);
	}

	buffer.allocate(size);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(left, top, width, height, glFmt, glType, buffer.data());
	RenderEngine::Instance()->bindGLFBO(curGLFBO);
}

void FrameBuffer::attachRenderTargetView(uint32 idx, RenderTargetView* pRTV)
{
	RenderTargetView* pOldRTV = m_pRTVs[idx];
	if (pRTV && pOldRTV != pRTV)
	{
		m_pRTVs[idx] = pRTV;
		pRTV->onAttached(this, idx);
	}
}

RenderTargetView* FrameBuffer::detachRenderTargetView(uint32 idx)
{
	assert(idx < MAX_ATTACHMENTS);

	RenderTargetView* pRTV = m_pRTVs[idx];
	if (pRTV)
	{
		pRTV->onDetached(this);
		m_pRTVs[idx] = NULL;
		return pRTV;
	}

	return NULL;
}

void FrameBuffer::attachDepthStencilView(DepthStencilView* pDSV)
{
	if (pDSV && m_pDSV != pDSV)
	{
		m_pDSV = pDSV;
		m_pDSV->onAttached(this);
	}
}

DepthStencilView* FrameBuffer::detachDepthStencilView()
{
	if (m_pDSV)
	{
		DepthStencilView* pDSV = m_pDSV;
		pDSV->onDetached(this);
		m_pDSV = NULL;
		return pDSV;
	}

	return NULL;
}

bool FrameBuffer::saveRTVToFile(uint32 idx, const std::string& filename, ImageFormat imgFmt = IF_UNKNOWN)
{
	if (idx > MAX_ATTACHMENTS)
	{
		return false;
	}

	RenderTargetView* pRTV = m_pRTVs[idx];
	if (!pRTV)
	{
		printf("RTV [%d] is null.\n", idx);
		return false;
	}

	Buffer buffer;
	copyContent(buffer, EF_RGB8, 0, 0, pRTV->getWidth(), pRTV->getHeight());
	Image img(buffer.data(), pRTV->getWidth(), pRTV->getHeight(), 1, EF_RGB8, 1, 1);
	return img.saveToFile(filename, imgFmt);
}

bool FrameBuffer::saveDSVToFile(const std::string& filename, ImageFormat imgFmt = IF_UNKNOWN)
{
	Buffer buffer;
	copyContent(buffer, m_pDSV->getFormat(), 0, 0, m_pDSV->getWidth(), m_pDSV->getHeight());
	
	Buffer dstBuffer;
	uint32 dstSize = m_pDSV->getWidth() * m_pDSV->getHeight() * ELEMENT_SIZE(EF_RGB8);
	dstBuffer.allocate(dstSize);

	PixelBox dst(m_pDSV->getWidth(), m_pDSV->getHeight(), 1, EF_RGB8, dstBuffer.data());
	PixelBox src(m_pDSV->getWidth(), m_pDSV->getHeight(), 1, m_pDSV->getFormat(), buffer.data());
	ElementUtil::BulkPixelConversion(src, dst);

	Image img(dstBuffer.data(), m_pDSV->getWidth(), m_pDSV->getHeight(), 1, EF_RGB8, 1, 1);
	return img.saveToFile(filename, imgFmt);

}

void FrameBuffer::setViewport(int left, int top, uint32 width, uint32 height)
{
	m_pViewport->resize(left, top, width, height);
}

BLADE_NAMESPACE_END