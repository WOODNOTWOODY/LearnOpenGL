#include "GLES3RenderStd.h"
#include "GLES3Viewport.h"

BLADE_NAMESPACE_BEGIN

Viewport::Viewport(FrameBuffer* pFrameBuffer)
	: m_pFrameBuffer(pFrameBuffer)
	, m_left(0)
	, m_top(0)
	, m_width(0)
	, m_height(0)
	, m_widthRatio(1.0f)
	, m_heightRatio(1.0f)
{
}

BLADE_NAMESPACE_END