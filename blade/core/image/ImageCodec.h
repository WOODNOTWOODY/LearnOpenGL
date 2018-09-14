#ifndef __BLADE_IMAGECODEC_H__
#define __BLADE_IMAGECODEC_H__

#include "util/Buffer.h"
#include "util/Element.h"
#include "Image.h"

BLADE_NAMESPACE_BEGIN

class BLADE_CORE_API ImageCodec
{
public:
	ImageCodec(ImageFormat imgFmt);
	virtual ~ImageCodec();

public:
	virtual ImageFormat			getImageFormat() const;
	virtual bool				encodeToFile(ImageFormat imgFmt, const Buffer &buff, const ImageInfo &imgInfo, const std::string &filename) const = 0;
	virtual bool				encode(Buffer &dstBuff, const Buffer &srcBuff, const ImageInfo &info) const = 0;
	virtual bool				decode(Buffer &dstBuff, ImageInfo &info, const Buffer &srcBuff, bool bLoadSplitAlpha = false) = 0;

protected:
	ImageFormat			m_imgFmt;
};

BLADE_NAMESPACE_END

#endif