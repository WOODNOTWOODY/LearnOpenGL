#include "GLES3RenderStd.h"
#include "GLES3Shader.h"
#include "GLES3RenderEngine.h"
#include "GLES3Mapping.h"

BLADE_NAMESPACE_BEGIN

static uint32 genShaderId()
{
	static uint32 g_curId = 0;
	return g_curId++;
}

static uint32 getParamTypeSize(ParamType type)
{
	switch (type)
	{
		case PT_1BV:
		case PT_1IV:
		case PT_1UIV:
		case PT_1FV:			return 4; break;

		case PT_2BV:
		case PT_2IV:
		case PT_2UIV:
		case PT_2FV:			return 8; break;

		case PT_3BV:
		case PT_3IV:
		case PT_3UIV:
		case PT_3FV:			return 12; break;

		case PT_4BV:
		case PT_4IV:
		case PT_4UIV:
		case PT_4FV:			return 16; break;

		case PT_MAT2X2FV:		return 16; break;
		case PT_MAT2X3FV:		return 24; break;
		case PT_MAT2X4FV:		return 32; break;
		case PT_MAT3X2FV:		return 24; break;
		case PT_MAT3X3FV:		return 36; break;
		case PT_MAT3X4FV:		return 48; break;
		case PT_MAT4X2FV:		return 32; break;
		case PT_MAT4X3FV:		return 48; break;
		case PT_MAT4X4FV:		return 64; break;
		case PT_SAMPLER2D:
		case PT_SAMPLER3D:      return 4; break;
		default:
		{
			return 0;
		}
	}
}

RefCounter::RefCounter()
	: m_refCnt(1)
{

}

RefCounter::~RefCounter()
{

}

void RefCounter::retain()
{
	++m_refCnt;
}

void RefCounter::release()
{
	if (--m_refCnt <= 0)
	{
		BLADE_DELETE(this);
	}
}

Attribute::Attribute(const std::string& name, GLenum glType, GLint glLoc)
	: m_name(name)
	, m_glType(glType)
	, m_glLoc(glLoc)
{
	m_type = GLES3Mapping::unmapParamType(m_glType);
	m_size = getParamTypeSize(m_type);
}

Attribute::~Attribute()
{

}

Uniform::Uniform(const std::string& name, uint32 count, GLenum glType, GLint glLoc)
	: m_name(name)
	, m_count(count)
	, m_glType(glType)
	, m_glLoc(glLoc)
	, m_bDirty(true)
	, m_bSampler(false)
{
	m_type = GLES3Mapping::unmapParamType(m_glType);
	m_elementSize = getParamTypeSize(m_type);
	m_size = m_elementSize * m_count;
	m_bSampler = (m_type == PT_SAMPLER2D || m_type == PT_SAMPLER3D);
	m_buffer = (Byte*)BLADE_MALLOC(m_size);
}

Uniform::~Uniform()
{
	BLADE_SAFE_FREE(m_buffer);
}

Shader::Shader(const std::string& name, ShaderType type, const Buffer& buffer)
	: m_name(name)
	, m_type(type)
	, m_bCompiled(false)
	, m_size(buffer.size())
	, m_data(NULL)
	, m_glShader(0)
{
	if (m_size)
	{
		m_data = (Byte*)BLADE_MALLOC(m_size);
		memcpy(m_data, buffer.data(), buffer.size());
	}

	GLenum shaderType;
	switch (m_type)
	{
		case ST_VERTEX_SHADER: shaderType = GL_VERTEX_SHADER; break;
		case ST_FRAGMENT_SHADER: shaderType = GL_FRAGMENT_SHADER; break;
		default:
		{
			shaderType = GL_VERTEX_SHADER;
			printf("Unknown shader type.\n");
		} break;
	}
	
	m_glShader = glCreateShader(shaderType);
}

Shader::~Shader()
{
	BLADE_SAFE_FREE(m_data);
	if (m_glShader)
	{
		glDeleteShader(m_glShader);
		m_glShader = 0;
	}
}

bool Shader::compile()
{
	// bind shader source code to the shader object
	glShaderSource(m_glShader, 1, (const GLchar**)&m_data, NULL);

	// compile shader
	glCompileShader(m_glShader);

	// check to see if the shader compiled successfully
	GLint status;
	glGetShaderiv(m_glShader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		// get the size of the string containing the failed shader compilation message
		GLint logSize = 0;
		glGetShaderiv(m_glShader, GL_INFO_LOG_LENGTH, &logSize);

		// create a buffer to hold the log info
		GLchar* szLogInfo = (GLchar*)BLADE_MALLOC(++logSize);

		// retrieve the log info
		glGetShaderInfoLog(m_glShader, logSize, NULL, szLogInfo);

		// print the log info
		printf("Shader [%s] compilation failed: \n%s", m_name.c_str(), szLogInfo);

		BLADE_FREE(szLogInfo);

		m_bCompiled = false;
		return false;
	}

	m_bCompiled = true;
	return true;
}

ShaderProgram::ShaderProgram()
	: m_bLinked(false)
{
	for (uint32 i = 0; i < ST_SHADER_COUNT; ++i)
	{
		m_shaderList[i] = NULL;
	}

	m_id = genShaderId();

	m_glProgram = glCreateProgram();
	if (!m_glProgram)
	{
		printf("GLShaderProgram [%s] handle invalid.", m_name.c_str());
	}
}

ShaderProgram::~ShaderProgram()
{
	for (auto& it : m_attrs)
	{
		BLADE_SAFE_DELETE(it.second);
	}

	for (auto& it : m_uniforms)
	{
		BLADE_SAFE_DELETE(it.second);
	}

	for (uint32 i = 0; i < ST_SHADER_COUNT; ++i)
	{
		if (m_shaderList[i])
		{
			m_shaderList[i]->release();
		}
	}

	if (m_glProgram)
	{
		glDeleteProgram(m_glProgram);
		m_glProgram = 0;
	}
}

Attribute* ShaderProgram::getAttribute(const std::string& name)
{
	AttrMap::iterator it = m_attrs.find(name);
	if (it != m_attrs.end())
	{
		return it->second;
	}
	return NULL;
}

Uniform* ShaderProgram::getUniform(const std::string& name)
{
	UniformMap::iterator it = m_uniforms.find(name);
	if (it != m_uniforms.end())
	{
		return it->second;
	}
	return NULL;
}

bool ShaderProgram::attachShader(Shader* pShader)
{
	if (pShader)
	{
		glAttachShader(m_glProgram, pShader->getShaderHandle());
		return true;
	}
	return false;
}

bool ShaderProgram::detachShader(Shader* pShader)
{
	if (pShader)
	{
		glDetachShader(m_glProgram, pShader->getShaderHandle());
		return true;
	}
	return false;
}

bool ShaderProgram::setShaders(const ShaderList& shaders)
{
	for (auto it = shaders.begin(); it != shaders.end(); ++it)
	{
		Shader* pShader = *it;
		ShaderType type = pShader->getType();
		if (type < ST_SHADER_COUNT && !m_shaderList[type])
		{
			pShader->retain();
			m_shaderList[type] = pShader;
		}
		else
		{
			return false;
		}
	}
	return true;
}


bool ShaderProgram::prepareLink()
{
	for (uint32 i = 0; i < ST_SHADER_COUNT; ++i)
	{
		if (m_shaderList[i])
		{
			if (!attachShader(m_shaderList[i]))
			{
				return false;
			}
		}
	}
	return true;
}

bool ShaderProgram::compileAndLinkShaders()
{
	for (uint32 i = 0; i < ST_SHADER_COUNT; ++i)
	{
		Shader* pShader = m_shaderList[i];
		if (pShader && !pShader->isCompiled())
		{
			if (!pShader->compile())
			{
				return false;
			}
		}
	}
	return linkShaders();
}


bool ShaderProgram::linkShaders()
{
	if (!m_bLinked)
	{
		glLinkProgram(m_glProgram);

		GLint status;
		glGetProgramiv(m_glProgram, GL_LINK_STATUS, &status);
		if (status != GL_TRUE)
		{
			// get the size of the string containing the failed shader compilation message
			GLint logSize = 0;
			glGetProgramiv(m_glProgram, GL_INFO_LOG_LENGTH, &logSize);

			// create a buffer to hold the log info
			GLchar* szLogInfo = (GLchar*)BLADE_MALLOC(++logSize);

			// retrieve the log info
			glGetProgramInfoLog(m_glProgram, logSize, NULL, szLogInfo);

			// print the log info
			printf("Link Shaders of program [%s] failed: \n%s", m_name.c_str(), szLogInfo);

			BLADE_FREE(szLogInfo);

			m_bLinked = false;
			return false;
		}

		m_bLinked = true;
	}
	return true;
}

bool ShaderProgram::parseParams()
{
	GLint activeAttrMaxLength = 0;
	GLint activeAttrCount = 0;
	glGetProgramiv(m_glProgram, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &activeAttrMaxLength);
	glGetProgramiv(m_glProgram, GL_ACTIVE_ATTRIBUTES, &activeAttrCount);

	GLsizei glLength;
	GLsizei glSize;
	GLenum glType;
	GLchar glName[256];
	for (GLint i = 0; i < activeAttrCount; ++i)
	{
		memset(glName, 0, sizeof(glName));
		glGetActiveAttrib(m_glProgram, i, activeAttrMaxLength, &glLength, &glSize, &glType, glName);

		// NVidia returns name[0] for arrays, need to strip after [
		char* offset = strchr(glName, '[');
		if (offset)
		{
			offset[0] = '\0';
		}

		std::string name = glName;
		if (!(name.size() > 3 && (name.substr(0, 3) == "gl_")))
		{
			GLint glLoc = glGetAttribLocation(m_glProgram, name.c_str());
			if (glLoc == -1)
			{
				printf("Not found the shader input attr [%s] in shader.\n", name.c_str());
			}
			else
			{
				Attribute* attr = BLADE_NEW(Attribute(name, glType, glLoc));
				m_attrs.insert(AttrMap::value_type(name, attr));
			}
		}
	}

	GLint uniformCount;
	glGetProgramiv(m_glProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &activeAttrMaxLength);
	glGetProgramiv(m_glProgram, GL_ACTIVE_UNIFORMS, &uniformCount);
	for (GLint i = 0; i < uniformCount; ++i)
	{
		memset(glName, 0, sizeof(glName));
		glGetActiveUniform(m_glProgram, i, activeAttrMaxLength, &glLength, &glSize, &glType, glName);

		GLint glLoc = glGetUniformLocation(m_glProgram, glName);
		if (glLoc == -1)
		{
			printf("Not found the shader input uniform [%s] in shader.\n", glName);
		}
		else
		{
			Uniform* uniform = BLADE_NEW(Uniform(glName, glSize, glType, glLoc));
			m_uniforms.insert(UniformMap::value_type(glName, uniform));
		}
	}

	return true;
}

void ShaderProgram::bindUniforms()
{
	for (auto it : m_uniforms)
	{
		Uniform* uniform = it.second;
		if (uniform->isDirty())
		{
			switch (uniform->getType())
			{
				case PT_SAMPLER2D:
				case PT_SAMPLER3D: glUniform1i(uniform->getGLLocation(), (GLint)uniform->getGLLocation()); break;
				case PT_1BV:
				case PT_1IV: glUniform1iv(uniform->getGLLocation(), uniform->getCount(), (GLint*)uniform->getData()); break;
				case PT_2BV:
				case PT_2IV: glUniform2iv(uniform->getGLLocation(), uniform->getCount(), (GLint*)uniform->getData()); break;
				case PT_3BV:
				case PT_3IV: glUniform3iv(uniform->getGLLocation(), uniform->getCount(), (GLint*)uniform->getData()); break;
				case PT_4BV:
				case PT_4IV: glUniform4iv(uniform->getGLLocation(), uniform->getCount(), (GLint*)uniform->getData()); break;
				case PT_1UIV: glUniform1uiv(uniform->getGLLocation(), uniform->getCount(), (GLuint*)uniform->getData()); break;
				case PT_2UIV: glUniform2uiv(uniform->getGLLocation(), uniform->getCount(), (GLuint*)uniform->getData()); break;
				case PT_3UIV: glUniform3uiv(uniform->getGLLocation(), uniform->getCount(), (GLuint*)uniform->getData()); break;
				case PT_4UIV: glUniform4uiv(uniform->getGLLocation(), uniform->getCount(), (GLuint*)uniform->getData()); break;
				case PT_1FV: glUniform1fv(uniform->getGLLocation(), uniform->getCount(), (GLfloat*)uniform->getData()); break;
				case PT_2FV: glUniform2fv(uniform->getGLLocation(), uniform->getCount(), (GLfloat*)uniform->getData()); break;
				case PT_3FV: glUniform3fv(uniform->getGLLocation(), uniform->getCount(), (GLfloat*)uniform->getData()); break;
				case PT_4FV: glUniform4fv(uniform->getGLLocation(), uniform->getCount(), (GLfloat*)uniform->getData()); break;
				case PT_MAT2X2FV: glUniformMatrix2fv(uniform->getGLLocation(), uniform->getCount(), false, (GLfloat*)uniform->getData()); break;
				case PT_MAT2X3FV: glUniformMatrix2x3fv(uniform->getGLLocation(), uniform->getCount(), false, (GLfloat*)uniform->getData()); break;
				case PT_MAT2X4FV: glUniformMatrix2x4fv(uniform->getGLLocation(), uniform->getCount(), false, (GLfloat*)uniform->getData()); break;
				case PT_MAT3X2FV: glUniformMatrix3x2fv(uniform->getGLLocation(), uniform->getCount(), false, (GLfloat*)uniform->getData()); break;
				case PT_MAT3X3FV: glUniformMatrix3fv(uniform->getGLLocation(), uniform->getCount(), false, (GLfloat*)uniform->getData()); break;
				case PT_MAT3X4FV: glUniformMatrix3x4fv(uniform->getGLLocation(), uniform->getCount(), false, (GLfloat*)uniform->getData()); break;
				case PT_MAT4X2FV: glUniformMatrix4x2fv(uniform->getGLLocation(), uniform->getCount(), false, (GLfloat*)uniform->getData()); break;
				case PT_MAT4X3FV: glUniformMatrix4x3fv(uniform->getGLLocation(), uniform->getCount(), false, (GLfloat*)uniform->getData()); break;
				case PT_MAT4X4FV: glUniformMatrix4fv(uniform->getGLLocation(), uniform->getCount(), false, (GLfloat*)uniform->getData()); break;
				default:
				{
					printf("Unsupported uniform type in shader [%s].\n", m_name.c_str());
				}
			}

			uniform->setDirty(false);
		}

		if (uniform->isSampler())
		{
			Texture* texture = getTexture(uniform->getGLLocation());
			if (texture)
			{
				RenderEngine::Instance()->activeGLTextureUnit(uniform->getGLLocation());
				RenderEngine::Instance()->bindGLTexture(texture->getType(), texture->getGLTarget(), texture->getTextureHandle());
				glTexParameteri(texture->getGLTarget(), GL_TEXTURE_MIN_FILTER, texture->getSamplerState()->getGLMinFilter());
				glTexParameteri(texture->getGLTarget(), GL_TEXTURE_MAG_FILTER, texture->getSamplerState()->getGLMagFilter());
				glTexParameteri(texture->getGLTarget(), GL_TEXTURE_WRAP_S, texture->getSamplerState()->getGLAddrModeU());
				glTexParameteri(texture->getGLTarget(), GL_TEXTURE_WRAP_T, texture->getSamplerState()->getGLAddrModeV());
				if (texture->getType() == TT_3D)
				{
					glTexParameteri(texture->getGLTarget(), GL_TEXTURE_WRAP_R, texture->getSamplerState()->getGLAddrModeW());
				}
			}
		}
	}
}

void ShaderProgram::bind()
{
	RenderEngine::Instance()->bindGLProgram(m_glProgram);
}

void ShaderProgram::unbind()
{
	RenderEngine::Instance()->bindGLProgram(0);
}

Texture* ShaderProgram::getTexture(uint32 unit) const
{
	TextureBindMap::const_iterator it = m_textures.find(unit);
	if (it != m_textures.end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}

void ShaderProgram::bindTexture(uint32 unit, Texture* texture)
{
	m_textures[unit] = texture;
}

BLADE_NAMESPACE_END