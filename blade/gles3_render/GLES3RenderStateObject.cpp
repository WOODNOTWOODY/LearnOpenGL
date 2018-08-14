#include "GLES3RenderStd.h"
#include "GLES3RenderStateObject.h"
#include "GLES3Mapping.h"

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

BLADE_NAMESPACE_END