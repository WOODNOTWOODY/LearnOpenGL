#ifndef __BLADE_IMAGE_H__
#define __BLADE_IMAGE_H__

#include "util/Buffer.h"
#include "util/Element.h"
#include "util/Color.h"

BLADE_NAMESPACE_BEGIN

enum ImageFormat
{
	IF_UNKNOWN, 
	IF_JPG,					//!< JPEG - .jpg, .jpe and .jpeg extensions
	IF_PNG,					//!< Portable Network Graphics - .png extension
};

struct ImageInfo 
{
	uint32					width;
	uint32					height;
	uint32					depth;
	uint32					size;
	uint16					numMipmaps;			//!< used for dds.
	uint32					flags;
	ElementFormat			format;
	bool					bHasSplitAlpha;

	ImageInfo() : width(0), height(0), depth(0), size(0), numMipmaps(0), flags(0), format(EF_UNKNOWN), bHasSplitAlpha(false) {};
};

enum ImageFlags
{
	IMGFLAG_COMPRESSED	= 0x00000001, 
	IMGFLAG_CUBEMAP		= 0x00000002, 
	IMGFLAG_3DTEX		= 0x00000004, 
};

enum ImageFilter
{
	IMGFILTER_NEAREST, 
	IMGFILTER_LINEAR, 
	IMGFILTER_BILINEAR, 
	IMGFILTER_BOX, 
	IMGFILTER_TRIANGLE, 
	IMGFILTER_BICUBIC, 
};

class BLADE_CORE_API Image
{
private:
	Image();

public:
	Image(Byte *pData, uint32 width, uint32 height, uint32 depth,
		ElementFormat format, uint32 numFaces = 1, uint32 numMipMaps = 1);
	~Image();

	static const uint32	MAX_MINMAPS = 16;

public:
	static Image*				createFromMemory(const Buffer &buff, ImageFormat imgFmt, bool bLoadSplitAlpha = false);
	bool						saveToFile(const std::string &filename, ImageFormat imgFmt = IF_UNKNOWN);
	void						destroy();

	inline bool					hasFlag(ImageFlags imgFlag) const { return ((m_flags & imgFlag) != 0); }
	inline uint32				getFlags() const { return m_flags; }
	inline ElementFormat		getElementFormat() const { return m_format; }
	inline uint32				getNumMipmaps() const { return m_numMipmaps; }
	inline uint32				getWidth() const { return m_width; }
	inline uint32				getHeight() const { return m_height; }
	inline uint32				getDepth() const { return m_depth; }
	inline uint32				getPixelSize() const { return m_pixelSize; }
	inline uint32				getSize() const { return m_size; }
	inline Byte*				getData() const { return m_data; }
	inline uint32				getNumFaces() const { return (hasFlag(IMGFLAG_CUBEMAP) ? 6 : 1); }
	inline bool					hasAlpha() const { return ELEMENT_HAS_ALPHA(m_format); }
	inline Byte					getBPP() const { return ELEMENT_BITS(m_format); }
	inline bool					hasSplitAlpha() const { return m_bHasSplitAlpha; }

	static std::string			getImageFormatExt(ImageFormat imgFmt);
	static ImageFormat			getImageFormat(const std::string &filename);
	static ImageFormat			getImageFormatByExt(const std::string &imgExt);

	/**
	* Get color value from a certain location in the image. The z coordinate
	* is only valid for cubemap and volume textures. This uses the first (largest) mipmap.
	*/
	Color						getColor(int x, int y, int z = 0) const;
	
	// Static function to calculate size in bytes from the number of mipmaps, faces and the dimensions
	static uint32				calculateSize(uint32 mipmaps, uint32 faces, uint32 width, uint32 height, uint32 depth, ElementFormat format);

private:
	ElementFormat		m_format;			// The pixel format of the image
	uint32				m_width;			// The width of the image in pixels
	uint32				m_height;			// The height of the image in pixels
	uint32				m_depth;			// The depth of the image
	uint32				m_numMipmaps;		// The number of mipmaps the image contains
	uint32				m_flags;			// Image specific flags.
	uint32				m_pixelSize;		// The number of bytes per pixel
	uint32				m_size;
	Byte*				m_data;
	bool				m_bHasSplitAlpha;
};
	
BLADE_NAMESPACE_END

#endif