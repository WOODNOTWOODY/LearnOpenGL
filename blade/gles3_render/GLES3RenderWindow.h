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

	inline bool					    isMainWindow() const { return false; }
	inline const std::string&		getName() const { return m_name; }
	inline uint32					getLeft() const { return m_left; }
	inline uint32					getTop() const { return m_top; }
	inline uint32					getWidth() const { return m_width; }
	inline uint32					getHeight() const { return m_height; }
	inline RenderContext*		    getContext() const { return m_pContext; }
	inline FrameBuffer*             getDefaultFrameBuffer() const { return m_pFrameBuffer; }
	inline FrameBuffer*             getCurrentFrameBuffer() const { return m_pCurFrameBuffer; }
	inline void                     setCurrentFrameBuffer(FrameBuffer* pFrameBuffer) { m_pCurFrameBuffer = pFrameBuffer; }
	
#if (BLADE_PLATFORM == BLADE_PLATFORM_MAC_IOS)
	bool				            renderbufferStorage();
	inline intptr		            getEAGLView() const { return m_eaglView; }
	inline intptr		            getEAGLContext() const { return m_eaglContext; }
#else
	inline EGLDisplay	            getEGLDisplay() const { return m_eglDisplay; }
	inline EGLConfig	            getEGLConfig() const { return m_eglConfig; }
	inline EGLSurface	            getEGLSurface() const { return m_eglSurface; }
#endif

private:
	std::string       m_name;
	uint32            m_left;
	uint32            m_top;
	uint32            m_width;
	uint32            m_height;
	RenderContext*    m_pContext;
	FrameBuffer*      m_pFrameBuffer;
	FrameBuffer*      m_pCurFrameBuffer;

#if (BLADE_PLATFORM == BLADE_PLATFORM_MAC_IOS)
	intptr			  m_eaglView;
	intptr			  m_eaglContext;
#else
	EGLDisplay		  m_eglDisplay;
	EGLConfig		  m_eglConfig;
	EGLSurface		  m_eglSurface;
#endif
};

BLADE_NAMESPACE_END

#endif
