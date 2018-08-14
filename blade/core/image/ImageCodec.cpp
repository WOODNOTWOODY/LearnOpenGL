#include "CoreStd.h"
#include "ImageCodec.h"

BLADE_NAMESPACE_BEGIN

ImageCodec::ImageCodec(ImageFormat imgFmt):
m_imgFmt(imgFmt)
{
}

ImageCodec::~ImageCodec()
{
}

ImageFormat ImageCodec::getImageFormat() const
{
	return m_imgFmt;
}

BLADE_NAMESPACE_END
