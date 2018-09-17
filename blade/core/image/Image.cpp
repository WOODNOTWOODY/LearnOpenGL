#include "CoreStd.h"
#include "Image.h"
#include "STBImageCodec.h"
#include "util/PathUtil.h"
#include "util/PixelSampler.h"

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

bool Image::saveToFile(const std::string &filename, ImageFormat imgFmt)
{
	if (!m_data)
	{
		printf("No image data loaded.\n");
		return false;
	}

	if (imgFmt == IF_UNKNOWN)
	{
		imgFmt = Image::getImageFormatByExt(PathUtil::getFileExt(filename));
		if (imgFmt == IF_UNKNOWN)
		{
			printf("Unknown image format.\n");
			return false;
		}
	}

	ImageCodec *pSTBImageCodec = new STBImageCodec(imgFmt);
	if (!pSTBImageCodec)
	{
		printf("Not found image format [%s] codec.\n", Image::getImageFormatExt(imgFmt).c_str());
		return false;
	}

	ImageInfo imgInfo;
	imgInfo.width = m_width;
	imgInfo.height = m_height;
	imgInfo.depth = m_depth;
	imgInfo.size = m_size;
	imgInfo.format = m_format;

	Buffer buff;
	buff.attach(m_size, m_data);
	bool bOK = pSTBImageCodec->encodeToFile(imgFmt, buff, imgInfo, filename);
	buff.detach();
	return bOK;
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

PixelBox Image::getPixelBox(uint32 face, uint32 mipmap) const
{
	// Image data is arranged as:
	// face 0, top level (mip 0)
	// face 0, mip 1
	// face 0, mip 2
	// face 1, top level (mip 0)
	// face 1, mip 1
	// face 1, mip 2
	// etc
	assert(mipmap <= m_numMipmaps, "Mipmap index is out of range.");
	assert(face < getNumFaces(), "Face index is out of range.");

	// Calculate mipmap offset and size
	uint8 *offset = const_cast<uint8*>(m_data);

	// Base offset is number of full faces
	uint32 width = m_width, height = m_height, depth = m_depth;

	// Figure out the offsets 
	uint32 fullFaceSize = 0;
	uint32 finalFaceSize = 0;
	uint32 finalWidth = 0, finalHeight = 0, finalDepth = 0;

	for (uint32 mip = 0; mip <= m_numMipmaps; ++mip)
	{
		if (mip == mipmap)
		{
			finalFaceSize = fullFaceSize;
			finalWidth = width;
			finalHeight = height;
			finalDepth = depth;
			break;
		}

		fullFaceSize += ElementUtil::GetMemorySize(width, height, depth, m_format);

		/// Half size in each dimension
		if (width != 1) width /= 2;
		if (height != 1) height /= 2;
		if (depth != 1) depth /= 2;
	}

	// Advance pointer by number of full faces, plus mip offset into
	offset += face * fullFaceSize;
	offset += finalFaceSize;
	// Return subsurface as pixelbox
	PixelBox src(finalWidth, finalHeight, finalDepth, m_format, offset);

	return src;
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

Color Image::getColor(int x, int y, int z) const
{
	Color rval;
	ElementUtil::UnpackColor(rval, m_format, &m_data[m_pixelSize * (z * m_width * m_height + m_width * y + x)]);
	return rval;
}

void Image::setColor(Color const &cv, int x, int y, int z)
{
	ElementUtil::PackColor(cv, m_format, &m_data[m_pixelSize * (z * m_width * m_height + m_width * y + x)]);
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

bool Image::scale(uint32 width, uint32 height, ImageFilter filter)
{
	// scale dynamic images is not supported
	assert(m_depth == 1);

	// reassign buffer to temp image, make sure auto-delete is true
	Image tempImg(m_data, m_width, m_height, 1, m_format);

	// do not delete[] m_pBuffer!  temp will destroy it

	// set new dimensions, allocate new buffer
	m_width = width;
	m_height = height;
	m_size = ElementUtil::GetMemorySize(m_width, m_height, 1, m_format);
	m_data = (Byte*)BLADE_MALLOC(m_size);
	m_numMipmaps = 0; // Loses precomputed mipmaps

	// scale the image from temp into our resized buffer
	if (!Image::Scale(tempImg.getPixelBox(), getPixelBox(), filter))
		return false;

	return true;
}

bool Image::Scale(const PixelBox &src, const PixelBox &dst, ImageFilter filter)
{
	assert(!ELEMENT_IS_COMPRESSED(src.format));
	assert(!ELEMENT_IS_COMPRESSED(dst.format));

	Buffer buf; // For auto-delete
	PixelBox temp;
	switch (filter)
	{
	default:
	case IMGFILTER_NEAREST:
	{
		if (src.format == dst.format)
		{
			// No intermediate buffer needed
			temp = dst;
		}
		else
		{
			// Allocate temporary buffer of destination size in source format 
			temp = PixelBox(dst.getWidth(), dst.getHeight(), dst.getDepth(), src.format);
			buf.allocate(temp.getConsecutiveSize());
			temp.data = buf.data();
		}
		// super-optimized: no conversion
		switch (ELEMENT_SIZE(src.format))
		{
		case 1: NearestSampler<1>::Scale(src, temp); break;
		case 2: NearestSampler<2>::Scale(src, temp); break;
		case 3: NearestSampler<3>::Scale(src, temp); break;
		case 4: NearestSampler<4>::Scale(src, temp); break;
		case 6: NearestSampler<6>::Scale(src, temp); break;
		case 8: NearestSampler<8>::Scale(src, temp); break;
		case 12: NearestSampler<12>::Scale(src, temp); break;
		case 16: NearestSampler<16>::Scale(src, temp); break;
		default:
		{
			// never reached
			assert(false);
			return false;
		}
		}

		if (temp.data != dst.data)
		{
			// Blit temp buffer
			ElementUtil::BulkPixelConversion(temp, dst);
		}
	} break;
	case IMGFILTER_LINEAR:
	case IMGFILTER_BILINEAR:
	{
		switch (src.format)
		{
		case EF_R8:
		case EF_R8_SNORM:
		case EF_R8_UINT:
		case EF_R8_SINT:
		case EF_RGB8:
		case EF_RGB8_SNORM:
		case EF_RGB8_UINT:
		case EF_RGB8_SINT:
		case EF_BGR8:
		case EF_RGBA8:
		case EF_RGBA8_SNORM:
		case EF_RGBA8_UINT:
		case EF_RGBA8_SINT:
		case EF_BGRA8:
		{
			if (src.format == dst.format)
			{
				// No intermediate buffer needed
				temp = dst;
			}
			else
			{
				// Allocate temp buffer of destination size in source format 
				temp = PixelBox(dst.getWidth(), dst.getHeight(), dst.getDepth(), src.format);
				buf.allocate(temp.getConsecutiveSize());
				temp.data = buf.data();
			}
			// super-optimized: byte-oriented math, no conversion
			switch (ELEMENT_SIZE(src.format))
			{
			case 1: LinearSamplerByte<1>::Scale(src, temp); break;
			case 2: LinearSamplerByte<2>::Scale(src, temp); break;
			case 3: LinearSamplerByte<3>::Scale(src, temp); break;
			case 4: LinearSamplerByte<4>::Scale(src, temp); break;
			default:
			{
				// never reached
				assert(false);
				return false;
			}
			}
			if (temp.data != dst.data)
			{
				// Blit temp buffer
				ElementUtil::BulkPixelConversion(temp, dst);
			}
		} break;
		case EF_RGB32_FLOAT:
		case EF_RGBA32_FLOAT:
		{
			if (dst.format == EF_RGB32_FLOAT || dst.format == EF_RGBA32_FLOAT)
			{
				// float32 to float32, avoid unpack/repack overhead
				LinearSamplerFloat32::Scale(src, dst);
				break;
			}
		}
			// else, fall through
		default:
		{
			// non-optimized: floating-point math, performs conversion but always works
			LinearSampler::Scale(src, dst);
		} break;
		} // switch
	} break;
	}

	return true;
}

BLADE_NAMESPACE_END
