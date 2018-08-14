#include "CoreStd.h"
#include "Image.h"
#include "STBImageCodec.h"
#include "util/PathUtil.h"

BLADE_NAMESPACE_BEGIN

Image::Image(): 
m_format(EF_UNKNOWN), 
m_width(0), 
m_height(0), 
m_depth(0), 
m_numMipmaps(1), 
m_flags(0), 
m_pixelSize(0), 
m_size(0), 
m_data(NULL),
m_bHasSplitAlpha(false)
{
}

Image::Image(Byte *pData, uint32 width, uint32 height, uint32 depth, 
	ElementFormat format, uint32 numFaces, uint32 numMipMaps)
{
	// Set image metadata
	m_format = format;
	m_width = width;
	m_height = height;
	m_depth = depth;
	m_numMipmaps = numMipMaps;
	m_flags = 0;
	m_pixelSize = ELEMENT_SIZE(format);
	m_bHasSplitAlpha = false;

	// Set flags
	if (ELEMENT_IS_COMPRESSED(format))
		m_flags |= IMGFLAG_COMPRESSED;
	if (m_depth != 1)
		m_flags |= IMGFLAG_3DTEX;
	if(numFaces == 6)
		m_flags |= IMGFLAG_CUBEMAP;
	if (numFaces != 6 && numFaces != 1)
	{
		printf("Number of faces currently must be 6 or 1.\n");
	}

	m_size = calculateSize(m_numMipmaps, numFaces, width, height, depth, format);
	m_data = (Byte*)BLADE_MALLOC(m_size);
	if(pData)
	{
		memcpy(m_data, pData, m_size);
	}
	else
	{
		memset(m_data, 0, m_size);
	}
}

Image::~Image()
{
	destroy();
}

Image* Image::createFromMemory(const Buffer &buff, ImageFormat imgFmt, bool bLoadSplitAlpha)
{
	ImageCodec *pSTBImageCodec = new STBImageCodec(IF_PNG);
	if (!pSTBImageCodec)
	{
		printf("Unable to load image: Image format [%s] is unknown. Unable to identify codec.", getImageFormatExt(imgFmt).c_str());
		return NULL;
	}

	Buffer dstBuff;
	ImageInfo info;
	if (!pSTBImageCodec->decode(dstBuff, info, buff, bLoadSplitAlpha))
		return NULL;

	Image *pImage = BLADE_NEW(Image);
	
	pImage->m_width = info.width;
	pImage->m_height = info.height;
	pImage->m_depth = info.depth;
	pImage->m_size = info.size;
	pImage->m_numMipmaps = info.numMipmaps;
	pImage->m_flags = info.flags;

	// Get the format and compute the pixel size
	pImage->m_format = info.format;
	pImage->m_pixelSize = static_cast<Byte>(ELEMENT_SIZE(info.format));
	// Just use internal buffer of returned memory stream

	pImage->m_data = dstBuff.detach();
	pImage->m_bHasSplitAlpha = info.bHasSplitAlpha;

	return pImage;
}

void Image::destroy()
{
	BLADE_SAFE_FREE(m_data);

	m_format = EF_UNKNOWN;
	m_width = 0;
	m_height = 0;
	m_depth = 0;
	m_numMipmaps = 0;
	m_flags = 0;
	m_pixelSize = 0;
	m_size = 0;
}

std::string Image::getImageFormatExt(ImageFormat imgFmt)
{
	switch(imgFmt)
	{
		case IF_JPG:			return "jpg";
		case IF_PNG:			return "png";
		default:				return "unknown";
	}
}

ImageFormat Image::getImageFormat(const std::string &filename)
{
	std::string fileExt = PathUtil::getFileExt(filename);
	return getImageFormatByExt(fileExt);
}

ImageFormat Image::getImageFormatByExt(const std::string &imgExt)
{
	std::string imgExtStr = imgExt;
	std::transform(imgExtStr.begin(), imgExtStr.end(), imgExtStr.begin(), tolower);

	if(imgExtStr == "png")
		return IF_PNG;
	else if(imgExtStr == "jpg" || imgExtStr == "jpeg" || imgExtStr == "jpe")
		return IF_JPG;
	else
		return IF_UNKNOWN;
}

uint32 Image::calculateSize(uint32 mipmaps, uint32 faces, uint32 width, uint32 height, uint32 depth, ElementFormat format)
{
	uint32 size = 0;
	for(uint32 mip = 0; mip < mipmaps; ++mip)
	{
		size += ElementUtil::GetMemorySize(width, height, depth, format) * faces;
		width = std::max(width >> 1, 1U);
		height = std::max(height >> 1, 1U);
		depth = std::max(depth >> 1, 1U);
	}

	return size;
}

BLADE_NAMESPACE_END
