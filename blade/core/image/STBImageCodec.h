#ifndef __BLADE_STBIMAGECODEC_H__
#define __BLADE_STBIMAGECODEC_H__

#include "ImageCodec.h"

BLADE_NAMESPACE_BEGIN

class BLADE_CORE_API STBImageCodec : public ImageCodec
{
public:
	STBImageCodec(ImageFormat imgFmt);
	virtual ~STBImageCodec();

public:
	bool				encodeToFile(ImageFormat imgFmt, const Buffer &buff, const ImageInfo &imgInfo, const std::string &filename) const;
	bool				encode(Buffer &dstBuff, const Buffer &srcBuff, const ImageInfo &imgInfo) const;
	bool				decode(Buffer &dstBuff, ImageInfo &imgInfo, const Buffer &srcBuff, bool bLoadSplitAlpha);

	static bool			initialize();
	static void			destroy();
};

BLADE_NAMESPACE_END

#endif