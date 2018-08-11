#ifndef __BLADE_GLES3GPUBUFFER_H__
#define __BLADE_GLES3GPUBUFFER_H__

BLADE_NAMESPACE_BEGIN

enum GPUBufferType
{
	GBT_VERTEX,
	GBT_INDEX,
};

enum GPUBufferUsage
{
	GBU_STATIC_DRAW,
	GBU_DYNAMIC_DRAW,
	GBU_STREAM_DRAW,
};

enum GPUBufferAccess
{
	GBA_READ_ONLY,
	GBA_WRITE_ONLY,
	GBA_READ_WRITE,
	GBA_WRITE_DISCARD,
};

struct GPUBufferDesc
{
	GPUBufferType type;
	uint32        usage;
	uint32        stride;
	uint32        size;
	void*         buffer;
	bool          bBak;

	GPUBufferDesc()
		: type(GBT_VERTEX)
		, usage(0)
		, stride(0)
		, size(0)
		, buffer(NULL)
		, bBak(true)
	{}
};

class BLADE_GLES3RENDER_API GPUBuffer
{
public:
	GPUBuffer();
	~GPUBuffer();

public:
	bool                     initialize(const GPUBufferDesc& desc);

	inline GPUBufferType     getType() const { return m_type; }
	inline uint32            getStride() const { return m_stride; }
	inline uint32            getCount() const { return m_count; }
	inline uint32            getSize() const { return m_size; }
	inline Byte*             getBuffer() const { return m_buffer; }
	inline GLenum            getGLTarget() const { return m_glTarget; }
	inline uint32            getGLBuffer() const { return m_glBuffer; }

private:
	GPUBufferType m_type;
	uint32        m_usage;
	uint32        m_stride;
	uint32        m_count;
	uint32        m_size;
	Byte*         m_buffer;

	GLenum        m_glTarget;
	uint32        m_glBuffer;
};

BLADE_NAMESPACE_END

#endif
