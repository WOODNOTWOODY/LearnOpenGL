#ifndef __BLADE_GLES3SHADER_H__
#define __BLADE_GLES3SHADER_H__

#include "util/Buffer.h"

BLADE_NAMESPACE_BEGIN

enum ParamType
{
	PT_UNKNOWN,
	PT_1BV,
	PT_2BV,
	PT_3BV,
	PT_4BV,
	PT_1IV,
	PT_2IV,
	PT_3IV,
	PT_4IV,
	PT_1UIV,
	PT_2UIV,
	PT_3UIV,
	PT_4UIV,
	PT_1FV,
	PT_2FV,
	PT_3FV,
	PT_4FV,
	PT_MAT2X2FV,
	PT_MAT2X3FV,
	PT_MAT2X4FV,
	PT_MAT3X2FV,
	PT_MAT3X3FV,
	PT_MAT3X4FV,
	PT_MAT4X2FV,
	PT_MAT4X3FV,
	PT_MAT4X4FV,
	PT_SAMPLER2D,
	PT_SAMPLER3D,
	PT_COUNT,
};

class BLADE_GLES3RENDER_API Attribute
{
public:
	Attribute(const std::string& name, GLenum glType, GLint glLoc);
	~Attribute();

public:
	inline const std::string&        getName() const { return m_name; }
	inline ParamType                 getType() const { return m_type; }
	inline uint32                    getSize() const { return m_size; }

	inline GLenum                    getGLType() const { return m_glType; }
	inline GLint                     getGLLocation() const { return m_glLoc; }

private:
	std::string  m_name;
	ParamType    m_type;
	uint32       m_size;

	GLenum       m_glType;
	GLint        m_glLoc;
};

class BLADE_GLES3RENDER_API Uniform
{
public:
	Uniform(const std::string& name, uint32 count, GLenum glType, GLint glLoc);
	~Uniform();

public:
	inline const std::string&        getName() const { return m_name; }
	inline ParamType                 getType() const { return m_type; }
	inline uint32                    getElementSize() const { return m_elementSize; }
	inline uint32                    getSize() const { return m_size; }
	inline uint32                    getCount() const { return m_count; }
	inline Byte*                     getData() const { return m_buffer; }
	inline GLenum                    getGLType() const { return m_glType; }
	inline GLint                     getGLLocation() const { return m_glLoc; }
	inline bool                      isDirty() const { return m_bDirty; }
	inline void                      setDirty(bool flag) { m_bDirty = flag; }
	inline bool                      isSampler() const { return m_bSampler; }

	inline void                      setData(const Buffer& buff) 
	{ 
		uint32 size = std::min(buff.size(), m_size);
		memcpy(m_buffer, buff.data(), size);
		m_bDirty = true;
	}

	inline void                      setData(void* data, uint32 size)
	{
		size = std::min(size, m_size);
		memcpy(m_buffer, data, size);
		m_bDirty = true;
	}

	template <typename T>
	inline void				         setValue(const T& data)
	{
		uint32 size = std::min((uint32)sizeof(T), m_size);
		memcpy(m_buffer, &data, size);
		m_bDirty = true;
	}

	template <typename T>
	inline void				         setArray(T* data, uint32 count)
	{
		uint32 elmCount = std::min(count, m_count);
		memcpy(m_buffer, data, m_elementSize * elmCount);
		m_bDirty = true;
	}

private:
	std::string  m_name;
	ParamType    m_type;
	uint32       m_elementSize;
	uint32       m_size;
	uint32       m_count;
	Byte*        m_buffer;
	bool         m_bDirty;
	bool         m_bSampler;

	GLenum       m_glType;
	GLint        m_glLoc;

};

enum ShaderType
{
	ST_VERTEX_SHADER,
	ST_FRAGMENT_SHADER,
	ST_SHADER_COUNT,
};

class BLADE_GLES3RENDER_API RefCounter
{
public:
	RefCounter();
	virtual ~RefCounter();

	void retain();
	void release();

protected:
	int32 m_refCnt;
};

class BLADE_GLES3RENDER_API Shader : public RefCounter
{
public:
	Shader(const std::string& name, ShaderType type, const Buffer& buffer);
	~Shader();

public:
	bool                              compile();
	inline bool                       isCompiled() const { return m_bCompiled; }

	inline const std::string&         getName() const { return m_name; }
	inline ShaderType                 getType() const { return m_type; }
	inline Byte*                      getData() const { return m_data; }
	inline uint32                     getSize() const { return m_size; }
	inline GLuint                     getShaderHandle() const { return m_glShader; }

private:
	std::string   m_name;
	ShaderType    m_type;
	bool          m_bCompiled;
	uint32        m_size;
	Byte*         m_data;

	GLuint        m_glShader;
};

typedef std::vector<Shader*> ShaderList;

class Texture;

class BLADE_GLES3RENDER_API ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	typedef std::map<std::string, Attribute*> AttrMap;
	typedef std::map<std::string, Uniform*> UniformMap;
	typedef std::map<uint32, Texture*> TextureBindMap;
	
public:
	inline uint32                getId() const { return m_id; }
	inline const std::string&    getName() const { return m_name; }
	inline GLuint				 getProgramHandle() const { return m_glProgram; }
	Attribute*                   getAttribute(const std::string& name);
	Uniform*                     getUniform(const std::string& name);
	Texture*                     getTexture(uint32 unit) const;


	bool                         attachShader(Shader* pShader);
	bool                         detachShader(Shader* pShader);
	bool                         setShaders(const ShaderList& shaders);
	bool                         parseParams();
	void                         bindUniforms();
	void                         bindTexture(uint32 unit, Texture* texture);
	void                         bind();
	void                         unbind();

	inline bool                  isLinked() const { return m_bLinked; }
	bool                         prepareLink();
	bool                         linkShaders();
	bool                         compileAndLinkShaders();

private:
	uint32          m_id;
	std::string     m_name;
	AttrMap         m_attrs;
	UniformMap      m_uniforms;
	TextureBindMap  m_textures;
	Shader*         m_shaderList[ST_SHADER_COUNT];
	bool            m_bLinked;
	GLuint          m_glProgram;
};

BLADE_NAMESPACE_END

#endif
