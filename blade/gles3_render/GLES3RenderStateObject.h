#ifndef __BLADE_GLES3RENDERSTATEOBJECT_H__
#define __BLADE_GLES3RENDERSTATEOBJECT_H__

#include "util/Color.h"
#include "math/MathLib.h"

BLADE_NAMESPACE_BEGIN

enum ColorWriteMask
{
	CWM_R = 1 << 0,
	CWM_G = 1 << 1,
	CWM_B = 1 << 2,
	CWM_A = 1 << 3,
	CWM_ALL = CWM_R | CWM_G | CWM_B | CWM_A
};

enum ComparisonFunc : unsigned char
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

enum StencilOperation : unsigned char
{
	SOP_KEEP,        // The currently stored stencil value is kept
	SOP_ZERO,        // The stencil value is set to 0
	SOP_REPLACE,     // The stencil value is replaced with the reference value set weith glStencilFunc
	SOP_INCR,        // The stencil value is increased by 1 if it is lower than the maximum value
	SOP_INCR_WRAP,   // Same as SOP_INCR, but wraps it back to 0 as soon as the maximum value is exceeded
	SOP_DECR,        // The stencil value is decreased by 1 if it is higher than the minimum value
	SOP_DECR_WRAP,   // Same as SOP_DECR, but wraps it back to maximum value if it ends up lower than 0
	SOP_INVERT,      // Bitwise inverts the current stencil buffer value
};

enum PolygonMode : unsigned char
{
	PM_POINT,
	PM_LINE,
	PM_FILL,
};

enum CullMode : unsigned char
{
	CULL_NONE,
	CULL_FRONT,
	CULL_BACK,
};

enum BlendOperation : unsigned char
{
	BOP_ADD,
	BOP_SUB,
	BOP_REV_SUB,
};

enum BlendFactor : unsigned char
{
	BF_ZERO,
	BF_ONE,
	BF_SRC_ALPHA,
	BF_DST_ALPHA,
	BF_ONE_MINUS_SRC_ALPHA,
	BF_ONE_MINUS_DST_ALPHA,
	BF_SRC_COLOR,
	BF_DST_COLOR,
	BF_ONE_MINUS_SRC_COLOR,
	BF_ONE_MINUS_DST_COLOR,
	BF_SRC_ALPHA_SAT,
};

enum AddressMode : unsigned char
{
	AM_WRAP,
	AM_MIRROR,
	AM_CLAMP,
	AM_BORDER,
};

enum FilterOption : unsigned char
{
	FO_NONE,
	FO_POINT,
	FO_LINEAR,
	FO_ANISOTROPIC,
};

struct RasterizerStateDesc
{
	bool            bDiscard;
	PolygonMode     polygonMode;
	CullMode        cullMode;
	bool            bFrontFaceCCW;

	// depth bias
	// z = depthBiasFactor * DZ + depthBias
	// DZ is max depth slope
	float		    depthBias;
	float		    depthBiasFactor;

	RasterizerStateDesc()
	{
		polygonMode = PM_FILL;
		cullMode = CULL_BACK;
		bFrontFaceCCW = true;
		depthBias = 0.0f;
		depthBiasFactor = 0.0f;
	}

	inline bool operator == (const RasterizerStateDesc& desc) const
	{
		return (bDiscard == desc.bDiscard) && (polygonMode == desc.polygonMode) && (cullMode == desc.cullMode) && 
			(bFrontFaceCCW == desc.bFrontFaceCCW) && Math::IsEqual(depthBias, desc.depthBias) &&
			Math::IsEqual(depthBiasFactor, desc.depthBiasFactor);
	}

	inline bool operator != (const RasterizerStateDesc& desc) const { return !((*this) == desc); }
};

class BLADE_GLES3RENDER_API RasterizerState
{
public:
	RasterizerState();
	RasterizerState(const RasterizerStateDesc& desc);
	~RasterizerState();

public:
	void                               bind(bool bForce = false);
	inline void                        setName(const std::string& name) { m_name = name; }
	inline const std::string&          getName() const { return m_name; }
	inline const RasterizerStateDesc&  getDesc() const { return m_desc; }

private:
	void                               create();

private:
	std::string          m_name;
	RasterizerStateDesc  m_desc;
	GLenum               m_glFrontFace;
};

struct TargetBlendStateDesc
{
	bool                 bBlend;
	BlendFactor          srcBlend;
	BlendFactor          dstBlend;
	BlendOperation       blendOp;
	BlendFactor          srcAlphaBlend;
	BlendFactor          dstAlphaBlend;
	BlendOperation       alphaBlendOp;
	uint8                colorWriteMask;

	TargetBlendStateDesc()
	{
		bBlend = false;
		srcBlend = BF_ONE;
		dstBlend = BF_ZERO;
		blendOp = BOP_ADD;
		srcAlphaBlend = BF_ONE;
		dstAlphaBlend = BF_ZERO;
		alphaBlendOp = BOP_ADD;
		colorWriteMask = CWM_ALL;
	}

	inline bool operator == (const TargetBlendStateDesc& desc) const
	{
		return (bBlend == desc.bBlend) && (srcBlend == desc.srcBlend) && (dstBlend == desc.dstBlend) &&
			(blendOp == desc.blendOp) && (srcAlphaBlend == desc.srcAlphaBlend) && (dstAlphaBlend == desc.dstAlphaBlend) &&
			(alphaBlendOp == desc.alphaBlendOp) && (colorWriteMask == desc.colorWriteMask);
	}

	inline bool operator != (const TargetBlendStateDesc& desc) const { return !((*this) == desc); }
};

typedef std::vector<TargetBlendStateDesc> TargetBlendStateDescList;
struct BlendStateDesc
{
	bool                          bA2C;
	Color                         blendFactor;
	TargetBlendStateDescList      targets;

	BlendStateDesc()
	{
		bA2C = false;
		blendFactor.r = 0;
		blendFactor.g = 0;
		blendFactor.b = 0;
		blendFactor.a = 0;

		TargetBlendStateDesc target;
		targets.push_back(std::move(target));
	}

	inline bool operator == (const BlendStateDesc& desc) const
	{
		if (targets.size() == desc.targets.size())
		{
			for (size_t i = 0; i < targets.size(); ++i)
			{
				if (targets[i] != desc.targets[i])
				{
					return false;
				}
			}

			return (bA2C == desc.bA2C) && (blendFactor == desc.blendFactor);
		}
		else
		{
			return false;
		}
	}

	inline bool operator != (const BlendStateDesc& desc) const { return !((*this) == desc); }
};

class BLADE_GLES3RENDER_API BlendState
{
public:
	BlendState();
	BlendState(const BlendStateDesc& desc);
	~BlendState();

public:
	inline void                     setName(const std::string& name) { m_name = name; }
	inline const std::string&       getName() const { return m_name; }
	inline const BlendStateDesc&    getDesc() const { return m_desc; }

	void                            bind(bool bForce = false);
	void                            colorMaskGL();

private:
	void                            create();

private:
	std::string     m_name;
	BlendStateDesc  m_desc;
	GLenum			m_glBlendOp;
	GLenum			m_glAlphaBlendOp;
	GLenum			m_glSrcBlend;
	GLenum			m_glDstBlend;
	GLenum			m_glSrcAlphaBlend;
	GLenum			m_glDstAlphaBlend;
	GLboolean		m_glRedMask;
	GLboolean		m_glGreenMask;
	GLboolean		m_glBlueMask;
	GLboolean		m_glAlphaMask;
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

	inline bool operator == (const SamplerStateDesc& desc) const
	{
		return (minFilter == desc.minFilter) && (magFilter == desc.magFilter) && (mipFilter == desc.mipFilter) &&
			(addrModeU == desc.addrModeU) && (addrModeV == desc.addrModeV) && (addrModeW == desc.addrModeW) &&
			(maxAnisotropy == desc.maxAnisotropy) && (cmpFunc == desc.cmpFunc) && (borderColor == desc.borderColor) &&
			Math::IsEqual(minLOD, desc.minLOD) && Math::IsEqual(maxLOD, desc.maxLOD) && Math::IsEqual(mipLODBias, desc.mipLODBias);
	}

	inline bool operator != (const SamplerStateDesc& desc) const { return !((*this) == desc); }
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

struct DepthStencilStateDesc
{
	bool               bDepth;
	bool               bWriteDepth;
	ComparisonFunc     depthFunc;

	bool               bFrontStencil;
	ComparisonFunc     frontStencilFunc;
	uint32             frontStencilReadMask;
	uint32             frontStencilWriteMask;
	StencilOperation   frontStencilFailOp;
	StencilOperation   frontStencilDepthFailOp;
	StencilOperation   frontStencilPassOp;
	uint32             frontStencilRef;

	bool               bBackStencil;
	ComparisonFunc     backStencilFunc;
	uint32             backStencilReadMask;
	uint32             backStencilWriteMask;
	StencilOperation   backStencilFailOp;
	StencilOperation   backStencilDepthFailOp;
	StencilOperation   backStencilPassOp;
	uint32             backStencilRef;

	DepthStencilStateDesc()
	{
		bDepth = true;
		bWriteDepth = true;
		depthFunc = CF_LESS;

		bFrontStencil = false;
		frontStencilFunc = CF_ALWAYS;
		frontStencilReadMask = 0xffffffff;
		frontStencilWriteMask = 0xffffffff;
		frontStencilFailOp = SOP_KEEP;
		frontStencilDepthFailOp = SOP_INCR;
		frontStencilPassOp = SOP_KEEP;
		frontStencilRef = 1;

		bBackStencil = false;
		backStencilFunc = CF_ALWAYS;
		backStencilReadMask = 0xffffffff;
		backStencilWriteMask = 0xffffffff;
		backStencilFailOp = SOP_KEEP;
		backStencilDepthFailOp = SOP_DECR;
		backStencilPassOp = SOP_KEEP;
		backStencilRef = 1;
	}

	inline bool operator == (const DepthStencilStateDesc& desc) const
	{
		return (bDepth == desc.bDepth) && (bWriteDepth == desc.bWriteDepth) && (depthFunc == desc.depthFunc) &&
			(bFrontStencil == desc.bFrontStencil) && (frontStencilFunc == desc.frontStencilFunc) &&
			(frontStencilReadMask == desc.frontStencilReadMask) && (frontStencilWriteMask == desc.frontStencilWriteMask) &&
			(frontStencilFailOp == desc.frontStencilFailOp) && (frontStencilDepthFailOp == desc.frontStencilDepthFailOp) &&
			(frontStencilPassOp == desc.frontStencilPassOp) && (frontStencilRef == desc.frontStencilRef) &&
			(bBackStencil == desc.bBackStencil) && (backStencilFunc == desc.backStencilFunc) &&
			(backStencilReadMask == desc.backStencilReadMask) && (backStencilWriteMask == desc.backStencilWriteMask) &&
			(backStencilFailOp == desc.backStencilFailOp) && (backStencilDepthFailOp == desc.backStencilDepthFailOp) &&
			(backStencilPassOp == desc.backStencilPassOp) && (backStencilRef == desc.backStencilRef);
	}

	inline bool operator != (const DepthStencilStateDesc& desc) const { return !((*this) == desc); }
};

class BLADE_GLES3RENDER_API DepthStencilState
{
public:
	DepthStencilState();
	DepthStencilState(const DepthStencilStateDesc& desc);
	~DepthStencilState();

public:
	inline void                          setName(const std::string& name) { m_name = name; }
	inline const std::string&            getName() const { return m_name; }
	inline const DepthStencilStateDesc&  getDesc() const { return m_desc; }

	void                                 bind(bool bForce = false);

private:
	void                                 create();

private:
	std::string           m_name;
	DepthStencilStateDesc m_desc;

	GLboolean             m_glDepthMask;
	GLenum				  m_glDepthFunc;
	GLenum				  m_glFrontStencilFunc;
	GLenum				  m_glFrontStencilFailOp;
	GLenum				  m_glFrontStencilDepthFailOp;
	GLenum				  m_glFrontStencilPassOp;
	GLenum				  m_glBackStencilFunc;
	GLenum				  m_glBackStencilFailOp;
	GLenum				  m_glBackStencilDepthFailOp;
	GLenum				  m_glBackStencilPassOp;
};

BLADE_NAMESPACE_END

#endif
