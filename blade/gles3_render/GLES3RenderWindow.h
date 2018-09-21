#ifndef __BLADE_GLES3RENDERWINDOW_H__
#define __BLADE_GLES3RENDERWINDOW_H__

#include "camera/Camera.h"
#include "GLES3RenderContext.h"
#include "GLES3FrameBuffer.h"

BLADE_NAMESPACE_BEGIN

struct WindowSetting
{
	std::string     name;
	uint32          top;
	uint32          left;
	uint32          width;
	uint32          height;

	WindowSetting()
		: name("")
		, top(0)
		, left(0)
		, width(800)
		, height(600)
	{}
};

class BLADE_GLES3RENDER_API RenderWindow
{
public:
	RenderWindow();
	~RenderWindow();

public:
	bool                            initialize(const WindowSetting& setting);
	void                            destroy();
	void                            swapBuffers();
	bool                            isActive();
	void                            processInput(Camera* camera, float deltaTime);
	void                            pollEvents();

	inline const std::string&		getName() const { return m_name; }
	inline uint32					getLeft() const { return m_left; }
	inline uint32					getTop() const { return m_top; }
	inline uint32					getWidth() const { return m_width; }
	inline uint32					getHeight() const { return m_height; }
	inline RenderContext*		    getContext() const { return m_pContext; }
	inline FrameBuffer*             getDefaultFrameBuffer() const { return m_pFrameBuffer; }
	inline FrameBuffer*             getCurrentFrameBuffer() const { return m_pCurFrameBuffer; }
	inline void                     setCurrentFrameBuffer(FrameBuffer* pFrameBuffer) { m_pCurFrameBuffer = pFrameBuffer; }
	inline GLFWwindow*              getGLFWWindow() const { return m_glfwWindow; }

private:
	std::string       m_name;
	uint32            m_left;
	uint32            m_top;
	uint32            m_width;
	uint32            m_height;
	RenderContext*    m_pContext;
	FrameBuffer*      m_pFrameBuffer;
	FrameBuffer*      m_pCurFrameBuffer;

	GLFWwindow*       m_glfwWindow;
};

BLADE_NAMESPACE_END

#endif
