#ifndef __BLADE_GLES3RENDERLAYOUT_H__
#define __BLADE_GLES3RENDERLAYOUT_H__

#include "util/Element.h"
#include "GLES3GPUBuffer.h"
#include "GLES3Shader.h"

BLADE_NAMESPACE_BEGIN

#define MAX_VERTEX_STREAM 8

enum PrimitiveMode
{
	PM_POINTS,
	PM_LINES,
	PM_LINE_STRIPE,
	PM_TRIANGLES,
	PM_TRIANGLE_STRIPE,
};

struct VertexElement
{
	std::string     name;
	ElementFormat   format;
	uint32          streamIdx;
	uint32          offset;
	bool            bNormalized;

	VertexElement()
		: streamIdx(0)
		, offset(0)
		, bNormalized(false)
	{}
};

typedef std::vector<VertexElement> VertexElementList;

class BLADE_GLES3RENDER_API RenderLayout
{
public:
	RenderLayout();
	~RenderLayout();

	typedef std::vector<GPUBuffer*> GPUBufferList;
	typedef std::map<uint32, GPUBuffer*> GPUBufferMap;

public:
	void                              setPrimitiveMode(PrimitiveMode mode);
	inline PrimitiveMode              getPrimitiveMode() const { return m_primitiveMode; }
	inline void						  setStartVertexIndex(uint32 startVertIndex) { m_startVertIndex = startVertIndex; }
	inline uint32                     getStartVertexIndex() const { return m_startVertIndex; }
	inline void                       setVertexCount(uint32 vertexCount) { m_vertCount = vertexCount; }
	inline uint32                     getVertexCount() const { return m_vertCount; }
	inline void                       setStartIndex(uint32 startIndex) { m_startIndex = startIndex; }
	inline uint32                     getStartIndex() const { return m_startIndex; }
	inline void                       setIndexCount(uint32 indexCount) { m_indexCount = indexCount; }
	inline uint32                     getIndexCount() const { return m_indexCount; }
	inline void                       setIndexStride(uint32 indexStride) { m_indexStride = indexStride; }
	inline uint32                     getIndexStride() const { return m_indexStride; }
	inline ShaderProgram*             getProgram() const { return m_program; }
	inline uint32                     getVertexElementCount() const { return m_vertElements.size(); }
	inline const VertexElementList&   getVertexElements() const { return m_vertElements; }
	inline void                       setVertexBuffer(uint32 idx, GPUBuffer* vertBuffer) { m_vertBuffers[idx] = vertBuffer; }
	inline GPUBuffer*                 getVertexBuffer(uint32 idx) const { return m_vertBuffers[idx]; }
	inline void                       setIndexBuffer(GPUBuffer* indexBuffer) { m_indexBuffer = indexBuffer; }
	inline GPUBuffer*                 getIndexBuffer() const { return m_indexBuffer; }

	inline GLuint                     getVAOHandle() const { return m_glVAO; }
	inline GLenum                     getGLPrimitiveMode() const { return m_glPrimitiveMode; }
	inline GLenum                     getGLIndexType() const { return m_glIndexType; }
	inline GLenum                     getGLProgram() const { return m_glProgram; }

	bool                              initialize(const VertexElementList& vertElements, ShaderProgram* program);
	void                              destroy();
	void                              bindGPUBuffers();
	void                              bind();
	void                              unbind();

private:
	ShaderProgram*      m_program;
	PrimitiveMode       m_primitiveMode;

	GPUBuffer*          m_vertBuffers[MAX_VERTEX_STREAM];
	VertexElementList   m_vertElements;
	uint32              m_startVertIndex;
	uint32              m_vertCount;

	GPUBuffer*          m_indexBuffer;
	uint32              m_startIndex;
	uint32              m_indexCount;
	uint32              m_indexStride;

	GLuint              m_glProgram;
	GLuint              m_glVAO;
	GLenum              m_glPrimitiveMode;
	GLenum              m_glIndexType;
};

BLADE_NAMESPACE_END

#endif
