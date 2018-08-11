#ifndef __BLADE_GLES3RENDERSTD_H__
#define __BLADE_GLES3RENDERSTD_H__

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64) || defined(__WIN64__) || defined(WIN64)
#	ifdef BLADE_GLES3RENDER_EXPORTS
#		define BLADE_GLES3RENDER_API __declspec(dllexport)
#	else
#		define BLADE_GLES3RENDER_API __declspec(dllimport)
#	endif
#endif

#include "CoreStd.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#endif
