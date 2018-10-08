#ifndef __BLADE_GLES3EXTENSION_H__
#define __BLADE_GLES3EXTENSION_H__

#ifndef GL_GLEXT_PROTOTYPES
#	define GL_GLEXT_PROTOTYPES
#endif

#include "gles3w.h"
#include "util/Singleton.h"

#if (BLADE_PLATFORM == BLADE_PLATFORM_MAC_IOS)
	#ifdef __OBJC__
		#include <OpenGLES/EAGL.h>
	#endif
#else
	#include <EGL/egl.h>
	#include <EGL/eglext.h>
	#include <EGL/eglplatform.h>
#endif

#ifndef EGL_KHR_create_context
#define EGL_KHR_create_context 1
#define EGL_CONTEXT_MAJOR_VERSION_KHR						EGL_CONTEXT_CLIENT_VERSION
#define EGL_CONTEXT_MINOR_VERSION_KHR						0x30FB
#define EGL_CONTEXT_FLAGS_KHR								0x30FC
#define EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR					0x30FD
#define EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR	0x31BD
#define EGL_NO_RESET_NOTIFICATION_KHR						0x31BE
#define EGL_LOSE_CONTEXT_ON_RESET_KHR						0x31BF
#define EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR					0x00000001
#define EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR	    0x00000002
#define EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR			0x00000004
#define EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR				0x00000001
#define EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR    0x00000002
#define EGL_OPENGL_ES3_BIT_KHR								0x00000040
#endif

#ifndef GL_OES_compressed_ETC1_RGB8_texture
#	define GL_OES_compressed_ETC1_RGB8_texture 1
#	define GL_ETC1_RGB8_OES								0x8D64
#endif

#define GL_COMPRESSED_RGB8_ETC2							0x9274
#define GL_COMPRESSED_SRGB8_ETC2						0x9275
#define GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2		0x9276
#define GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2	0x9277
#define GL_COMPRESSED_RGBA8_ETC2_EAC					0x9278
#define GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC				0x9279

BLADE_NAMESPACE_BEGIN

class BLADE_GLES3RENDER_API GLES3Extension : public Singleton < GLES3Extension >
{
public:
	GLES3Extension();
	~GLES3Extension();

	typedef std::vector<GLint>	ExtEnumList;

public:
	bool				initialize();
	bool				check(const std::string& extension) const;
	bool				checkTextureStorageCompressedFormat(GLenum glInternalFmt) const;
	std::string			getCompressedTextureFormatName(GLenum val) const;

//	inline GPUHardware	getGPUHardware() const { return m_gpuHW; }
	inline uint32		getGPUModel() const { return m_gpuModel; }
	inline uint32		getMajorVersion() const { return m_majorVer; }
	inline uint32		getMinorVersion() const { return m_minorVer; }
	inline bool			isSupportMultiContext() const { return m_bMultiContext; }
	inline bool			isSupportKHRDebug() const { return m_bKHRDebug; };
	inline bool			isSupportMultiSampledRTT() const { return m_bMultiSampledRTT; }
	inline bool			isSupportMultiSampledRTTIMG() const { return m_bMultiSampledRTTIMG; }
	inline bool			isSupportMRT() const { return m_bMRT; };
	inline bool			isSupportMapBufferRange() const { return m_bMapBufferRange; };
	inline bool			isSupportVAO() const { return m_bVAO; }
	inline bool			isSupportTextureStorage() const { return m_bTextureStorage; };
	inline bool			isSupportGetProgramBinary() const { return m_bGetProgramBinary; }
	inline bool			isSupportSRGB() const { return m_bSRGB; };
	inline bool			isSupportS3TC() const { return m_bS3TC; }
	inline bool			isSupportETC2() const { return m_bETC2; }
	inline bool			isSupportDrawInstanced() const { return m_bDrawInstanced; }
	inline bool			isSupportInstancedArrays() const { return m_bInstancedArrays; }
	inline bool			isSupportMultiThreadShader() const { return m_bMultiThreadShader; }

private:
	bool				initGLExt();

private:
//	GPUHardware		           m_gpuHW;
	uint32			           m_gpuModel;
	uint32			           m_majorVer;
	uint32			           m_minorVer;
	std::vector<std::string>   m_extensions;
	bool			           m_bMultiContext;
	bool			           m_bKHRDebug;
	bool			           m_bMultiSampledRTT;
	bool			           m_bMultiSampledRTTIMG;
	bool			           m_bMRT;
	bool			           m_bMapBufferRange;
	bool			           m_bVAO;
	bool			           m_bTextureStorage;
	bool			           m_bGetProgramBinary;
	bool			           m_bSRGB;
	bool			           m_bS3TC;
	bool			           m_bETC2;
	bool			           m_bPVRTC;
	bool			           m_bDrawInstanced;
	bool			           m_bInstancedArrays;
	bool			           m_bMultiThreadShader;


};

BLADE_NAMESPACE_END

#endif
