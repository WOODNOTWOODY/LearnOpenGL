#include "CoreStd.h"
#include "STBImageCodec.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

BLADE_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////////////////
STBImageCodec::STBImageCodec(ImageFormat imgFmt)
	: ImageCodec(imgFmt)
{
}

STBImageCodec::~STBImageCodec()
{
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
