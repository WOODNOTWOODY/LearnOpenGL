#include "GLES3RenderStd.h"
#include "GLES3RenderStateObject.h"
#include "GLES3Mapping.h"
#include "GLES3RenderContext.h"
#include "GLES3RenderEngine.h"

BLADE_NAMESPACE_BEGIN

RasterizerState::RasterizerState()
{
	create();
}

RasterizerState::RasterizerState(const RasterizerStateDesc& desc)
	: m_desc(desc)
{
	create();
}

RasterizerState::~RasterizerState()
{
	RenderEngine::Instance()->notifyRasterizerStateReleased(this);
}

void RasterizerState::create()
{
	m_glFrontFace = m_desc.bFrontFaceCCW ? GL_CCW : GL_CW;
}

void RasterizerState::bind(bool bForce)
{
	RenderContext* pContext = RenderEngine::Instance()->getCurrentRenderWindow()->getContext();
	RasterizerState* pCurState = pContext->getRasterizerState();
	if (pCurState && !bForce)
	{
		const RasterizerStateDesc& curDesc = pCurState->getDesc();
		if (m_desc.bDiscard != curDesc.bDiscard)
		{
			if (m_desc.bDiscard)
			{
				glEnable(GL_RASTERIZER_DISCARD);
			}
			else
			{
				glDisable(GL_RASTERIZER_DISCARD);
			}
		}

		if (m_desc.cullMode != curDesc.cullMode)
		{
			switch (m_desc.cullMode)
			{
			case CULL_NONE:
				{
					glDisable(GL_CULL_FACE);
				} break;
			case CULL_FRONT:
				{
					glEnable(GL_CULL_FACE);
					glCullFace(GL_FRONT);
				} break;
			case CULL_BACK:
				{
					glEnable(GL_CULL_FACE);
					glCullFace(GL_BACK);
				} break;
			default: break;
			}
		}

		if (m_desc.bFrontFaceCCW != curDesc.bFrontFaceCCW)
		{
			glFrontFace(m_glFrontFace);
		}

		if ((m_desc.depthBiasFactor != curDesc.depthBiasFactor) ||
			(m_desc.depthBias != curDesc.depthBias))
		{
			glPolygonOffset(m_desc.depthBiasFactor, m_desc.depthBias);
		}
	}
	else
	{
		if (m_desc.bDiscard)
		{
			glEnable(GL_RASTERIZER_DISCARD);
		}
		else
		{
			glDisable(GL_RASTERIZER_DISCARD);
		}

		switch (m_desc.cullMode)
		{
			case CULL_NONE:
			{
				glDisable(GL_CULL_FACE);
			} break;
			case CULL_FRONT:
			{
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT);
			} break;
			case CULL_BACK:
			{
				glEnable(GL_CULL_FACE);
				glCullFace(GL_BACK);
			} break;
			default: break;
		}

		glFrontFace(m_glFrontFace);
		glPolygonOffset(m_desc.depthBiasFactor, m_desc.depthBias);
	}
}

BlendState::BlendState()
{
	create();
}

BlendState::BlendState(const BlendStateDesc& desc)
	: m_desc(desc)
{
	create();
}

BlendState::~BlendState()
{
	RenderEngine::Instance()->notifyBlendStateReleased(this);
}

void BlendState::create()
{
	m_glBlendOp = GLES3Mapping::mapBlendOperation(m_desc.targets[0].blendOp);
	m_glAlphaBlendOp = GLES3Mapping::mapBlendOperation(m_desc.targets[0].alphaBlendOp);
	m_glSrcBlend = GLES3Mapping::mapBlendFactor(m_desc.targets[0].srcBlend);
	m_glDstBlend = GLES3Mapping::mapBlendFactor(m_desc.targets[0].dstBlend);
	m_glSrcAlphaBlend = GLES3Mapping::mapBlendFactor(m_desc.targets[0].srcAlphaBlend);
	m_glDstAlphaBlend = GLES3Mapping::mapBlendFactor(m_desc.targets[0].dstAlphaBlend);
	m_glRedMask = (m_desc.targets[0].colorWriteMask & CWM_R) != 0;
	m_glGreenMask = (m_desc.targets[0].colorWriteMask & CWM_G) != 0;
	m_glBlueMask = (m_desc.targets[0].colorWriteMask & CWM_B) != 0;
	m_glAlphaMask = (m_desc.targets[0].colorWriteMask & CWM_A) != 0;
}

void BlendState::bind(bool bForce)
{
	RenderContext* pContext = RenderEngine::Instance()->getCurrentRenderWindow()->getContext();
	BlendState* pCurState = pContext->getBlendState();
	if (pCurState && !bForce)
	{
		const BlendStateDesc& curDesc = pCurState->getDesc();
		if (m_desc.bA2C != curDesc.bA2C)
		{
			if (m_desc.bA2C)
			{
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
			}
			else
			{
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
			}
		}

		if (m_desc.targets[0].bBlend != curDesc.targets[0].bBlend)
		{
			if (m_desc.targets[0].bBlend)
			{
				glEnable(GL_BLEND);
			}
			else
			{
				glDisable(GL_BLEND);
			}
		}

		if (m_desc.targets[0].blendOp != curDesc.targets[0].blendOp || 
			m_desc.targets[0].alphaBlendOp != curDesc.targets[0].alphaBlendOp)
		{
			glBlendEquationSeparate(m_glBlendOp, m_glAlphaBlendOp);
		}

		if ((m_desc.targets[0].srcBlend != curDesc.targets[0].srcBlend) ||
			(m_desc.targets[0].dstBlend != curDesc.targets[0].dstBlend) ||
			(m_desc.targets[0].srcAlphaBlend != curDesc.targets[0].srcAlphaBlend) ||
			(m_desc.targets[0].dstAlphaBlend != curDesc.targets[0].dstAlphaBlend))
		{
			glBlendFuncSeparate(m_glSrcBlend, m_glDstBlend, m_glSrcAlphaBlend, m_glDstAlphaBlend);
		}

		if (m_desc.targets[0].colorWriteMask != curDesc.targets[0].colorWriteMask)
		{
			glColorMask(m_glRedMask, m_glGreenMask, m_glBlueMask, m_glAlphaMask);
		}

		if (m_desc.blendFactor != curDesc.blendFactor)
		{
			glBlendColor((GLclampf)m_desc.blendFactor.r, (GLclampf)m_desc.blendFactor.g, (GLclampf)m_desc.blendFactor.b, (GLclampf)m_desc.blendFactor.a);
		}
	}
	else
	{
		if (m_desc.bA2C)
		{
			glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		}
		else
		{
			glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		}

		if (m_desc.targets[0].bBlend)
		{
			glEnable(GL_BLEND);
		}
		else
		{
			glDisable(GL_BLEND);
		}

		glBlendEquationSeparate(m_glBlendOp, m_glAlphaBlendOp);
		glBlendFuncSeparate(m_glSrcBlend, m_glDstBlend, m_glSrcAlphaBlend, m_glDstAlphaBlend);
		glColorMask(m_glRedMask, m_glGreenMask, m_glBlueMask, m_glAlphaMask);
		glBlendColor((GLclampf)m_desc.blendFactor.r, (GLclampf)m_desc.blendFactor.g, (GLclampf)m_desc.blendFactor.b, (GLclampf)m_desc.blendFactor.a);
	}
}

void BlendState::colorMaskGL()
{
	glColorMask(m_glRedMask, m_glGreenMask, m_glBlueMask, m_glAlphaMask);
}

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

DepthStencilState::~DepthStencilState()
{
	RenderEngine::Instance()->notifyDepthStencilStateReleased(this);
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