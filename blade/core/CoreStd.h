#ifndef __BLADE_CORESTD_H__
#define __BLADE_CORESTD_H__

// Initial platform stuff to set.
#define BLADE_PLATFORM_WINDOWS	 1
#define BLADE_PLATFORM_LINUX     2
#define BLADE_PLATFORM_MAC_OSX   3
#define BLADE_PLATFORM_MAC_IOS   4
#define BLADE_PLATFORM_ANDROID   5
#define BLADE_PLATFORM_NACL		 6

// Platform recognition
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64) || defined(__WIN64__) || defined(WIN64)
#	define BLADE_PLATFORM    BLADE_PLATFORM_WINDOWS
#elif defined(__APPLE_CC__)
// Device                                                     Simulator
// Both requiring OS version 4.0 or greater
#   if __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ >= 40000 || __IPHONE_OS_VERSION_MIN_REQUIRED >= 40000
#       define BLADE_PLATFORM        BLADE_PLATFORM_MAC_IOS
#   else
#       define BLADE_PLATFORM        BLADE_PLATFORM_MAC_OSX
#   endif
#elif defined(__ANDROID__)
#	define BLADE_PLATFORM    BLADE_PLATFORM_ANDROID
#elif defined(linux) || defined(__linux) || defined(__linux__)
#	define BLADE_PLATFORM	 BLADE_PLATFORM_LINUX
#elif defined(__native_client__)
#   define BLADE_PLATFORM	 BLADE_PLATFORM_NACL
#else
#	error "Couldn't recognize platform"
#endif

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

#define BALDE_TOSTR(s) #s

#include <string>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <cassert>
#include "TypeDef.h"

#endif
