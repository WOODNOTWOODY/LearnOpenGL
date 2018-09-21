#ifndef __BLADE_GLES3RENDERENGINE_H__
#define __BLADE_GLES3RENDERENGINE_H__

#include "util/Singleton.h"
#include "GLES3RenderWindow.h"
#include "GLES3RenderLayout.h"
#include "GLES3Texture.h"
#include "GLES3RenderStateObject.h"

BLADE_NAMESPACE_BEGIN

class BLADE_GLES3RENDER_API RenderEngine : public Singleton < RenderEngine >
{
public:
	RenderEngine();
	~RenderEngine();

	static const uint32	MAX_TEXTURE_UNIT_NUM = 8;

public:
	bool                              initialize(const WindowSetting& setting);
	void                              destroy();
	void                              render(RenderLayout* layout);
	void                              setViewport(int left, int top, uint32 width, uint32 height);
	void                              clearGLColor(const Color& color);
	void                              clearGLDepth(float depth);
	void                              clearGLStencil(uint32 stencil);
	void                              clear(uint32 flags);

	void                              bindGLVAO(GLuint hVAO);
	void                              bindGLFBO(GLuint hFBO);
	void                              bindGLProgram(GLuint hProgram);
	void                              bindGLBuffer(GLenum glTarget, GLuint hVBO);
	void                              unbindGLBuffer(GLenum glTarget, GLuint hVBO);
	void                              activeGLTextureUnit(GLenum texUnit);
	void                              bindGLTexture(TextureType type, GLenum glTarget, GLuint hTexture);
	void                              unbindGLTexture(TextureType type, GLenum glTarget, GLuint hTexture);

	inline void                       setDepthStencilState(DepthStencilState* pState)
	{
		m_pCurrentDSS = pState;
		m_curRenderWindow->getContext()->setDepthStencilState(m_pCurrentDSS);
	}

	inline void                       setRasterizerState(RasterizerState* pState)
	{
		m_pCurrentRS = pState;
		m_curRenderWindow->getContext()->setRasterizerState(m_pCurrentRS);
	}

	inline void                       setBlendState(BlendState* pState)
	{
		m_pCurrentBS = pState;
		m_curRenderWindow->getContext()->setBlendState(m_pCurrentBS);
	}

	void							  notifyRasterizerStateReleased(RasterizerState* pState);
	void							  notifyDepthStencilStateReleased(DepthStencilState* pState);
	void							  notifyBlendStateReleased(BlendState* pState);

	inline RenderWindow*              getCurrentRenderWindow() const { return m_curRenderWindow; }
	inline DepthStencilState*         getDefaultDepthStencilState() const { return m_pDefaultDSS; }
	inline RasterizerState*           getDefaultRasterizerState() const { return m_pDefaultRS; }
	inline BlendState*                getDefaultBlendState() const { return m_pDefaultBS; }
	inline DepthStencilState*         getDepthStencilState() const { return m_pCurrentDSS; }
	inline RasterizerState*           getRasterizerState() const { return m_pCurrentRS; }
	inline BlendState*                getBlendState() const { return m_pCurrentBS; }
	inline GLuint                     getCurrentProgramHandle() const { return m_curGLProgram; }
	inline GLuint                     getCurrentGLVAO() const { return m_curGLVAO; }
	inline GLuint                     getCurrentGLFBO() const { return m_curGLFBO; }
	inline GLuint                     getActiveTextureUnit() const { return m_glActiveTexUnit; }

private:
	typedef std::map<GLenum, GLuint> BindBufferMap;

	RenderWindow*        m_curRenderWindow;
	BindBufferMap        m_bindBufferMap;
	DepthStencilState*   m_pDefaultDSS;
	RasterizerState*     m_pDefaultRS;
	BlendState*          m_pDefaultBS;
	DepthStencilState*   m_pCurrentDSS;
	RasterizerState*     m_pCurrentRS;
	BlendState*          m_pCurrentBS;

	GLuint               m_curGLProgram;
	GLuint               m_curGLFBO;
	GLuint               m_curGLVAO;
	GLuint				 m_texUnits[MAX_TEXTURE_UNIT_NUM][TT_COUNT];
	GLuint				 m_glActiveTexUnit;
};

BLADE_NAMESPACE_END

#endif
