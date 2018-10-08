#include "GLES3RenderStd.h"
#include "GLES3Extension.h"
#include "util/StringUtil.h"

BLADE_NAMESPACE_BEGIN

GLES3Extension::GLES3Extension()
//m_gpuHW(GPUHW_UNKNOWN),
	: m_gpuModel(0)
	, m_majorVer(0)
	, m_minorVer(0)
	, m_bMultiContext(false)
	, m_bKHRDebug(false)
	, m_bMultiSampledRTT(false)
	, m_bMultiSampledRTTIMG(false)
	, m_bMRT(false)
	, m_bMapBufferRange(false)
	, m_bVAO(false)
	, m_bTextureStorage(true)
	, m_bGetProgramBinary(false)
	, m_bSRGB(false)
	, m_bS3TC(false)
	, m_bETC2(false)
	, m_bPVRTC(false)
	, m_bDrawInstanced(false)
	, m_bInstancedArrays(false)
	, m_bMultiThreadShader(false)
{
}

GLES3Extension::~GLES3Extension()
{
}

bool GLES3Extension::initialize()
{
	if (!gles3wInit())
	{
		return false;
	}

	m_majorVer = 3;
	m_minorVer = 0;

	m_extensions = StringUtil::Split((const char*)glGetString(GL_EXTENSIONS), " ");

	initGLExt();

	return true;
}

bool GLES3Extension::check(const String& extension) const
{
	return (KSTD::find(m_extensions.begin(), m_extensions.end(), extension) != m_extensions.end());
}

bool GLES3Extension::initGLExt()
{
	std::string versionStr = (const char*)glGetString(GL_VERSION);
	std::string vendorStr = (const char*)glGetString(GL_VENDOR);
	std::string rendererStr = (const char*)glGetString(GL_RENDERER);

	printf("GL_VERSION: %s\n", versionStr.c_str());
	printf("GL_VENDOR: %s\n", vendorStr.c_str());
	printf("GL_RENDERER: %s\n", rendererStr.c_str());
	printf("Major version: %d\n", m_majorVer);
	printf("Minor version: %d\n", m_minorVer);

	m_bMultiContext = true;
	m_bKHRDebug = check(BALDE_TOSTR(GL_KHR_debug));
	m_bMultiSampledRTT = check(BALDE_TOSTR(GL_EXT_multisampled_render_to_texture));
	m_bMultiSampledRTTIMG = check(BALDE_TOSTR(GL_IMG_multisampled_render_to_texture));
	m_bMRT = true;
	m_bTextureStorage = true;
	m_bVAO = true;
	m_bGetProgramBinary = true;
	m_bSRGB = check(BALDE_TOSTR(GL_EXT_sRGB));
	m_bSRGB = check(BALDE_TOSTR(GL_EXT_sRGB));
	m_bS3TC = check(BALDE_TOSTR(GL_EXT_texture_compression_s3tc));
	m_bPVRTC = check(BALDE_TOSTR(GL_IMG_texture_compression_pvrtc));

	m_bDrawInstanced = true;
	m_bInstancedArrays = true;
	m_bMultiThreadShader = true;

	GLint numCompressedFmts;
	glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS, &numCompressedFmts);

	std::vector<GLint> formats(numCompressedFmts);
	glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS, formats.data());

	for (GLint i = 0; i < numCompressedFmts; ++i)
	{
		if (!m_bETC2 && (GL_COMPRESSED_RGB8_ETC2 == formats[i]))
		{
			m_bETC2 = true;
			break;
		}
	}

	// Determine GPU hardware

	std::string hwStr;

	//if (rendererStr.find("Apple") != std::string::npos)
	//{
	//	m_gpuHW = GPUHW_APPLE;
	//	hwStr = "Apple";
	//}
	//else if (rendererStr.find("PowerVR") != std::string::npos)
	//{
	//	//if (m_vendor.find("Imagination Technologies"))
	//	if (rendererStr.find("SGX") != std::string::npos)
	//	{
	//		m_gpuHW = GPUHW_POWERVR_SGX;
	//		hwStr = "PowerVR SGX";
	//	}
	//	else if (rendererStr.find("Rogue") != std::string::npos)
	//	{
	//		m_gpuHW = GPUHW_POWERVR_ROGUE;
	//		hwStr = "PowerVR Rogue";
	//	}
	//	else
	//	{
	//		hwStr = "PowerVR";
	//	}
	//}
	//else if (rendererStr.find("Mali") != std::string::npos)
	//{
	//	if (rendererStr.find("Mali-T") != std::string::npos)
	//	{
	//		m_gpuHW = GPUHW_ARM_MALI_T;
	//		hwStr = "Mali-T";
	//	}
	//	else if (rendererStr.find("Mali-G") != std::string::npos)
	//	{
	//		m_gpuHW = GPUHW_ARM_MALI_G;
	//		hwStr = "Mali-G";
	//	}
	//	else
	//	{
	//		m_gpuHW = GPUHW_ARM_MALI;
	//		hwStr = "Mali";
	//	}
	//}
	//else if (rendererStr.find("Adreno") != std::string::npos)
	//{
	//	m_gpuHW = GPUHW_QUALCOMM_ADRENO;
	//	hwStr = "Adreno";
	//}
	//else if (rendererStr.find("Tegra") != std::string::npos)
	//{
	//	m_gpuHW = GPUHW_NVIDIA_TEGRA;
	//	hwStr = "Tegra";
	//}
	//else if (rendererStr.find("Immersion") != std::string::npos)
	//{
	//	m_gpuHW = GPUHW_HUAWEI_IMMERSION;
	//	hwStr = "Immersion";
	//}
	//else if (rendererStr.find("PVRVFrame") != std::string::npos)
	//{
	//	m_gpuHW = GPUHW_POWERVR_PVRVFRAME;
	//	hwStr = "PVRVFrame";
	//}
	//else if (rendererStr[0] == 'G' && rendererStr[1] == 'C')
	//{
	//	m_gpuHW = GPUHW_VIVANTE_GC;
	//	hwStr = "Vivante GC";
	//}
	//else if (rendererStr.find("Vivante GC") != std::string::npos)
	//{
	//	m_gpuHW = GPUHW_VIVANTE_GC;
	//	hwStr = "Vivante GC";
	//}
	//else if (rendererStr.find("VideoCore") != std::string::npos)
	//{
	//	m_gpuHW = GPUHW_BROADCOM_VIDEOCORE;
	//	hwStr = "Broadcom VideoCore";
	//}
	//else if (rendererStr.find("Intel(R) HD Graphics for BayTrail") != std::string::npos)
	//{
	//	m_gpuHW = GPUHW_INTEL_HD_GRAPHICS_BAYTRAIL;
	//	hwStr = "Intel(R) HD Graphics for BayTrail";
	//}
	//else if (rendererStr.find("Intel(R) HD Graphics") != std::string::npos)
	//{
	//	m_gpuHW = GPUHW_INTEL_HD_GRAPHICS;
	//	hwStr = "Intel(R) HD Graphics";
	//}
	//else
	//{
	//	m_gpuHW = GPUHW_UNKNOWN;
	//	hwStr = "Unknown";
	//}

	char buf[256];
	memset(buf, 0, 256);
	sscanf(rendererStr.c_str(), "%*[^0-9]%[0-9]", buf);

	m_gpuModel = StringUtil::ParseUI32(buf);

	printf("GPU Hardware: %s", hwStr.c_str());
	printf("GPU Model: %d", m_gpuModel);

//	if (m_gpuHW == GPUHW_POWERVR_SGX)
//	{
//		// broken drivers:
//		// PowerVR SGX
//		// OpenGL ES 2.0 build 1.9@2204701
//		// OpenGL ES 2.0 build 1.9.RC2@2139099
//		// OpenGL ES 2.0 build 1.10@2209507
//		// OpenGL ES 2.0 build 1.11@2630400
//
//		// stable drivers:
//		// PowerVR Rogue
//		// OpenGL ES 3.1 build 1.4@3300288
//		// OpenGL ES 3.0 build 1.4@3304414
//		// OpenGL ES 3.1 build 1.5@3776568
//#if (BLADE_PLATFORM != BLADE_PLATFORM_MAC_IOS)
//		m_bVAO = false;
//		m_bGetProgramBinary = false;
//#endif
//		// single context loading is faster than multi context loading
//		m_bMultiContext = false;
//	}
//	else if (m_gpuHW == GPUHW_POWERVR_ROGUE)
//	{
//		m_bDrawInstanced = false;
//		m_bInstancedArrays = false;
//	}
//	else if (m_gpuHW == GPUHW_ARM_MALI)
//	{
//		//////////////////////////////////////////////////////////////////////////
//		// Mali
//
//		// Device driver API match
//		// Device driver API version : 10
//		// User space API version : 10
//		// mali: REVISION=Linux-r2p4-02rel0 BUILD_DATE=Tue Oct 16 15:37:13 KST 2012 
//
//		// Device driver API match
//		// Device driver API version : 29
//		// User space API version : 29
//		// mali : REVISION = Linux - r3p2 - 01rel3 BUILD_DATE = Tue Jul 22 19 : 59 : 34 KST 2014
//
//		// OpenGL ES 3.1 v1.r7p0-03rel0.b596bd02e7d0169c10574b57180c8b57
//
//		//m_bVAO = false;
//		m_bMultiThreadShader = false;
//		m_bGetProgramBinary = false;
//	}
//	else if (m_gpuHW == GPUHW_QUALCOMM_ADRENO)
//	{
//		// broken drivers:
//		// OpenGL ES 2.0 V@4.1 AU@  (CL@3090659)
//		// OpenGL ES 2.0 V@6.0 AU@04.01.02.21.119 (CL@3357771)
//		// OpenGL ES 2.0 V@14.0 AU@04.02.02.093.020 (CL@3579225)
//		// OpenGL ES 3.0 V@45.0 AU@  (CL@4169980)
//		// OpenGL ES 3.0 V@53.0 AU@04.03.00.173.012 LNXBUILD_AU_LINUX_ANDROID_JB_3.2.4.04.03.00.173.012+PATCH[ES]_msm8226_JB_3.2.4_release_ENGG (CL@)
//		// OpenGL ES 3.0 V@66.0 AU@  (CL@)
//		// OpenGL ES 3.0 V@84.0 AU@  (CL@)
//		// OpenGL ES 3.0 V@84.0 AU@04.04.04.179.002 (CL@)
//		// OpenGL ES 3.0 V@100.0 AU@  (CL@)05.00.02.031.018
//		// OpenGL ES 3.0 V@100.0 AU@ (GIT@I7b941c52a8)
//
//		// fatal bug driver - can not fix
//		// OpenGL ES 3.0 V@140.0 AU@  (GIT@I741a3d36ca)
//
//		// stable drivers:
//		// OpenGL ES 3.1 V@103.0 AU@  (GIT@Iae42b9ed90)
//		// OpenGL ES 3.1 V@104.0 AU@
//		// OpenGL ES 3.1 V@127.0 (GIT@I8366cd0437)
//		// OpenGL ES 3.1 V@140.0 (GIT@Ibb8f3faafb)
//		// OpenGL ES 3.2 V@145.0 (GIT@I5bc0f577f9)
//
//		memset(buf, 0, 256);
//		sscanf(versionStr.c_str(), "%*[^@]@%[0-9]", buf);
//
//		uint32 driverVersion = StringUtil::ParseUI32(buf);
//		if (driverVersion < 84)
//		{
//			m_bMultiContext = false;
//		}
//
//		if (driverVersion < 127)
//		{
//			m_bVAO = false;
//			//m_bDrawInstanced = false;
//			//m_bInstancedArrays = false;
//		}
//
//		//m_bGetProgramBinary = false;
//	}
//	else if (m_gpuHW == GPUHW_HUAWEI_IMMERSION)
//	{
//		m_bGetProgramBinary = false;
//	}
//	else if (m_gpuHW == GPUHW_VIVANTE_GC)
//	{
//		// GC1000 - call eglMakeCurrent error in PBuffer context
//		if (m_gpuModel < 2000)
//		{
//			m_bMultiContext = false;
//		}
//
//		if (m_gpuModel <= 2000)
//		{
//			m_bGetProgramBinary = false;
//		}
//	}
//	else if (m_gpuHW == GPUHW_INTEL_HD_GRAPHICS_BAYTRAIL)
//	{
//		m_bMultiContext = false;
//	}
//	else if (m_gpuHW == GPUHW_POWERVR_PVRVFRAME)
//	{
//		// broken drivers:
//		// PVRVFrame 10.2 - None (Host : GeForce GT 630/PCIe/SSE2) (SDK Build: 4.0@3835662)
//		m_bGetProgramBinary = false;
//		m_bVAO = false;
//		m_bDrawInstanced = false;
//		m_bInstancedArrays = false;
//	}

	//////////////////////////////////////////////////////////////////////////
	// NVIDIA Tegra
	// stable drivers:
	// OpenGL ES 2.0 17.01214
	// OpenGL ES 3.1 334.00

	//////////////////////////////////////////////////////////////////////////
	// Immersion
	// fatal bug driver - can not fix
	// OpenGL ES 2.0

	//////////////////////////////////////////////////////////////////////////
	// VideoCore IV HW
	// OpenGL ES 2.0

	//////////////////////////////////////////////////////////////////////////

	printf("Multiple Context: %s\n", (m_bMultiContext ? "yes" : "no"));
	printf("GL_KHR_debug: %s\n", (m_bKHRDebug ? "yes" : "no"));
	printf("GL_EXT_multisampled_render_to_texture: %s\n", (m_bMultiSampledRTT ? "yes" : "no"));
	printf("Multiple Render Target: %s\n", (m_bMRT ? "yes" : "no"));
	printf("Vertex Array Object: %s\n", (m_bVAO ? "yes" : "no"));
	printf("Get Program Binary: %s\n", (m_bGetProgramBinary ? "yes" : "no"));
	printf("Draw Instanced: %s\n", (m_bDrawInstanced ? "yes" : "no"));
	printf("Instanced Arrays: %s\n", (m_bInstancedArrays ? "yes" : "no"));
	printf("ETC2 texture format: %s\n", (m_bETC2 ? "yes" : "no"));
	printf("PVRTC texture format: %s\n", (m_bPVRTC ? "yes" : "no"));
	printf("MultiThread Shader Compilation: %s\n", (m_bMultiThreadShader ? "yes" : "no"));

	return true;
}

bool GLES3Extension::checkTextureStorageCompressedFormat(GLenum glInternalFmt) const
{
	// https://www.khronos.org/opengles/sdk/docs/man3/html/glTexStorage2D.xhtml

	switch (glInternalFmt)
	{
	case GL_COMPRESSED_R11_EAC:
	case GL_COMPRESSED_SIGNED_R11_EAC:
	case GL_COMPRESSED_RG11_EAC:
	case GL_COMPRESSED_SIGNED_RG11_EAC:
	case GL_COMPRESSED_RGB8_ETC2:
	case GL_COMPRESSED_SRGB8_ETC2:
	case GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2:
	case GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2:
	case GL_COMPRESSED_RGBA8_ETC2_EAC:
	case GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC:
		return true;
	default: return false;
	}
}

std::string GLES3Extension::getCompressedTextureFormatName(GLenum val) const
{
	struct GLEnumSt
	{
		const char *name;
		GLenum val;
	};

	static const GLEnumSt enums[] =
	{
		{ "GL_COMPRESSED_ALPHA", 0x84E9 },
		{ "GL_COMPRESSED_LUMINANCE", 0x84EA },
		{ "GL_COMPRESSED_LUMINANCE_ALPHA", 0x84EB },
		{ "GL_COMPRESSED_INTENSITY", 0x84EC },
		{ "GL_COMPRESSED_RGB", 0x84ED },
		{ "GL_COMPRESSED_RGBA", 0x84EE },
		{ "GL_COMPRESSED_TEXTURE_FORMATS", 0x86A3 },
		{ "GL_COMPRESSED_SRGB", 0x8C48 },
		{ "GL_COMPRESSED_SRGBA_ALPHA", 0x8C49 },
		{ "GL_COMPRESSED_SLUMINANCE", 0x8C4A },
		{ "GL_COMPRESSED_SLUMINANCE_ALPHA", 0x8C4B },
		{ "GL_COMPRESSED_RGBA_BPTC_UNORM", 0x8E8C },
		{ "GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM", 0x8E8D },
		{ "GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT", 0x8E8E },
		{ "GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT", 0x8E8F },
		{ "GL_COMPRESSED_RGB_FXT1_3DFX", 0x86B0 },
		{ "GL_COMPRESSED_RGBA_FXT1_3DFX", 0x86B1 },

		{ "GL_COMPRESSED_RGB_S3TC_DXT1_ANGLE", 0x83F0 },
		{ "GL_COMPRESSED_RGBA_S3TC_DXT1_ANGLE", 0x83F1 },
		{ "GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE", 0x83F2 },
		{ "GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE", 0x83F3 },

		{ "GL_COMPRESSED_R11_EAC", 0x9270 },
		{ "GL_COMPRESSED_SIGNED_R11_EAC", 0x9271 },
		{ "GL_COMPRESSED_RG11_EAC", 0x9272 },
		{ "GL_COMPRESSED_SIGNED_RG11_EAC", 0x9273 },

		{ "GL_COMPRESSED_RGB8_ETC2", 0x9274 },
		{ "GL_COMPRESSED_SRGB8_ETC2", 0x9275 },
		{ "GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2", 0x9276 },
		{ "GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2", 0x9277 },
		{ "GL_COMPRESSED_RGBA8_ETC2_EAC", 0x9278 },
		{ "GL_COMPRESSED_SRGBA8_ALPHA8_ETC2_EAC", 0x9279 },

		{ "GL_COMPRESSED_ALPHA_ARB", 0x84E9 },
		{ "GL_COMPRESSED_LUMINANCE_ARB", 0x84EA },
		{ "GL_COMPRESSED_LUMINANCE_ALPHA_ARB", 0x84EB },
		{ "GL_COMPRESSED_INTENSITY_ARB", 0x84EC },
		{ "GL_COMPRESSED_RGB_ARB", 0x84ED },
		{ "GL_COMPRESSED_RGBA_ARB", 0x84EE },
		{ "GL_COMPRESSED_TEXTURE_FORMATS_ARB", 0x86A3 },
		{ "GL_COMPRESSED_RGBA_BPTC_UNORM_ARB", 0x8E8C },
		{ "GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB", 0x8E8D },
		{ "GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB", 0x8E8E },
		{ "GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB", 0x8E8F },

		{ "GL_COMPRESSED_RED_RGTC1", 0x8DBB },
		{ "GL_COMPRESSED_SIGNED_RED_RGTC1", 0x8DBC },
		{ "GL_COMPRESSED_RG_RGTC2", 0x8DBD },
		{ "GL_COMPRESSED_SIGNED_RG_RGTC2", 0x8DBE },

		{ "GL_COMPRESSED_RED", 0x8225 },
		{ "GL_COMPRESSED_RG", 0x8226 },
		{ "GL_COMPRESSED_LUMINANCE_ALPHA_3DC_ATI", 0x8837 },
		{ "GL_COMPRESSED_LUMINANCE_LATC1_EXT", 0x8C70 },
		{ "GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT", 0x8C71 },
		{ "GL_COMPRESSED_LUMINANCE_LATC2_EXT", 0x8C72 },
		{ "GL_COMPRESSED_SIGNED_LUMINANCE_LATC2_EXT", 0x8C73 },

		{ "GL_COMPRESSED_SRGB_EXT", 0x8C48 },
		{ "GL_COMPRESSED_SRGB_ALPHA_EXT", 0x8C49 },
		{ "GL_COMPRESSED_SLUMINANCE_EXT", 0x8C4A },
		{ "GL_COMPRESSED_SLUMINANCE_ALPHA_EXT", 0x8C4B },
		{ "GL_COMPRESSED_SRGB_S3TC_DXT1_EXT", 0x8C4C },
		{ "GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT", 0x8C4D },
		{ "GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT", 0x8C4E },
		{ "GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT", 0x8C4F },

		{ "GL_COMPRESSED_RGBA_ASTC_4x4_KHR", 0x93B0 },
		{ "GL_COMPRESSED_RGBA_ASTC_5x4_KHR", 0x93B1 },
		{ "GL_COMPRESSED_RGBA_ASTC_5x5_KHR", 0x93B2 },
		{ "GL_COMPRESSED_RGBA_ASTC_6x5_KHR", 0x93B3 },
		{ "GL_COMPRESSED_RGBA_ASTC_6x6_KHR", 0x93B4 },
		{ "GL_COMPRESSED_RGBA_ASTC_8x5_KHR", 0x93B5 },
		{ "GL_COMPRESSED_RGBA_ASTC_8x6_KHR", 0x93B6 },
		{ "GL_COMPRESSED_RGBA_ASTC_8x8_KHR", 0x93B7 },
		{ "GL_COMPRESSED_RGBA_ASTC_10x5_KHR", 0x93B8 },
		{ "GL_COMPRESSED_RGBA_ASTC_10x6_KHR", 0x93B9 },
		{ "GL_COMPRESSED_RGBA_ASTC_10x8_KHR", 0x93BA },
		{ "GL_COMPRESSED_RGBA_ASTC_10x10_KHR", 0x93BB },
		{ "GL_COMPRESSED_RGBA_ASTC_12x10_KHR", 0x93BC },
		{ "GL_COMPRESSED_RGBA_ASTC_12x12_KHR", 0x93BD },

		{ "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR", 0x93D0 },
		{ "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR", 0x93D1 },
		{ "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR", 0x93D2 },
		{ "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR", 0x93D3 },
		{ "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR", 0x93D4 },
		{ "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR", 0x93D5 },
		{ "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR", 0x93D6 },
		{ "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR", 0x93D7 },
		{ "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR", 0x93D8 },
		{ "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR", 0x93D9 },
		{ "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR", 0x93DA },
		{ "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR", 0x93DB },
		{ "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR", 0x93DC },
		{ "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR", 0x93DD },

		{ "GL_PALETTE4_RGB8_OES", 0x8B90 },
		{ "GL_PALETTE4_RGBA8_OES", 0x8B91 },
		{ "GL_PALETTE4_R5_G6_B5_OES", 0x8B92 },
		{ "GL_PALETTE4_RGBA4_OES", 0x8B93 },
		{ "GL_PALETTE4_RGB5_A1_OES", 0x8B94 },
		{ "GL_PALETTE8_RGB8_OES", 0x8B95 },
		{ "GL_PALETTE8_RGBA8_OES", 0x8B96 },
		{ "GL_PALETTE8_R5_G6_B5_OES", 0x8B97 },
		{ "GL_PALETTE8_RGBA4_OES", 0x8B98 },
		{ "GL_PALETTE8_RGB5_A1_OES", 0x8B99 },

		{ "GL_ETC1_RGB8_OES", 0x8D64 }
	};

	const int n = sizeof(enums) / sizeof(enums[0]);
	int i;
	for (i = 0; i < n; i++)
	{
		if (enums[i].val == val) {
			return enums[i].name;
		}
	}

	return "Unknown format";
}

BLADE_NAMESPACE_END