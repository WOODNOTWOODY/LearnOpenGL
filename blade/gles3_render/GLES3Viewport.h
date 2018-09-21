#ifndef __BLADE_GLES3VIEWPORT_H__
#define __BLADE_GLES3VIEWPORT_H__

BLADE_NAMESPACE_BEGIN

class FrameBuffer;

class BLADE_GLES3RENDER_API Viewport
{
public:
	Viewport(FrameBuffer* pFrameBuffer);

public:
	inline void        resize(int left, int top, uint32 width, uint32 height) { m_left = left; m_top = top; m_width = width; m_height = height; }
	inline void        setLeft(int left) { m_left = left; }
	inline void        setTop(int top) { m_top = top; }
	inline void        setWidth(uint32 w) { m_width = w; }
	inline void        setHeight(uint32 h) { m_height = h; }
	inline void        setWidthRatio(float ratio) { m_widthRatio = ratio; }
	inline void        setHeightRatio(float ratio) { m_heightRatio = ratio; }
	inline int         getLeft() const { return m_left; }
	inline int         getTop() const { return m_top; }
	inline uint32      getWidth() const { return m_width; }
	inline uint32      getHeight() const { return m_height; }
	inline float       getWidthRatio() const { return m_widthRatio; }
	inline float       getHeightRatio() const { return m_heightRatio; }
	inline uint32      getActualWidth() const { return (uint32)(m_width * m_widthRatio); }
	inline uint32      getActualHeight() const { return (uint32)(m_height * m_heightRatio); }

private:
	FrameBuffer*         m_pFrameBuffer;
	int                  m_left;
	int                  m_top;
	uint32               m_width;
	uint32               m_height;
	float                m_widthRatio;
	float                m_heightRatio;
};

BLADE_NAMESPACE_END

#endif
