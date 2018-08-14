#ifndef __BLADE_GLES3RENDERSTATEOBJECT_H__
#define __BLADE_GLES3RENDERSTATEOBJECT_H__

#include "util/Color.h"
#include "math/MathLib.h"

BLADE_NAMESPACE_BEGIN

enum ComparisonFunc
{
	CF_NEVER,
	CF_LESS,
	CF_LESS_EQUAL,
	CF_EQUAL,
	CF_GREATER_EQUAL,
	CF_GREATER,
	CF_ALWAYS,
	CF_NOT_EQUAL,
};

enum AddressMode
{
	AM_WRAP,
	AM_MIRROR,
	AM_CLAMP,
	AM_BORDER,
};

enum FilterOption
{
	FO_NONE,
	FO_POINT,
	FO_LINEAR,
	FO_ANISOTROPIC,
};

struct SamplerStateDesc
{
	FilterOption    minFilter;
	FilterOption    magFilter;
	FilterOption    mipFilter;
	AddressMode     addrModeU;
	AddressMode     addrModeV;
	AddressMode     addrModeW;
	uint8           maxAnisotropy;
	Color           borderColor;
	ComparisonFunc  cmpFunc;
	float			minLOD;
	float			maxLOD;
	float			mipLODBias;

	SamplerStateDesc()
	{
		minFilter = FO_LINEAR;
		magFilter = FO_LINEAR;
		mipFilter = FO_LINEAR;
		addrModeU = AM_WRAP;
		addrModeV = AM_WRAP;
		addrModeW = AM_WRAP;
		maxAnisotropy = 16;
		borderColor = COLOR_BLACK;
		cmpFunc = CF_NEVER;
		minLOD = 0.0f;
		maxLOD = Math::MAX_FLOAT;
		mipLODBias = 0.0f;
	}
};

class BLADE_GLES3RENDER_API SamplerState
{
public:
	SamplerState();
	SamplerState(const SamplerStateDesc& desc);
	~SamplerState() {}

public:
	inline void                     setName(const std::string& name) { m_name = name; }
	inline const std::string&       getName() const { return m_name; }
	inline const SamplerStateDesc&  getDesc() const { return m_desc; }

	inline GLint		            getGLAddrModeU() const { return m_glAddrModeU; }
	inline GLint		            getGLAddrModeV() const { return m_glAddrModeV; }
	inline GLint		            getGLAddrModeW() const { return m_glAddrModeW; }
	inline GLenum                   getGLMinFilter() const { return m_glMinFilter; }
	inline GLenum                   getGLMagFilter() const { return m_glMagFilter; }

private:
	void                            create();
		 
private:
	std::string      m_name;
	SamplerStateDesc m_desc;

	GLint			 m_glAddrModeU;
	GLint			 m_glAddrModeV;
	GLint			 m_glAddrModeW;
	GLenum           m_glMinFilter;
	GLenum           m_glMagFilter;
};

BLADE_NAMESPACE_END

#endif
