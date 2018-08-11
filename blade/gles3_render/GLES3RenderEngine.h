#ifndef __BLADE_GLES3RENDERENGINE_H__
#define __BLADE_GLES3RENDERENGINE_H__

#include "util/Singleton.h"
#include "GLES3RenderWindow.h"
#include "GLES3RenderLayout.h"

BLADE_NAMESPACE_BEGIN

enum ClearMask
{
	CM_COLOR = 0x1,
	CM_DEPTH = 0x2,
	CM_STENCIL = 0x4,
};

class BLADE_GLES3RENDER_API RenderEngine : public Singleton < RenderEngine >
{
public:
	RenderEngine();
	~RenderEngine();

public:
	bool                              initialize(const WindowSetting& setting);
	void                              destroy();
	void                              render(RenderLayout* layout);
	void                              setViewport(int left, int top, uint32 width, uint32 height);
	void                              clearGLColor(float r, float g, float b, float a);
	void                              clear(uint32 flags);

	void                              bindGLVAO(GLuint hVAO);
	void                              bindGLProgram(GLuint hProgram);
	void                              bindGLBuffer(GLenum glTarget, GLuint hVBO);

	inline RenderWindow*              getCurrentRenderWindow() const { return m_curRenderWindow; }
	inline GLuint                     getCurrentProgramHandle() const { return m_curGLProgram; }
	inline GLuint                     getCurrentVAOHandle() const { return m_curGLVAO; }

private:
	typedef std::map<GLenum, GLuint> BindBufferMap;

	RenderWindow*        m_curRenderWindow;
	BindBufferMap        m_bindBufferMap;
	GLuint               m_curGLProgram;
	GLuint               m_curGLVAO;
};

BLADE_NAMESPACE_END

#endif
