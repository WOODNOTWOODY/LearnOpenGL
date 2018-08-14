#ifndef __BLADE_CORESTD_H__
#define __BLADE_CORESTD_H__

#define BLADE_NAMESPACE_BEGIN	namespace Blade {
#define BLADE_NAMESPACE_END		}
#define USING_NAMESPACE_BLADE   using namespace Blade

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64) || defined(__WIN64__) || defined(WIN64)
#	ifdef BLADE_CORE_EXPORTS
#		define BLADE_CORE_API __declspec(dllexport)
#	else
#		define BLADE_CORE_API __declspec(dllimport)
#	endif
#endif

#define BLADE_NEW(T)								new T
#define BLADE_NEW_ARRAY(T, count)					new T[count]
#define BLADE_DELETE(ptr)							delete (ptr)
#define BLADE_DELETE_ARRAY(ptr)						delete[] (ptr)
#define BLADE_SAFE_DELETE(ptr)						if(ptr) { BLADE_DELETE(ptr); (ptr) = NULL; }
#define BLADE_SAFE_DELETE_ARRAY(ptr)				if(ptr) { BLADE_DELETE_ARRAY(ptr); (ptr) = NULL; }
#define BLADE_MALLOC(bytes) malloc(bytes)
#define BLADE_FREE(ptr) free(ptr)
#define BLADE_SAFE_FREE(ptr) if(ptr) { free(ptr); (ptr) = NULL; }

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>
#include "TypeDef.h"

#endif
