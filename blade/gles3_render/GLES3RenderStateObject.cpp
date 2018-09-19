#include "GLES3RenderStd.h"
#include "GLES3RenderStateObject.h"
#include "GLES3Mapping.h"
#include "GLES3RenderContext.h"
#include "GLES3RenderEngine.h"

BLADE_NAMESPACE_BEGIN

SamplerState::SamplerState()
{
	create();
}

SamplerState::SamplerState(const SamplerStateDesc& desc)
	: m_desc(desc)
{
	create();
}

void SamplerState::create()
{
	m_glAddrModeU = GLES3Mapping::mapAddressMode(m_desc.addrModeU);
	m_glAddrModeV = GLES3Mapping::mapAddressMode(m_desc.addrModeV);
	m_glAddrModeW = GLES3Mapping::mapAddressMode(m_desc.addrModeW);
	GLES3Mapping::mapTextureFilter(m_glMinFilter, m_glMagFilter, m_desc.minFilter, m_desc.magFilter, m_desc.mipFilter);
}

DepthStencilState::DepthStencilState()
{
	create();
}

DepthStencilState::DepthStencilState(const DepthStencilStateDesc& desc)
	: m_desc(desc)
{
	create();
}

void DepthStencilState::create()
{
	m_glDepthMask = m_desc.bWriteDepth ? GL_TRUE : GL_FALSE;
	m_glDepthFunc = GLES3Mapping::mapComparisonFunc(m_desc.depthFunc);
	m_glFrontStencilFunc = GLES3Mapping::mapComparisonFunc(m_desc.frontStencilFunc);
	m_glFrontStencilFailOp = GLES3Mapping::mapStencilOperation(m_desc.frontStencilFailOp);
	m_glFrontStencilDepthFailOp = GLES3Mapping::mapStencilOperation(m_desc.frontStencilDepthFailOp);
	m_glFrontStencilPassOp = GLES3Mapping::mapStencilOperation(m_desc.frontStencilPassOp);
	m_glBackStencilFunc = GLES3Mapping::mapComparisonFunc(m_desc.backStencilFunc);
	m_glBackStencilFailOp = GLES3Mapping::mapStencilOperation(m_desc.backStencilFailOp);
	m_glBackStencilDepthFailOp = GLES3Mapping::mapStencilOperation(m_desc.backStencilDepthFailOp);
	m_glBackStencilPassOp = GLES3Mapping::mapStencilOperation(m_desc.backStencilPassOp);
}

void DepthStencilState::bind(bool bForce)
{
	RenderContext* pContext = RenderEngine::Instance()->getCurrentRenderWindow()->getContext();
	DepthStencilState* pCurState = pContext->getDepthStencilState();
	if (pCurState && !bForce)
	{
		const DepthStencilStateDesc& curDesc = pCurState->getDesc();
		if (m_desc.bDepth != curDesc.bDepth)
		{
			if (m_desc.bDepth)
			{
				glEnable(GL_DEPTH_TEST);
			}
			else
			{
				glDisable(GL_DEPTH_TEST);
			}
		}

		if (m_desc.bWriteDepth != curDesc.bWriteDepth)
		{
			glDepthMask(m_glDepthMask);
		}

		if (m_desc.depthFunc != curDesc.depthFunc)
		{
			glDepthFunc(m_glDepthFunc);
		}

		if ((m_desc.frontStencilFunc != curDesc.frontStencilFunc) ||
			(m_desc.frontStencilRef != curDesc.frontStencilRef) ||
			(m_desc.frontStencilReadMask != curDesc.frontStencilReadMask))
		{
			glStencilFuncSeparate(GL_FRONT, m_glFrontStencilFunc, m_desc.frontStencilRef, m_desc.frontStencilReadMask);
		}

		if ((m_desc.frontStencilFailOp != curDesc.frontStencilFailOp) ||
			(m_desc.frontStencilDepthFailOp != curDesc.frontStencilDepthFailOp) ||
			(m_desc.frontStencilPassOp != curDesc.frontStencilPassOp))
		{
			glStencilOpSeparate(GL_FRONT, m_glFrontStencilFailOp, m_glFrontStencilDepthFailOp, m_glFrontStencilPassOp);
		}

		if (m_desc.frontStencilWriteMask != curDesc.frontStencilWriteMask)
		{
			glStencilMaskSeparate(GL_FRONT, m_desc.frontStencilWriteMask);
		}

		if ((m_desc.backStencilFunc != curDesc.backStencilFunc) ||
			(m_desc.backStencilRef != curDesc.backStencilRef) ||
			(m_desc.backStencilReadMask != curDesc.backStencilReadMask))
		{
			glStencilFuncSeparate(GL_BACK, m_glBackStencilFunc, m_desc.backStencilRef, m_desc.backStencilReadMask);
		}

		if ((m_desc.backStencilFailOp != curDesc.backStencilFailOp) ||
			(m_desc.backStencilDepthFailOp != curDesc.backStencilDepthFailOp) ||
			(m_desc.backStencilPassOp != curDesc.backStencilPassOp))
		{
			glStencilOpSeparate(GL_BACK, m_glBackStencilFailOp, m_glBackStencilDepthFailOp, m_glBackStencilPassOp);
		}

		if (m_desc.backStencilWriteMask != curDesc.backStencilWriteMask)
		{
			glStencilMaskSeparate(GL_BACK, m_desc.backStencilWriteMask);
		}

		if ((m_desc.bFrontStencil != curDesc.bFrontStencil) ||
			(m_desc.bBackStencil != curDesc.bBackStencil))
		{
			if (m_desc.bFrontStencil || m_desc.bBackStencil)
			{
				glEnable(GL_STENCIL_TEST);
			}
			else
			{
				glDisable(GL_STENCIL_TEST);
			}
		}
	}
	else
	{
		if (m_desc.bDepth)
		{
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}

		glDepthMask(m_glDepthMask);
		glDepthFunc(m_glDepthFunc);

		glStencilFuncSeparate(GL_FRONT, m_glFrontStencilFunc, m_desc.frontStencilRef, m_desc.frontStencilReadMask);
		glStencilOpSeparate(GL_FRONT, m_glFrontStencilFailOp, m_glFrontStencilDepthFailOp, m_glFrontStencilPassOp);
		glStencilMaskSeparate(GL_FRONT, m_desc.frontStencilWriteMask);
		glStencilFuncSeparate(GL_BACK, m_glBackStencilFunc, m_desc.backStencilRef, m_desc.backStencilReadMask);
		glStencilOpSeparate(GL_BACK, m_glBackStencilFailOp, m_glBackStencilDepthFailOp, m_glBackStencilPassOp);
		glStencilMaskSeparate(GL_BACK, m_desc.backStencilWriteMask);

		if (m_desc.bFrontStencil || m_desc.bBackStencil)
		{
			glEnable(GL_STENCIL_TEST);
		}
		else
		{
			glDisable(GL_STENCIL_TEST);
		}
	}
}

BLADE_NAMESPACE_END