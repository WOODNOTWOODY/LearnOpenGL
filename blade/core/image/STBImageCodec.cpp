#include "CoreStd.h"
#include "STBImageCodec.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

BLADE_NAMESPACE_BEGIN

static const Buffer* encodeBitmap(const Buffer& buff, const ImageInfo& imgInfo, Buffer& convBuff, int& comp)
{
	ElementFormat srcFormat = imgInfo.format;
	ElementFormat requiredFormat = srcFormat;

	std::string name = ElementUtil::GetFormatName(srcFormat);

	switch (srcFormat)
	{
	case EF_R5G6B5:
	case EF_RGB8:
	case EF_RGBA8:
	case EF_RG8:
	case EF_RGBA4:
	case EF_RGB5A1:
	case EF_RGB10A2:
	case EF_A8:
	case EF_R8:
		if (ELEMENT_HAS_ALPHA(srcFormat))
		{
			requiredFormat = EF_RGBA8;
			comp = 4;
		}
		else
		{
			requiredFormat = EF_RGB8;
			comp = 3;
		}
		break;
	default:
		printf("STBI encodeBitmap: invalid image format.\n");
		return NULL;
	};


	if (requiredFormat != srcFormat)
	{
		int size = ElementUtil::GetMemorySize(imgInfo.width, imgInfo.height, 1, requiredFormat);
		convBuff.allocate(size);

		const size_t srcPixelSize = ELEMENT_SIZE(srcFormat);
		const size_t dstPixelSize = ELEMENT_SIZE(requiredFormat);
		uint8* srcptr = buff.data();
		uint8* dstptr = convBuff.data();

		// Calculate pitches+skips in bytes
		const size_t srcRowSkipBytes = 0;
		const size_t dstRowSkipBytes = 0;

		// The brute force fallback
		float r = 0, g = 0, b = 0, a = 1;
		for (size_t y = 0; y<imgInfo.height; y++)
		{
			for (size_t x = 0; x<imgInfo.width; x++)
			{
				ElementUtil::UnpackColor(r, g, b, a, srcFormat, srcptr);
				ElementUtil::PackColor(r, g, b, a, requiredFormat, dstptr);
				srcptr += srcPixelSize;
				dstptr += dstPixelSize;
			}
			srcptr += srcRowSkipBytes;
			dstptr += dstRowSkipBytes;
		}
		return &convBuff;
	}

	return &buff;
}

///////////////////////////////////////////////////////////////////////////////////////////
STBImageCodec::STBImageCodec(ImageFormat imgFmt)
	: ImageCodec(imgFmt)
{
}

STBImageCodec::~STBImageCodec()
{
}

bool STBImageCodec::encodeToFile(ImageFormat imgFmt, const Buffer &buff, const ImageInfo &imgInfo, const std::string &filename) const
{
	if (imgFmt == IF_PNG)
	{
		Buffer convBuff;
		int comp;
		const Buffer* retbuff = encodeBitmap(buff, imgInfo, convBuff, comp);
		if (retbuff)
		{
			if (imgFmt == IF_PNG)
			{
				stbi_write_png(filename.c_str(), imgInfo.width, imgInfo.height, comp, retbuff->data(), imgInfo.width*comp);
				return true;
			}
		}
		return false;
	}

	printf("STBI encodeToFile not supported imgfmt: %d.\n", imgFmt);
	return false;
}

bool STBImageCodec::encode(Buffer &dstBuff, const Buffer& srcBuff, const ImageInfo &imgInfo) const
{
	printf("STBI encoding not supported.\n");
	return false;
}

bool STBImageCodec::decode(Buffer &dstBuff, ImageInfo &info, const Buffer &srcBuff, bool bLoadSplitAlpha)
{
	int width = 0;
	int height = 0;
	int components = 0;
	stbi_uc *pixelData = NULL;
	try
	{
		pixelData = stbi_load_from_memory(srcBuff.data(), static_cast<int>(srcBuff.size()), &width, &height, &components, 0);
	}
	catch (...)
	{
		printf("stbi_load_from_memory failed.\n");
	}

	if(!pixelData)
	{
		printf("Error decoding image: %s.\n", stbi_failure_reason());
		return false;
	}

	info.depth = 1;			// only 2D formats handled by this codec
	info.width = width;
	info.height = height;
	info.numMipmaps = 1;	// no mipmaps in non-DDS 
	info.flags = 0;

	switch(components)
	{
	case 3:
		{
			info.format = EF_RGB8;
		} break;
	case 4:
		{
			info.format = EF_RGBA8;
		} break;
	default:
		{
			stbi_image_free(pixelData);
			printf("Unknown or unsupported image format.\n");
			return false;
		}
	}

	uint32 dstPitch = info.width * ELEMENT_SIZE(info.format);
	info.size = dstPitch * info.height;

	dstBuff.allocate(info.size);
	dstBuff.write(pixelData, info.size);

	stbi_image_free(pixelData);

	return true;
}

bool STBImageCodec::initialize()
{
	stbi_convert_iphone_png_to_rgb(1);
	stbi_set_unpremultiply_on_load(1);

	return true;
}

void STBImageCodec::destroy()
{
}

BLADE_NAMESPACE_END
